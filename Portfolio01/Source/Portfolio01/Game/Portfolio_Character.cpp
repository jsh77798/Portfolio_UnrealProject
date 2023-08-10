// Fill out your copyright notice in the Description page of Project Settings.


#include "Portfolio_Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APortfolio_Character::APortfolio_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 25.f;
	BaseLookUpRate = 25.f;


	//Create our components 스프링암 설정
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 140.0f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 10.0f;
	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//캐릭터 이동 회전 (#include "GameFramework/CharacterMovementComponent.h" 헤더 필요)
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
}

// Called when the game starts or when spawned
void APortfolio_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortfolio_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//use controller rotation yaw 설정
	{
		if (AniState == EAniState::Idle || AniState == EAniState::ForwardMove )
		{
			bUseControllerRotationYaw = false;

			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
		}
		else 
		{
		    bUseControllerRotationYaw = true;
		}
	}


	//Zoom in if ZoomIn button is down, zoom back out if it's not
	{
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.15f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.15f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		//FMath::Lerp<float>(Af, Bf, C) -> C의 속력으로 A-B를 한다.
		OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(140.0f, 80.0f, ZoomFactor);
		OurCameraSpringArm->SocketOffset.Y = FMath::Lerp<float>(55.0f, 80.0f, ZoomFactor);
		OurCameraSpringArm->SocketOffset.Z = FMath::Lerp<float>(65.0f, 70.0f, ZoomFactor);
	}
}


// Called to bind functionality to input
void APortfolio_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;

	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		
		// 축매핑
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));
		
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerAimingCheck", EKeys::RightMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAiming"), EKeys::RightMouseButton));
    	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::LeftMouseButton));

	}

	// 키와 함수를 연결합니다.
	// 이 키가 눌리면 이 함수를 실행시켜줘인데.
	// 축일때는 일단 계속 실행시켜줘.
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &APortfolio_Character::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &APortfolio_Character::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &APortfolio_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &APortfolio_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &APortfolio_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &APortfolio_Character::LookUpAtRate);

	//PlayerInputComponent->BindAxis("PlayerAimingCheck", this, &APortfolio_Character::IN_AimingAction_Check);
	PlayerInputComponent->BindAction("PlayerAiming", EInputEvent::IE_Pressed , this, &APortfolio_Character::IN_AimingAction);
	PlayerInputComponent->BindAction("PlayerAiming", EInputEvent::IE_Released, this, &APortfolio_Character::OUT_AimingAction);
	PlayerInputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &APortfolio_Character::AttackAction);
	
}


void APortfolio_Character::MoveRight(float Val)
{
	/*
	if (AniState == EAniState::W_Attack)
	{
		return;
	}
	*/

	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			// transform to world space and add it
			// 현재 내 회전을 가져와서 y축에 해당하는 축벡터를 얻어오는 겁니다.
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);

			AniState = Val > 0.f ? EAniState::RightMove : EAniState::LeftMove;
			return;
		}
	}
	else
	{
		if (AniState == EAniState::RightMove || AniState == EAniState::LeftMove)
		{
			AniState = EAniState::Idle;
		}
	}
}


void APortfolio_Character::MoveForward(float Val)
{
	if (Val != 0.f)
	{

		if (Controller)
		{
			
			FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);
			AddMovementInput(Direction, Val);

			AniState = Val > 0.f ? EAniState::ForwardMove : EAniState::BackwardMove;
			return;

			/*
			
			// 컨트롤러는 기본적으로
			// charcter 하나씩 붙어 있습니다.
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// 이건 방향일 뿐입니다.
			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
			// 탑뷰게임이면 다르게 나오게 되는데.
			// 지금은 TPS를 하고 있기 때문에 컨트롤러의 회전이나 액터의 회전이나 같아요.
			// AddMovementInput(GetActorForwardVector(), Val);

			*/
		}
	}
	else
	{
		if (AniState == EAniState::ForwardMove || AniState == EAniState::BackwardMove)
		{
			AniState = EAniState::Idle;
		}
	}

	// 이런 느낌의 함수 즉 static함수를 의미한다.
	// AEGLOBAL::DebugPrint("AAAAAAA");
}


void APortfolio_Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void APortfolio_Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void APortfolio_Character::IN_AimingAction()
{
    AniState = EAniState::W_Aiming;

	AimingActionCheck = 1;
	//ZoomingIn = 1;
	bZoomingIn = true;
}

void APortfolio_Character::OUT_AimingAction()
{
	if (AimingActionCheck == 0)
	{
		AniState = EAniState::Idle;
	}
	else
	{
		AniState = EAniState::Idle;
		AimingActionCheck = 0;
	}

	bZoomingIn = false;
}

void APortfolio_Character::AttackAction()
{
	// 무브먼트 컴포넌트를 통해서 한다.
	// GetMovementComponent()
	if (AimingActionCheck == 1 && AniState == EAniState::W_Aiming)
	{
	    AniState = EAniState::W_Attack;
	}
   
	return;
}


void APortfolio_Character::AnimationTick()
{

}
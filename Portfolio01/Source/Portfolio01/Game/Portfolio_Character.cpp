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

	//캐릭터 이동속도 설정
	MoveCom = Cast<UCharacterMovementComponent>(GetMovementComponent());
	MoveCom->MaxWalkSpeed = 350.0f; 
	

	//Create our components 스프링암 설정
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 140.0f;
	OurCameraSpringArm->SocketOffset.Y = 55.0f;
	OurCameraSpringArm->SocketOffset.Z = 65.0f;
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

	//GetGlobalAnimInstance()->OnPlayMontageNotifyBegin.AddUniqueDynamic(this, &APortfolio_Character::AnimNotifyBegin);
	//GetGlobalAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &APortfolio_Character::AnimNotifyBegin);
}

// Called every frame
void APortfolio_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Run 상태확인 및 설정
	{
	    if (AniState == EAniState::Idle)
	    {
	    	RunCheck = 0;
			RunZooming = false;
	    }
	    //if (RunAnimCheck == 1)
	    //{
	    //   AniState = EAniState::Run;
	    //}
	}

	//use controller rotation yaw 설정
	{
		if (AniState == EAniState::Idle || AniState == EAniState::ForwardMove || RunCheck == 1)
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
		if (bZoomingIn || RunZooming || CrouchZooming)
		{
			ZoomFactor += DeltaTime / S;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / S;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		//FMath::Lerp<float>(Af, Bf, C) -> C의 속력으로 A-B를 한다.
		
		OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(140.0f, A, ZoomFactor);
		OurCameraSpringArm->SocketOffset.Y = FMath::Lerp<float>(55.0f, B, ZoomFactor);
		OurCameraSpringArm->SocketOffset.Z = FMath::Lerp<float>(65.0f, C, ZoomFactor);
	}


	//공격에서 AttackCheck == 1이 되면 여기서 공격실행
	{
		if (AttackCheck == 1) {

	        if (AimingActionCheck == 1 && AniState == EAniState::W_Aiming)
	        {
		       AniState = EAniState::W_Attack;
			   AttackCheck= 0;
	        }
 
	        if (AimingActionCheck == 1
		        || AniState == EAniState::Aiming_ForwardMove
		        || AniState == EAniState::Aiming_BackwardMove
		        || AniState == EAniState::Aiming_RightMove
		        || AniState == EAniState::Aiming_LeftMove)
	        {
		        AniState = EAniState::W_Attack;
				AttackCheck= 0;
	        }
		}
	}

}

void APortfolio_Character::ZoomCheck(float *_A, float *_B, float *_C, float* _S)
{
	A = *_A;
	B = *_B;
	C = *_C;
	S = *_S;

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

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerRun"), EKeys::LeftShift));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerCrouch"), EKeys::Q));
	}

	// 키와 함수를 연결한다
	// 이 키가 눌리면 이 함수를 실행시켜줘인데.
	// BindAxis_축일때는 일단 계속 실행시켜줘.
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

	PlayerInputComponent->BindAction("PlayerRun", EInputEvent::IE_Pressed, this, &APortfolio_Character::Run);
	PlayerInputComponent->BindAction("PlayerCrouch", EInputEvent::IE_Pressed, this, &APortfolio_Character::Crouch);
	
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

			if (RunCheck == 1 && AimingActionCheck == 0 && AniState != EAniState::Idle)
			{
				MoveCom->MaxWalkSpeed = 420.0f;
				RunZooming = true;
				AniState = Val > 0.f ? EAniState::RightRun : EAniState::LeftRun;
				return;
			}
			
			if (CrouchCheck == 1)
			{
				MoveCom->MaxWalkSpeed = 250.0f;
				AniState = Val > 0.f ? EAniState::Crouch_RightMove : EAniState::Crouch_LeftMove;
				return;
			}

			
		    {
			    if (AimingActionCheck == 0) 
			    {
			  	    MoveCom->MaxWalkSpeed = 350.0f;
				    AniState = Val > 0.f ? EAniState::RightMove : EAniState::LeftMove;
				    return;
			    }
			    else 
			    {
			    	MoveCom->MaxWalkSpeed = 300.0f;
			        AniState = Val > 0.f ? EAniState::Aiming_RightMove : EAniState::Aiming_LeftMove;
				    return;
		  	    }  
		    }


		}
	}
	else
	{
		if ( AniState == EAniState::RightMove || AniState == EAniState::LeftMove )
		{
			AniState = EAniState::Idle;
		}
		if ( AniState == EAniState::Aiming_RightMove || AniState == EAniState::Aiming_LeftMove )
		{
			AniState = EAniState::W_Aiming;
		}

		if (AniState == EAniState::RightRun || AniState == EAniState::LeftRun)
		{
			AniState = EAniState::Idle;
			RunZooming = false;
			RunCheck = 0;
		}

		if (AniState == EAniState::Crouch_RightMove || AniState == EAniState::Crouch_LeftMove)
		{
			AniState = EAniState::Crouch_Idle;
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


			if (RunCheck == 1 && AimingActionCheck == 0 && AniState != EAniState::Idle)
			{
				MoveCom->MaxWalkSpeed = 420.0f;
				RunZooming = true;
				AniState = Val > 0.f ? EAniState::ForwardRun : EAniState::BackwardRun;
				return;
			}

			if (CrouchCheck == 1)
			{
				MoveCom->MaxWalkSpeed = 250.0f;
				AniState = Val > 0.f ? EAniState::Crouch_ForwardMove : EAniState::Crouch_BackwardMove;
				return;
			}

			
			{
				if (AimingActionCheck == 0)
				{
					MoveCom->MaxWalkSpeed = 350.0f;
					AniState = Val > 0.f ? EAniState::ForwardMove : EAniState::BackwardMove;
					return;
				}
				else
				{
					MoveCom->MaxWalkSpeed = 300.0f;
					AniState = Val > 0.f ? EAniState::Aiming_ForwardMove : EAniState::Aiming_BackwardMove;
					return;
				}
			}

		}
	}
	else
	{
		if ( AniState == EAniState::ForwardMove || AniState == EAniState::BackwardMove )
		{
			AniState = EAniState::Idle;
		}
		if (AniState == EAniState::Aiming_ForwardMove || AniState == EAniState::Aiming_BackwardMove)
		{
			AniState = EAniState::W_Aiming;
		}

		if (AniState == EAniState::ForwardRun || AniState == EAniState::BackwardRun)
		{
			AniState = EAniState::Idle;
			RunZooming = false;
			RunCheck = 0;
		}

		if (AniState == EAniState::Crouch_ForwardMove || AniState == EAniState::Crouch_BackwardMove)
		{
			AniState = EAniState::Crouch_Idle;
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

	float a = 80.0f;
	float b = 80.0f;
	float c = 70.0f;
	float s = 0.15f;
	ZoomCheck(&a, &b, &c, &s);

	RunCheck = 0;
	CrouchCheck = 0;
	CrouchZooming = false;
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
	/*
	if ( AimingActionCheck == 1 && AniState == EAniState::W_Aiming )
	{
	    AniState = EAniState::W_Attack;
	}

	if (AimingActionCheck == 1 
		|| AniState == EAniState::Aiming_ForwardMove
		|| AniState == EAniState::Aiming_BackwardMove
		|| AniState == EAniState::Aiming_RightMove
		|| AniState == EAniState::Aiming_LeftMove )
	{
		AniState = EAniState::W_Attack;
    }
	*/

	//Tick에서 공격
	AttackCheck = 1;
	return;
}

void APortfolio_Character::AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	UPortfolio_GameInstance* Inst = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();

	TSubclassOf<UObject> Effect = Inst->GetSubClass(TEXT("ShotEffect"));
	TSubclassOf<UObject> RangeAttack = Inst->GetSubClass(TEXT("PlayerRangeAttack"));

	/*
	if (nullptr != Effect)
	{
		AActor* Actor = GetWorld()->SpawnActor<AActor>(Effect);
		Actor->SetActorLocation(GetActorLocation());
		Actor->SetActorRotation(GetActorRotation());
	}
	*/
	if (nullptr != Effect)
	{
		FTransform Trans;
		FVector Pos;
		TArray<UActorComponent*> MeshEffects = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("WeaponEffect"));
		TArray<UActorComponent*> StaticMeshs = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("WeaponMesh"));

		USceneComponent* EffectCom = Cast<USceneComponent>(MeshEffects[0]);
		Pos = EffectCom->GetComponentToWorld().GetLocation();

		// 발사체 만들기
		{
			AActor* Actor = GetWorld()->SpawnActor<AActor>(RangeAttack);
			Actor->Tags.Add(TEXT("Damage"));
			APortfolio_Tile* ProjectTile = Cast<APortfolio_Tile>(Actor);
			ProjectTile->SetActorLocation(Pos);
			ProjectTile->SetActorRotation(GetActorRotation());
			ProjectTile->GetSphereComponent()->SetCollisionProfileName(TEXT("PlayerAttack"), true);
			
		}
	}
}

void APortfolio_Character::Run() 
{
	float a = 145.0f;
	float b = 45.0f;
	float c = 60.0f;
	float s = 0.35f;

	if (RunCheck == 0)
	{
		CrouchCheck = 0;
		CrouchZooming = false;

		RunCheck = 1;

		ZoomCheck(&a, &b, &c, &s);

		return;
	}
	else
	{
		RunZooming = false;
		RunCheck = 0;
		return;
	}
}

void APortfolio_Character::Crouch() 
{
	float a = 150.0f;
	float b = 55.0f;
	float c = 50.0f;
	float s = 0.35f;
	if (CrouchCheck == 0 && AimingActionCheck == 0)
	{
		RunCheck = 0;
		AimingActionCheck = 0;
		bZoomingIn = false;

		ZoomCheck(&a, &b, &c, &s);
		CrouchZooming = true;
	    CrouchCheck = 1;
		AniState = EAniState::CrouchOn;
		return;
	}
	else
	{
		AniState = EAniState::CrouchOff;
		CrouchZooming = false;
		CrouchCheck = 0;
		return;
	}
}

void APortfolio_Character::AnimationTick()
{

}
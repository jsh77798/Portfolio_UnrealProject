// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Global/Portfolio_GameInstance.h>
#include <Global/Portfolio_Tile.h>
#include "Player_AnimInstance.h"
#include "Portfolio_Enums.h"
#include "GameFramework/SpringArmComponent.h"
#include "Portfolio_Character.generated.h"

UCLASS()
class PORTFOLIO01_API APortfolio_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APortfolio_Character();


	// 블루프린트에서 호출하게 하려면 기본적으로 public이어야 합니다.
	UFUNCTION(BlueprintCallable)
	void AnimationTick();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
public:	

	class UPlayer_AnimInstance* GetGlobalAnimInstance()
	{
		return GlobalAnimInstance;
	}

	void MoveRight(float Val);
	void MoveForward(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void IN_AimingAction();
	void OUT_AimingAction();
	void AttackAction();

	void Run();
	void Crouch();

	void ZoomCheck(float *_A, float *_B, float *_C, float* _S);
	float A; //타겟암 길이
	float B; //타겟암 Y축
	float C; //타겟암 Z축
	float S; //속력

	int RunCheck = 0;
	bool RunZooming;

	int CrouchCheck = 0;
	bool CrouchZooming;
	

	int AimingActionCheck = 0;
	int AttackCheck = 0;

	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;

	UCharacterMovementComponent* MoveCom;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* OurCameraSpringArm;
	//타겟암 길이: 140.0
	//소켓 오프셋: 0.0 / 55.0 / 65.0
	//타깃 오프셋: 0.0 / 0.0 / 0.0
	
	//UCameraComponent* OurCamera;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;

	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
		EAniState AniState = EAniState::Idle;

	//몽타주 애니메이션 블루프린트내 Map가져오기
	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		TMap<EAniState, class UAnimMontage*> AllAnimations;

	UFUNCTION()
		void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	float Speed = 1000.0f;

private:
	class UPlayer_AnimInstance* GlobalAnimInstance = nullptr;
};


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


	// �������Ʈ���� ȣ���ϰ� �Ϸ��� �⺻������ public�̾�� �մϴ�.
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
	//void IN_AimingAction_Check(float Val);
	void IN_AimingAction();
	void OUT_AimingAction();
	void AttackAction();
	
	int AimingActionCheck = 0;

	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;

	
	UPROPERTY(EditAnywhere)
		USpringArmComponent* OurCameraSpringArm;
	//Ÿ�پ� ����: 160.0
	//���� ������: 0.0 / 55.0 / 55.0
	//Ÿ�� ������: 0.0 / 0.0 / 0.0
	
	//UCameraComponent* OurCamera;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;


	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
		EAniState AniState = EAniState::Idle;


	//��Ÿ�� �ִϸ��̼� �������Ʈ�� Map��������
	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		TMap<EAniState, class UAnimMontage*> AllAnimations;

	UFUNCTION()
		void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	float Speed = 1000.0f;

private:
	class UPlayer_AnimInstance* GlobalAnimInstance = nullptr;
};


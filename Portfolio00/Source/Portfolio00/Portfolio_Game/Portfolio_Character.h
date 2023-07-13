// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Portfolio_Enum.h"
#include "Portfolio_Character.generated.h"

UCLASS()
class PORTFOLIO00_API APortfolio_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APortfolio_Character();

	// 블루프린트에서 호출하게 하려면 기본적으로 public이어야 합니다.
	UFUNCTION(BlueprintCallable)
		void AnimationTick();

	// UFUNCTION()
	// void MontageEnd(UAnimMontage* Anim, bool _Inter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame

		// Called to bind functionality to input

	void AttackAction();


	void MoveRight(float Val);
	void MoveForward(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;

	bool AxisJump = false;


	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
		TPSAniState AniState = TPSAniState::Idle;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		TMap<TPSAniState, class UAnimMontage*> AllAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* WeaponMesh;

	// 블루프린트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UStaticMesh*> WeaponArrays;
};

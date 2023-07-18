// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Portfolio_Enums.h"
#include "Portfolio_Character.generated.h"

UCLASS()
class PORTFOLIO01_API APortfolio_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APortfolio_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AttackAction();

	void MoveLeft(float Val);
	void MoveRight(float Val);
	void MoveForward(float Val);
	void MoveBackward(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;


	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
		EAniState AniState = EAniState::Idle;

};

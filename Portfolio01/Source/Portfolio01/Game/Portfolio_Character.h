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

	void MoveRight(float Val);
	void MoveForward(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	//void AttackAction();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		float BaseLookUpRate;


	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
		EAniState AniState = EAniState::Idle;


	//��Ÿ�� �ִϸ��̼� �������Ʈ�� Map��������
	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
		TMap<EAniState, class UAnimMontage*> AllAnimations;

};

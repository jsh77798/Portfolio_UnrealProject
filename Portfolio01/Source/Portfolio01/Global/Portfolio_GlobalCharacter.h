// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Global/Portfolio_GlobalAnimInstance.h>
#include "Portfolio_GlobalCharacter.generated.h"

UCLASS()
class PORTFOLIO01_API APortfolio_GlobalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APortfolio_GlobalCharacter();

	void SetHP(int _HP)
	{
		HP -= _HP;
	}

	void AddHP(int _HP)
	{
		HP += _HP;
	}

	int GetHP()
	{
		return HP;
	}

	int GetAniState()
	{
		return AniState;
	}

	template<typename EnumType>
	EnumType GetAniState()
	{
		return static_cast<EnumType>(AniState);
	}

	template<typename EnumType>
	void SetAniState(EnumType _AniState)
	{
		AniState = static_cast<int>(_AniState);
	}

	void SetAniState(int _AniState)
	{
		AniState = _AniState;
	}

	class UPortfolio_GlobalAnimInstance* GetGlobalAnimInstance()
	{
		return Portfolio_GlobalAnimInstance;
	}

	template<typename EnumType>
	class UAnimMontage* GetAnimMontage(EnumType _Index)
	{
		return GetAnimMontage(static_cast<int>(_Index));
	}

	class UAnimMontage* GetAnimMontage(int _Index)
	{
		if (false == AllAnimations.Contains(_Index))
		{
			return nullptr;
		}

		return AllAnimations[_Index];
	}

	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& _MapAnimation)
	{
		for (TPair<EnumType, UAnimMontage*> Pair : _MapAnimation)
		{
			AllAnimations.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
	}

	UFUNCTION()
		void PushComponent(UActorComponent* _Component)
	{
		MgrComponent.Add(_Component);
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	template<typename EnumType>
	void PushAnimation(EnumType _Index, class UAnimMontage* _Montage)
	{
		PushAnimation(static_cast<int>(_Index), _Montage);
	}

	void PushAnimation(int _Index, class UAnimMontage* _Montage)
	{
		if (true == AllAnimations.Contains(_Index))
		{
			return;
		}

		AllAnimations.Add(_Index, _Montage);
	}

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
		void OverLap(class UPrimitiveComponent* OverlappedComponent,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);


	virtual void Damage(AActor* _Actor) {}

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UActorComponent*> MgrComponent;


private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int AniState = 0;

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<int, class UAnimMontage*> AllAnimations;

	//UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	//	TMap<AIState, class UAnimMontage*> AllAnimations;

	class UPortfolio_GlobalAnimInstance* Portfolio_GlobalAnimInstance = nullptr;

	UPROPERTY(Category = "GlobalChracterValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int HP = 1000;
};

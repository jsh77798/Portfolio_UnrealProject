// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_AnimInstance.h"
#include "Portfolio_Character.h"

/*
void UPlayer_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// ���ڽ��� �ִ��ν��Ͻ��Դϴ�.
	OnMontageEnded.AddDynamic(this, &UPlayer_AnimInstance::MontageEnd);

	// ���̵�       => ����
	// �귣�� �ƿ�     ������

	//OnMontageBlendingOut.AddDynamic(this, &UPlayer_AnimInstance::MontageEnd);

	// ���� ���� ���͸� ���⼭ �����ɴϴ�.
	// TPSĳ���Ϳ��� �� ������ �����.

	APortfolio_Character* Chracter = Cast<APortfolio_Character>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AllAnimations = Chracter->AllAnimations;
}

// �����Ҷ� �ѹ� ������Ʈ�� �����ֹǷ�.
void UPlayer_AnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	if (0 == AllAnimations.Num())
	{
		return;
	}

	APortfolio_Character* Chracter = Cast<APortfolio_Character>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AniState = Chracter->AniState;

	class UAnimMontage* Montage = AllAnimations[AniState];

	if (nullptr == Montage)
	{
		return;
	}

	if (false == Montage_IsPlaying(Montage))
	{
		Montage_Play(Montage, 1.0f);
	}
}

void UPlayer_AnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{
	//TSubclassOf<UPlayer_AnimInstance> Inst = UPlayer_AnimInstance::StaticClass();

	APortfolio_Character* Chracter = Cast<APortfolio_Character>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	// Anim ����� ��Ÿ��


	if (AllAnimations[EAniState::W_Attack] == Anim)
	{
		if (AniState == EAniState::Idle)
		{
			return;
			//AniState = EAniState::Idle;
			//Chracter->AniState = AniState;
			//Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
		}
		else
		{

			AniState = EAniState::W_Aiming;
			Chracter->AniState = AniState;
			Montage_Play(AllAnimations[EAniState::W_Aiming], 1.0f);
		}
	}


	if (AllAnimations[EAniState::CrouchOn] == Anim)
	{
		if (AniState == EAniState::Crouch_Idle)
		{
			return;
		}
		else
		{
			AniState = EAniState::Crouch_Idle;
			Chracter->AniState = AniState;
			Montage_Play(AllAnimations[EAniState::Crouch_Idle], 1.0f);
		}
	}

	if (AllAnimations[EAniState::CrouchOff] == Anim)
	{
		if (AniState == EAniState::Idle)
		{
			return;
		}
		else
		{

			AniState = EAniState::Idle;
			Chracter->AniState = AniState;
			Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
		}
	}
}
*/
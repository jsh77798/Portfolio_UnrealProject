// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_GlobalAnimInstance.h"
#include "Global/Portfolio_GlobalCharacter.h"
#include <Global/Data/MonsterData.h>
#include "Portfolio_Global.h"

void UPortfolio_GlobalAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OnMontageBlendingOut.AddDynamic(this, &UPortfolio_GlobalAnimInstance::MontageEnd);
}

// �����Ҷ� �ѹ� ������Ʈ�� �����ֹǷ�.
void UPortfolio_GlobalAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);
	
	if (0 == AllAnimations.Num())
	{
		return;
	}

	APortfolio_GlobalCharacter* Chracter = Cast<APortfolio_GlobalCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AniState = Chracter->GetAniState();

	class UAnimMontage* Montage = AllAnimations[AniState];

	if (nullptr == Montage)
	{
		return;
	}

	// ����1. ��Ÿ�� ����� ������.
	// ����2. ������ �̹� ����� ��Ÿ�ִ�.
	// ����3. ��Ÿ�ְ� ������.
	if (false == Montage_IsPlaying(Montage))
	{
		//if (Montage == CurMontage && -1 != DefaultAniState && false == Montage->bLoop)
		//{
		//	Montage = AllAnimations[DefaultAniState];
		//}

		CurMontage = Montage;
		Montage_Play(Montage, 1.0f);
	}
}

void UPortfolio_GlobalAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{

}

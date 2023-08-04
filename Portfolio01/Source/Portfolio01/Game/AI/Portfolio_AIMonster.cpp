// Fill out your copyright notice in the Description page of Project Settings.


#include "Portfolio_AIMonster.h"
#include <Global/Portfolio_GameInstance.h>
#include <Global/Data/MonsterData.h>

#include "BehaviorTree/BlackboardComponent.h"

void APortfolio_AIMonster::BeginPlay()
{
	UPortfolio_GameInstance * Inst = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();

	if (nullptr != Inst)
	{

		CurMonsterData = Inst->GetMonsterData(DataName);

		//SetAllAnimation(CurMonsterData->MapAnimation);
		//SetAniState(AIState::DEATH);

	}

	Super::BeginPlay();


	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIState"), static_cast<uint8>(AIState::IDLE));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 1000.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 130.0f);
	FVector _Pos = GetActorLocation();
	GetBlackboardComponent()->SetValueAsVector(TEXT("PrePos"), _Pos);

}


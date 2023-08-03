// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AI/BTTask_DEATH.h"

UBTTask_DEATH::UBTTask_DEATH()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_DEATH::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::DEATH);
	GetGlobalCharacter(OwnerComp)->Destroy();

	return EBTNodeResult::Type::InProgress;
}
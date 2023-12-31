// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AI/BTTask_STUN.h"
#include <Global/Portfolio_GlobalCharacter.h>
#include <Game/AI/Portfolio_AIController.h>
#include <Game/AI/Portfolio_MonsterEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "Kismet/GameplayStatics.h"
#include "Math/NumericLimits.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTTask_STUN::UBTTask_STUN()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_STUN::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::STUN); // 리소스를 구한후 STUN 애니메이션으로 변경

	ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_STUN::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	if (true == IsDeathCheck(OwnerComp))
	{
		SetStateChange(OwnerComp, AIState::DEATH);
		return;
	}

	if (0.5f <= GetStateTime(OwnerComp))
	{
		// 지역변수로 랜덤을 이용하는것.
		FRandomStream Stream;
		// 알아서 시간과 같은 변하는 수를 시드값으로 삼는다.
		Stream.GenerateNewSeed();

		int Value = Stream.RandRange(0, 1);

		// UE_LOG(LogTemp, Error, TEXT("%S(%u)> %d"), __FUNCTION__, __LINE__, Value);

		ResetStateTime(OwnerComp);

		//if (Value == 0)
		//{
		SetStateChange(OwnerComp, AIState::MOVE);
		return;
		//}

		// 그럼 순찰할까?
		// 그냥 5초간 다시 대기하자.
		// SetStateChange(OwnerComp, AIState::MOVE);
		// return;
	}

	AActor* ResultActor = GetTargetSearch(OwnerComp);

	if (nullptr != ResultActor)
	{
		GetBlackboardComponent(OwnerComp)->SetValueAsObject(TEXT("TargetActor"), ResultActor);
		SetStateChange(OwnerComp, AIState::MOVE);
		return;
	}

	//핵심은 플레이어를 찾아내는것.
	// GetGlobalCharacter(OwnerComp)->GetLevel()->;
	return;
}

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
	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::STUN); // ���ҽ��� ������ STUN �ִϸ��̼����� ����

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
		// ���������� ������ �̿��ϴ°�.
		FRandomStream Stream;
		// �˾Ƽ� �ð��� ���� ���ϴ� ���� �õ尪���� ��´�.
		Stream.GenerateNewSeed();

		int Value = Stream.RandRange(0, 1);

		// UE_LOG(LogTemp, Error, TEXT("%S(%u)> %d"), __FUNCTION__, __LINE__, Value);

		ResetStateTime(OwnerComp);

		//if (Value == 0)
		//{
		SetStateChange(OwnerComp, AIState::MOVE);
		return;
		//}

		// �׷� �����ұ�?
		// �׳� 5�ʰ� �ٽ� �������.
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

	//�ٽ��� �÷��̾ ã�Ƴ��°�.
	// GetGlobalCharacter(OwnerComp)->GetLevel()->;
	return;
}

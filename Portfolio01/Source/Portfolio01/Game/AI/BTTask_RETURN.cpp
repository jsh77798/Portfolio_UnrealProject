// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AI/BTTask_RETURN.h"
#include <Global/Portfolio_GlobalCharacter.h>
#include <Global/Portfolio_Global.h>
#include <Game/AI/Portfolio_MonsterEnums.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "BTTask_IDLE.h"
#include "Portfolio_AIMonster.h"
#include "GameFramework/CharacterMovementComponent.h"


UBTTask_RETURN::UBTTask_RETURN()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_RETURN::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::RETURN);

	UCharacterMovementComponent* MoveCom = Cast<UCharacterMovementComponent>(GetGlobalCharacter(OwnerComp)->GetMovementComponent());

	if (nullptr != MoveCom)
	{
		MoveCom->MaxWalkSpeed = 100.0f;
	}

	return EBTNodeResult::Type::InProgress;
}


void UBTTask_RETURN::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds)
{
	if (true == IsDeathCheck(OwnerComp))
	{
		SetStateChange(OwnerComp, AIState::DEATH);
		return;
	}

	if (true == IsStunCheck(OwnerComp))
	{
		SetStateChange(OwnerComp, AIState::STUN);
		return;
	}

	if (true == IsAttackCheck(OwnerComp))
	{
		SetStateChange(OwnerComp, AIState::MOVE);
		return;
	}

	PrePos = GetBlackboardComponent(OwnerComp)->GetValueAsVector(TEXT("PrePos"));
	PrePos.Z = 0.0f;

	//if (nullptr != TargetActor)
	//{
	//	SetStateChange(OwnerComp, AIState::MOVE);
	//	return;
	//}

	{

		FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		ThisPos.Z = 0.0f;

		FVector Dir = PrePos - ThisPos;
		Dir.Normalize();

		FVector OtherForward = GetGlobalCharacter(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 500.0f * DelataSeconds });
			GetGlobalCharacter(OwnerComp)->AddActorWorldRotation(Rot);
		}
		else
		{
			FRotator Rot = Dir.Rotation();
			GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		}

		//if (Dir.X == 0.0f && Dir.Y == 0.0f)
		//{
		//	SetStateChange(OwnerComp, AIState::IDLE);
		//	return;
		//}
	}



	{
		FVector PawnPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
		FVector TargetPos = PrePos;
		PawnPos.Z = 0.0f;
		TargetPos.Z = 0.0f;

		FVector Dir = TargetPos - PawnPos;

		GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);
		//GetGlobalCharacter(OwnerComp)->SetActorRotation(Dir.Rotation());


		GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);

		if (10.0f >= Dir.Size())
		{
			SetStateChange(OwnerComp, AIState::IDLE);
			return;
		}

	}

}


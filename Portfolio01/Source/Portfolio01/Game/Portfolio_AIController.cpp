// Fill out your copyright notice in the Description page of Project Settings.


#include "Portfolio_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include ""

APortfolio_AIController::APortfolio_AIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));;
}

// ���� ���� 
// ĳ���͸�������� �������� ��Ʈ�ѷ��� ��ĳ���͸� �����Ұ��̴�.
void APortfolio_AIController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	if (nullptr != BehaviorTreeComponent && true == BehaviorTreeComponent->IsValidLowLevel())
	{
		//AAICharacter* AIPawn = Cast<AAICharacter>(_InPawn);
		//UBehaviorTree* BehaviorTree = AIPawn->GetBehaviorTree();
		//BehaviorTreeComponent->StartTree(*BehaviorTree);

		// ��ŸƮ ������ �̹� �����尡 ���õǾ��ִٰ� �����ϰ� �����Ѵ�.
		// BehaviorTreeComponent->StartLogic();

		// BehaviorTreeComponent->StartTree();
	}

	// �ൿƮ�� ������ ���� �־��ְ�
	// BehaviorTreeComponent

	// �ൿƮ������ ������ �������� ���� �־��ָ�
	// BlackboardComponent

	// ���� �����϶�� �������Ʈ�� C++ ����� �����߸� �����մϴ�.
}


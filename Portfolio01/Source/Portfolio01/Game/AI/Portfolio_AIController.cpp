// Fill out your copyright notice in the Description page of Project Settings.


#include "Portfolio_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AICharacter.h"

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
		AAICharacter* AIPawn = Cast<AAICharacter>(_InPawn);

		UBehaviorTree* BehaviorTree = AIPawn->GetBehaviorTree();
		//BehaviorTreeComponent->StartTree(*BehaviorTree);

		if (nullptr == BehaviorTree || false == BehaviorTree->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BehaviorTree || false == BehaviorTree->IsValidLowLevel())"), __FUNCTION__, __LINE__);
			return;
		}
	    BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);

	    BlackboardComponent->SetValueAsObject(TEXT("SelfActor"), _InPawn);

	    BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
	
}


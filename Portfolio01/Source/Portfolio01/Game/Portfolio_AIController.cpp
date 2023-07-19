// Fill out your copyright notice in the Description page of Project Settings.


#include "Portfolio_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICharacter.h"

APortfolio_AIController::APortfolio_AIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));;
}

// 빙의 순간 
// 캐릭터만들어지고 이제부터 컨트롤러가 이캐릭터를 조작할것이다.
void APortfolio_AIController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	if (nullptr != BehaviorTreeComponent && true == BehaviorTreeComponent->IsValidLowLevel())
	{
		AAICharacter* AIPawn = Cast<AAICharacter>(_InPawn);

		UBehaviorTree* BehaviorTree = AIPawn->GetBehaviorTree();
		BehaviorTreeComponent->StartTree(*BehaviorTree);

		//BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlakboardAsset)

		// 스타트 로직은 이미 블랙보드가 세팅되어있다고 생각하고 동작한다.
		// BehaviorTreeComponent->StartLogic();
		// BehaviorTreeComponent->StartTree();
	}

	// 행동트리 에셋을 집어 넣어주고
	// BehaviorTreeComponent

	// 행동트리들이 공유할 데이터을 집어 넣어주면
	// BlackboardComponent

	// 직접 동작하라고 블루프린트나 C++ 명령을 내려야만 동작합니다.
}


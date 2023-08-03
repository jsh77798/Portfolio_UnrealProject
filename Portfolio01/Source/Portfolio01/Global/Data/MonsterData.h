#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include <Game/Portfolio_Enums.h>
#include "MonsterData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct PORTFOLIO01_API FMonsterData : public FTableRowBase
{
	GENERATED_BODY()

	FMonsterData(){}
	~FMonsterData(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	    int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ATT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		class UBehaviorTree* AI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TMap<AIState, class UAnimMontage*> MapAnimation;
};

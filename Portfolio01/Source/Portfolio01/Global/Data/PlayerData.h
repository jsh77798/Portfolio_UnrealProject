#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "PlayerData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct PORTFOLIO01_API FPlayerData : public FTableRowBase
{
	GENERATED_BODY()

		FPlayerData() {}
	~FPlayerData() {}

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	//	int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ATT;

};

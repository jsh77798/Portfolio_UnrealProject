#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "TileData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct PORTFOLIO01_API FTileData : public FTableRowBase
{
	GENERATED_BODY()

		FTileData() {}
	~FTileData() {}

	// �𸮾� �����Ϳ��� DT_PlayerData���̺� �� �ش缳������ �����ϰ� ������ �� �ִ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int RANGE_ATT;
};

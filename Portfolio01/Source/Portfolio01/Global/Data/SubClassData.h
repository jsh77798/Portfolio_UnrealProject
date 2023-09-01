#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "SubClassData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct PORTFOLIO01_API FSubClassData : public FTableRowBase
{
	GENERATED_BODY()

	FSubClassData() {}
	~FSubClassData() {}

	// �𸮾� �����Ϳ��� DT_SubClassData���̺� �� �ش缳������ �����ϰ� ������ �� �ִ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<UObject> Object;
};
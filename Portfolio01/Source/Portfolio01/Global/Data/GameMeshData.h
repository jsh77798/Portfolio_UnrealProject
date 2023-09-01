#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "GameMeshData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct PORTFOLIO01_API FGameMeshData : public FTableRowBase
{
	GENERATED_BODY()

		FGameMeshData() {}
	~FGameMeshData() {}

	// �𸮾� �����Ϳ��� DT_GameMeshData���̺� �� �ش缳������ �����ϰ� ������ �� �ִ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		class UStaticMesh* Mesh;
};

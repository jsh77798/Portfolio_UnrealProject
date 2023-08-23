// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Portfolio_GlobalObject.h"
#include "Portfolio_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO01_API UPortfolio_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPortfolio_GameInstance();
	~UPortfolio_GameInstance();

	TSubclassOf<UObject> GetSubClass(FName _Name);

	UStaticMesh* GetMesh(FName _Name);

	struct FMonsterData* GetMonsterData(FName _Name);

	struct FPlayerData* GetPlayerData(FName _Name);

	void GetGameData(int _Data);
	int SetGameData();
	int GameAtt;

private:
	UPROPERTY()
	UDataTable* SubClassData;

	UPROPERTY()
	UDataTable* MeshDatas;

	UPROPERTY()
	UDataTable* MonsterDatas;

	UPROPERTY()
	UDataTable* PlayerDatas;

	TArray<UStaticMesh*> Arrmesh;
};

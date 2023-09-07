// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Portfolio_Global.h"
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

	// Get...�Լ�-> �ش� ������ ��������
	UStaticMesh* GetMesh(FName _Name);

	const struct FItemData* GetRandomItemData();

	TSubclassOf<UObject> GetSubClass(FName _Name);

	struct FMonsterData* GetMonsterData(FName _Name);

	struct FPlayerData* GetPlayerData(FName _Name);

	struct FTileData* GetTileData(FName _Name);

	// GetGameData�Լ�-> ���� ���ݷ� ��������, SetGameData�Լ�-> ���� ���ݷ� ����
	void GetGameData(int _Data, AActor* Owner);
	int SetGameData();
	int GameAtt = 0;
	AActor* _Owner = nullptr;

private:
	// SubClassData ���̺�
	UPROPERTY()
	UDataTable* SubClassData;

	// MeshData ���̺�
	UPROPERTY()
	UDataTable* MeshDatas;

	// ItemData ���̺�
	UPROPERTY()
	UDataTable* ItemDatas;

	TArray<const struct FItemData*> ItemDataRandoms;

	// MonsterData ���̺�
	UPROPERTY()
	UDataTable* MonsterDatas;

	// PlayerData ���̺�
	UPROPERTY()
	UDataTable* PlayerDatas;

	// TileData ���̺�
	UPROPERTY()
	UDataTable* TileDatas;

	TArray<UStaticMesh*> Arrmesh;

};

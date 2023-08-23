// Fill out your copyright notice in the Description page of Project Settings.


#include "Portfolio_GameInstance.h"
#include <Global/Data/GameMeshData.h>
#include <Global/Data/SubClassData.h>
#include <Global/Data/MonsterData.h>
#include <Global/Data/PlayerData.h>
#include "Portfolio_Global.h"


UPortfolio_GameInstance::UPortfolio_GameInstance()
{
	
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/Global/Data/DT_GameMeshData.DT_GameMeshData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			MeshDatas = DataTable.Object;

			TArray<FName> ArrayName = MeshDatas->GetRowNames();

			for (size_t i = 0; i < ArrayName.Num(); i++)
			{

				FGameMeshData* FindTable = MeshDatas->FindRow<FGameMeshData>(ArrayName[i], ArrayName[i].ToString());

				int a = 0;
			}
		}
	}
	
	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/Global/Data/DT_SubClassData.DT_SubClassData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			SubClassData = DataTable.Object;
		}
	}
	

	{
	
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/Character_Monster/DT_MonsterData.DT_MonsterData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			MonsterDatas = DataTable.Object;
		}

	}


	{

		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BluePrint/Character_Player/DT_PlayerData.DT_PlayerData'");
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			PlayerDatas = DataTable.Object;
		}

	}

	UPortfolio_Global::MainRandom.GenerateNewSeed();
}

UPortfolio_GameInstance::~UPortfolio_GameInstance()
{

}

TSubclassOf<UObject> UPortfolio_GameInstance::GetSubClass(FName _Name)
{
	if (nullptr == SubClassData)
	{
		return nullptr;
	}

	FSubClassData* FindTable = SubClassData->FindRow<FSubClassData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable->Object;

}

UStaticMesh* UPortfolio_GameInstance::GetMesh(FName _Name)
{
	if (nullptr == MeshDatas)
	{
		return nullptr;
	}

	FGameMeshData* FindTable = MeshDatas->FindRow<FGameMeshData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable->Mesh;
}


FMonsterData* UPortfolio_GameInstance::GetMonsterData(FName _Name)
{
	if (nullptr == MonsterDatas)
	{
		return nullptr;
	}

	FMonsterData* FindTable = MonsterDatas->FindRow<FMonsterData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

FPlayerData* UPortfolio_GameInstance::GetPlayerData(FName _Name)
{
	if (nullptr == PlayerDatas)
	{
		return nullptr;
	}

	FPlayerData* FindTable = PlayerDatas->FindRow<FPlayerData>(_Name, _Name.ToString());

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable;
}

void UPortfolio_GameInstance::GetGameData(int _Data, AActor* Owner)
{
	if (_Owner == Owner)
	{
	   GameAtt = 0;
	   GameAtt = _Data;
	}
	else 
	{
		_Owner = Owner;
		GameAtt = 0;
	}
}

int UPortfolio_GameInstance::SetGameData()
{
	return GameAtt;
	GameAtt = 0;
}

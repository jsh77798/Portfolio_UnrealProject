// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Portfolio_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO00_API UPortfolio_GameInstance : public UGameInstance
{
	GENERATED_BODY()


public:
	UPortfolio_GameInstance();
	~UPortfolio_GameInstance();

	UStaticMesh* GetMesh(FName _Name);

private:
	UPROPERTY()
		UDataTable* MeshDatas;

	TArray<UStaticMesh*> Arrmesh;
};

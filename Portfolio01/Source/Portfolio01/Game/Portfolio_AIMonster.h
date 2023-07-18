// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
#include <Global/Data/MonsterData.h>
#include "Portfolio_AIMonster.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO01_API APortfolio_AIMonster : public AAICharacter
{
	GENERATED_BODY()

	const FMonsterData* CurMonsterData;
};

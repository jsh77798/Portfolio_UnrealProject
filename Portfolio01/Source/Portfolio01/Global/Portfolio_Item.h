// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Global/Data/ItemData.h>
#include "Portfolio_Item.generated.h"

UCLASS()
class PORTFOLIO01_API APortfolio_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortfolio_Item();
	//�� ������ ������
	UFUNCTION(BlueprintCallable)
	void Take(AActor* _Actor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:	
	const struct FItemData* Data = nullptr;
};

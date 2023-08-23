// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Portfolio_Tile.generated.h"

UCLASS()
class PORTFOLIO01_API APortfolio_Tile : public AActor
{
	GENERATED_BODY()

	struct FPlayerData* CurPlayerData;

	UPROPERTY(Category = "ATT", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FName AttDataName = "NONE";

	//int Att = 0;

public:	
	// Sets default values for this actor's properties
	
	APortfolio_Tile();

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float Speed = 3000.0f;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float DeathTime = 5.0f;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> DeathCreateObject = nullptr;

	UFUNCTION()
		FORCEINLINE USphereComponent* GetSphereComponent()
	{
		return SphereComponent;
	}

	//class APortfolio_GlobalCharacter* ATT = nullptr;
	//int ShutGunAtt = 1000;


protected:
	// Called when the game starts or when spawned
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:
	//Called every frame
	UFUNCTION()
		void DestroyProjectile(AActor* _Destroy);

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent = nullptr;
};

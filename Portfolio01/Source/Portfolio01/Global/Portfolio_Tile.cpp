// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_Tile.h"
#include <Global/Portfolio_GameInstance.h>
#include <Global/Data/PlayerData.h>
#include <Global/Portfolio_GlobalCharacter.h>

// Sets default values
APortfolio_Tile::APortfolio_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionProfileName(TEXT("NoCollision"), true);
	SphereComponent->ComponentTags.Add(FName("Damage"));
}


// Called when the game starts or when spawned
void APortfolio_Tile::BeginPlay()
{
	//PlayerData에 Att값을 가져와 사용한다
	UPortfolio_GameInstance* Inst = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();
	if (nullptr != Inst)
	{
		CurPlayerData = Inst->GetPlayerData(AttDataName);
	}
	PlayerAtt = CurPlayerData->ATT;


	Super::BeginPlay();

	OnDestroyed.AddDynamic(this, &APortfolio_Tile::DestroyProjectile);
	// SphereComponent->SetCollisionProfileName(TEXT("MonsterAttack"), true);
}

void APortfolio_Tile::DestroyProjectile(AActor* _Destroy)
{
	if (nullptr == DeathCreateObject)
	{
		return;
	}

	AActor* Actor = GetWorld()->SpawnActor<AActor>(DeathCreateObject);

	Actor->SetActorLocation(GetActorLocation());
	Actor->SetActorRotation(GetActorRotation());
}

// Called every frame
void APortfolio_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeathTime -= DeltaTime;

		if (DeathTime < 0.0f)
		{
			Destroy();
			return;
		}


		//if (DeltaTime >= 0.01f)
		//{

     	PlayerAtt -= RangeAtt * DeltaTime * 0.1;
		//PlayerAtt에 값을 저장하여, 적중시 HP계산할때 사용한다

		GetData(PlayerAtt);

		    //UPortfolio_GameInstance* Inst = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();
			//Inst->GetGameData(PlayerAtt);
		//}
	

	AddActorWorldOffset(GetActorForwardVector() * DeltaTime * Speed);
}

void APortfolio_Tile::GetData(int _Data) 
{
	Data = _Data;

	UPortfolio_GameInstance* Inst = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();
	Inst->GetGameData(Data, this);
	
}

int APortfolio_Tile::SetData() 
{
	return Data;
}

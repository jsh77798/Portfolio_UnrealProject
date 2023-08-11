// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_Tile.h"

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

	AddActorWorldOffset(GetActorForwardVector() * DeltaTime * Speed);
}


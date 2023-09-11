// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_Tile.h"
#include <Global/Portfolio_GameInstance.h>
#include <Global/Data/PlayerData.h>
#include <Global/Data/TileData.h>
#include <Global/Portfolio_GlobalCharacter.h>
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Components/SphereComponent.h"


// Sets default values
APortfolio_Tile::APortfolio_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionProfileName(TEXT("NoCollision"), true);
	SphereComponent->ComponentTags.Add(FName("Damage"));
	SphereComponent->OnComponentHit.AddDynamic(this, &APortfolio_Tile::OnHit);



	
	//UStaticMeshComponent* ProjectileMovement = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMovement"));
	//ProjectileMovement->UpdatedComponent = SphereComponent;
	/*
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	*/
}


// Called when the game starts or when spawned
void APortfolio_Tile::BeginPlay()
{
	Super::BeginPlay();

	//PlayerAtt = CurPlayerData->ATT;

	GetLocation = GetActorLocation();

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

     	RangeAtt += 100 * DeltaTime;

		SetAttRange(RangeAtt);

	    AddActorWorldOffset(GetActorForwardVector() * DeltaTime * Speed);

		//if (DeltaTime >= 0.01f)
		//{

		//PlayerAtt에 값을 저장하여, 적중시 HP계산할때 사용한다

		//GetData(PlayerAtt);

		    //UPortfolio_GameInstance* Inst = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();
			//Inst->GetGameData();
		//}
}

void APortfolio_Tile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		// Calculate the distance between the bullet and the hit location.
		
		float Distance = (Hit.ImpactPoint - GetActorLocation()).Size();
		//float Impact = (Hit.ImpactPoint).Size();
		// Calculate damage based on distance.
		float Damage = FMath::Lerp(1.0f, MaxDamageDistance, Distance) * DamagePerUnit;

		// Apply damage to the hit actor (assuming it's an ACharacter).
		APortfolio_GlobalCharacter* HitCharacter = Cast<APortfolio_GlobalCharacter>(OtherActor);
		if (HitCharacter)
		{
			HitCharacter->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
			int a = 0;
		}

		// Destroy the bullet.
		Destroy();
	}
}

















/*

int APortfolio_Tile::SetData() 
{
	return Data;
}
*/



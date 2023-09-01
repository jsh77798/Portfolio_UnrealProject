// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_GlobalCharacter.h"
#include <Global/Portfolio_GameInstance.h>
#include <Global/Data/PlayerData.h>
#include <Global/Data/TileData.h>
#include <Global/Portfolio_Tile.h>
#include "Components/CapsuleComponent.h"

// Sets default values
APortfolio_GlobalCharacter::APortfolio_GlobalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortfolio_GlobalCharacter::BeginPlay()
{
	Super::BeginPlay();


	Portfolio_GlobalAnimInstance = Cast<UPortfolio_GlobalAnimInstance>(GetMesh()->GetAnimInstance());

	Portfolio_GlobalAnimInstance->AllAnimations = AllAnimations;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APortfolio_GlobalCharacter::OverLap);
}

// Called every frame
void APortfolio_GlobalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APortfolio_GlobalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APortfolio_GlobalCharacter::OverLap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	//Damage Tag�� ���˽� ���
	if (true == OtherComp->ComponentHasTag(TEXT("Damage")))
	{
		int ATT = 0;
		int RANGEATT = 0;

		// -�߰��۾�-
		// �Ʒ� �ڵ带 Portfolio_Tile�� �̵�
		// 
		//APortfolio_Tile* Tile = NewObject<APortfolio_Tile>();
		UPortfolio_GameInstance* Tile = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();
		if (nullptr != Tile)
		{
			//CurData = Cast<APortfolio_Tile>(Tile->GetTileData(RangeAttDataName));
			CurData = Tile->GetTileData(RangeAttDataName);
		}
		RANGEATT = CurData->RANGE_ATT;

		ATT = Att; // PlayerAtt�� GlobalCharacter.h�� �Լ��� ���� Character���� �÷��̾��� ������ ���� �����´�
		ATT -= RANGEATT;

		if (100 >= ATT)
		{
			ATT = 100;
		}
		HP -= ATT;
	}
}

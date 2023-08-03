// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_GlobalCharacter.h"

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


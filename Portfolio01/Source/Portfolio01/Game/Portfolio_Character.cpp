// Fill out your copyright notice in the Description page of Project Settings.


#include "Portfolio_Character.h"

// Sets default values
APortfolio_Character::APortfolio_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortfolio_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortfolio_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APortfolio_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


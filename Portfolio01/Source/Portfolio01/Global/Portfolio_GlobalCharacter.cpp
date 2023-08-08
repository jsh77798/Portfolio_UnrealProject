// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_GlobalCharacter.h"
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
	// ���� HP�� ������� �ִٸ�.
	// ���⼭ ��� 
	// ���� ������ ������ Hp�� ���̶�� �Ҽ� ������
	// �������ϱ�?
	// �Ѿ��ϱ�?
	// Tag

	if (true == OtherComp->ComponentHasTag(TEXT("Damage")))
	{
		// ��밡 ������� �����ٸ� ��� �˾ƿð��̳�?

		HP -= 1;
		// Damage(OtherActor);
	}
}
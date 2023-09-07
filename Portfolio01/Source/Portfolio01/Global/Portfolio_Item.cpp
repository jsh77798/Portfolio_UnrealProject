// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_Item.h"
#include "Global/Portfolio_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <UI/Portfolio_Widget_Inventory.h>
#include <UI/Portfolio_HUD.h>

// Sets default values
APortfolio_Item::APortfolio_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortfolio_Item::BeginPlay()
{
	Super::BeginPlay();
	// 
	UPortfolio_GameInstance* GameInstance = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();
	Data = GameInstance->GetRandomItemData();


	if (nullptr != Data->Mesh)
	{
		// ���ο� static�Ž� ������Ʈ�� �ִ��� ã��
		UActorComponent* Component = GetComponentByClass(UStaticMeshComponent::StaticClass());
		UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component);
		if (nullptr != StaticMesh)
		{
			StaticMesh->SetStaticMesh(Data->Mesh);
		}
	}
}

// Called every frame
void APortfolio_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortfolio_Item::Take(AActor* _Actor)
{
	// �� �������� �Դ°� ������ ����� �� ������ �ɰ����� �÷��̾��°� Ȯ���ϸ�.
	// ������
	// UInventoryUserWidget* WidGet;
	// dlrjf 

	// static�� ����
	// �޸� ũ������ ���� �ִ�.

	// ���� ���� �� GameMode�Դϴ�.
	// 
	// UInventoryUserWidget::InvenWidget;

	// ����� �ȳ��´ٰ� Ȯ���� �޾ƾ� �Ѵ�.
	// ������ �Ծ����� �÷��̾��� �����Ѵ�.
	// �̰� ������ �� �÷��̾ �ƴҼ� �ִٴ� �����Ͽ�.

	// �κ��丮�� �����ͼ� �κ��丮�� �־������.

	APlayerController* Con = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APortfolio_HUD* HUD = Con->GetHUD<APortfolio_HUD>();
	if (nullptr == HUD)
	{
		// �κ��丮�� ���� ���̴�.
		return;
	}

	UPortfolio_Widget_Main* WidGet = HUD->GetMainWidget();
	if (nullptr == WidGet)
	{
		return;
	}

	UWidget* InvenWidGet = WidGet->GetWidgetFromName(TEXT("WBP_UI_Inventory"));
	UPortfolio_Widget_Inventory* Inventory = Cast<UPortfolio_Widget_Inventory>(InvenWidGet);

	if (nullptr == Inventory)
	{
		return;
	}

	Inventory->AddGameItem(Data);

	// Inventory->AddInvenItem()

	int a = 0;

}
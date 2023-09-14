// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portfolio_Widget_Inventory.h"
#include "Components/TileView.h"
#include <Global/Portfolio_GameInstance.h>
#include "UI/Portfolio_Widget_InventorySlot.h"
#include "UI/InventoryItemData.h"


// ������ ���赵�� ����.
UPortfolio_Widget_Inventory* UPortfolio_Widget_Inventory::InvenWidget = nullptr;

// GameMode�ƴϸ� HUD�� �˰��ϴ°� ���� �����ϴ�.

// �����Ϳ� �������� �и��Ǿ�� �Ѵ�.
void UPortfolio_Widget_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	InvenWidget = this;

	InvenList = Cast<UTileView>(GetWidgetFromName(TEXT("InvenTileView")));

	// ���⿡�ٰ� �� �־���� �ϴ����� ���� ������� ����.

	for (size_t i = 0; i < 4; i++)
	{
		UInventoryItemData* ItemObject = NewObject<UInventoryItemData>();
		ItemObject->Data = nullptr;
		InvenList->AddItem(ItemObject);
	}

	UPortfolio_GameInstance* GameInstance = GetWorld()->GetGameInstance<UPortfolio_GameInstance>();

	const TArray<UObject*>& Items = InvenList->GetListItems();
	for (size_t i = 0; i < 3; i++)
	{
		UInventoryItemData* DataObject = Cast<UInventoryItemData>(Items[i]);
		DataObject->Data = GameInstance->GetRandomItemData();
	}
}

void UPortfolio_Widget_Inventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// ��Ŀ�� ������� ��ȯ�Ǿ ���� �������� �ǹ��Ѵ�.
	// ��Ŀ�� ������ ��Ȯ�ϰ� �������ڸ� �������Ʈ������ ��ȿ�ϴ�.
	// ȭ�鿡���� ��ǥ�踦 �������� ó���ѰͰ�.
	// MyGeometry.GetAbsolutePosition();

	// SetPositionInViewport(FVector2D{0, 0});

	// ƽ�� ���Դٴ°��� �κ��丮�� ������ �������� �� ��������ٴ� �̾߱��̴�.
	const TArray<UObject*>& Items = InvenList->GetListItems();
	for (size_t i = 0; i < Items.Num(); i++)
	{
		UInventoryItemData* DataObject = Cast<UInventoryItemData>(Items[i]);

		if (nullptr == DataObject->Widget)
		{
			// ���õɶ����� ��ٸ��� �ȴ�.
			continue;
		}

		UPortfolio_Widget_InventorySlot* SlotWidget = DataObject->Widget;
		SlotWidget->SlotDataCheck();
	}


}

void UPortfolio_Widget_Inventory::AddInvenItem(UObject* _Data, UUserWidget* _Widget)
{
	UPortfolio_Widget_InventorySlot* ItemSlotWidget = Cast<UPortfolio_Widget_InventorySlot>(_Widget);

	UInventoryItemData* InvenSlotData = Cast<UInventoryItemData>(_Data);

	if (nullptr == ItemSlotWidget)
	{
		return;
	}

	InvenSlotData->Widget = ItemSlotWidget;
	ItemSlotWidget->SetItemData(InvenSlotData);

	int a = 0;
}

void UPortfolio_Widget_Inventory::AddGameItem(const FItemData* Data)
{
	// ��ü ������
	const TArray<UObject*>& Items = InvenList->GetListItems();

	// �ߺ������� �����۵��� �ѹ��� ���캸��

	for (size_t i = 0; i < Items.Num(); i++)
	{
		UInventoryItemData* DataObject = Cast<UInventoryItemData>(Items[i]);

		if (nullptr == DataObject->Data)
		{
			// �����ͱ����� ������ �����ϴ�.
			// ����ִ� �κ��̴�.
			DataObject->Data = Data;
			return;
		}

		if (DataObject->Data == Data
			&& DataObject->Count < Data->StackMax)
		{
			++DataObject->Count;
			return;
		}
	}


	return;
}


void UPortfolio_Widget_Inventory::NewWidget(UUserWidget* _Widget)
{
	int a = 0;
}
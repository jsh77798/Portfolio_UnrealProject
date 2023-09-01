// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portfolio_Widget_InventorySlot.h"

void UPortfolio_Widget_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemIconBack = Cast<UImage>(GetWidgetFromName(TEXT("ItemBack")));
	ItemIconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	ItemCountBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));

	// �κ��丮 �����ۿ� �ִ� UInvenItemData�� �κ��丮��� ������ ������ �־�� �մϴ�.
	ItemData = NewObject<UInventoryItemData>();
}

void UPortfolio_Widget_InventorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UPortfolio_Widget_InventorySlot::SetItemData(UInventoryItemData* _ItemData)
{
	ItemData = _ItemData;
	SlotDataCheck();
}

void UPortfolio_Widget_InventorySlot::SlotDataCheck()
{
	if (nullptr == ItemData)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == ItemData)"), __FUNCTION__, __LINE__);
		// ġ������ ����
		//ItemBackVisibility = ESlateVisibility::Visible;
		//ItemIconVisibility = ESlateVisibility::Hidden;
		//ItemCountVisibility = ESlateVisibility::Hidden;
		return;
	}

	if (nullptr == ItemData->Data)
	{
		ItemBackVisibility = ESlateVisibility::Visible;
		ItemIconVisibility = ESlateVisibility::Hidden;
		ItemCountVisibility = ESlateVisibility::Hidden;
		return;
	}

	if (nullptr != ItemData->Data)
	{
		ItemIconVisibility = ESlateVisibility::Visible;
		ItemIconImage->SetBrushFromTexture(Cast<UTexture2D>(ItemData->Data->Icon));
		ItemCountValue = ItemData->Count;

		if (1 < ItemData->Data->StackMax)
		{
			ItemCountVisibility = ESlateVisibility::Visible;
		}
		else
		{
			ItemCountVisibility = ESlateVisibility::Hidden;
		}
	}
}

void UPortfolio_Widget_InventorySlot::DragSetting(UPortfolio_Widget_InventorySlot* _OtherDragSlot)
{
	ItemIconBack = Cast<UImage>(GetWidgetFromName(TEXT("ItemBack")));
	ItemIconImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	ItemCountBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));


	// �̰�ȣ��Ǵ� ����ڴ�
	// �巡�׸� ���ؼ� ������� �������Դϴ�.
	ItemBackVisibility = ESlateVisibility::Hidden;

	// _OtherDragSlot�� �巡���� �����̵� �����̴�.
	SetItemData(_OtherDragSlot->ItemData);

}

void UPortfolio_Widget_InventorySlot::MoveSetting(UPortfolio_Widget_InventorySlot* _OtherDragSlot)
{
	if (_OtherDragSlot == this)
	{
		return;
	}

	// UInvenItemSlot* _OtherDragSlot ���۽���

	// �̰� ȣ���ϴ� ���� ���� ���� ����

	if (ItemTypeValue != ItemType::NONE && _OtherDragSlot->ItemData->Data->Type != ItemTypeValue)
	{
		return;
	}

	//const FItemData* SwapItemData = _OtherDragSlot->ItemData->Data;
	//_OtherDragSlot->ItemData->Data = ItemData->Data;
	//ItemData->Data = SwapItemData;

	UInventoryItemData* SwapItemData = _OtherDragSlot->ItemData;
	_OtherDragSlot->ItemData = ItemData;
	ItemData = SwapItemData;

	// ù��° �Լ�������.
	// �ι�° ������
	// StatusChracter

	// ���� �̺κп��� ������ �ϰ� �;�.
	// �װ� ���� �˷���� �ϴµ�.
	// �Լ�������.
	// ���� �׳� UI��. ���� �÷��̾ ���ͳ� �̷��͵��� �˰� ���� �ʴ�.

	// �Լ��� ���� �Ǿ��ٸ�
	if (true == ItemChangeFunction.IsBound())
	{
		// �� �Լ��� ȣ���ض�.
		ItemChangeFunction.Broadcast();
	}

	// ���� �� �޾Ƽ� �����ϰ�
	SlotDataCheck();
	_OtherDragSlot->SlotDataCheck();
}



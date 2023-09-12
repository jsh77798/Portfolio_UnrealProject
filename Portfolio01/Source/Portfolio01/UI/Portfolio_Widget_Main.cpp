// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Portfolio_Widget_Main.h"
#include "UI/Portfolio_Widget_Inventory.h"
#include "Game/Portfolio_Character.h"
#include "Global/Portfolio_GlobalCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Portfolio_Enums.h"

void UPortfolio_Widget_Main::NativeConstruct()
{
	Super::NativeConstruct();

	// Inven = Cast<UInventoryUserWidget>(GetWidgetFromName(TEXT("WBP_UI_Inventory")));
	// Inven = Cast<UInventoryUserWidget>(GetWidgetFromName(TEXT("WBP_Status")));


	AllWidGet.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_UI_Inventory"))));
	AllWidGet.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_UI_MiniMap"))));
	AllWidGet.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_UI_Option"))));
	AllWidGet.Add(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_UI_BackGround"))));
}

void UPortfolio_Widget_Main::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	// �⺻���� �̵��̳� �̷� �ý�����ü�� �ٸ��ٴ°��� ����ؾ� �Ѵ�.
	// Inven->SetPositionInViewport({100, 100});
	// Inven->SetAnchorsInViewport();
}

// ���⼭ �����ϴ� bool ���� ���� ���°� �ٲ���ٴ� AllHidden�� �ٲ���ٴ°��� üũ�ϴ� bool ���� �ȴ�.
bool UPortfolio_Widget_Main::CheckAllWidGetHidden()
{
	bool AllHiddenCheck = true;

	for (size_t i = 0; i < AllWidGet.Num(); i++)
	{
		if (AllWidGet[i]->GetVisibility() == ESlateVisibility::Visible)
		{
			AllHiddenCheck = false;
		}
	}

	// false���µ� true�� �ǰ�
	// true���µ� false�� �Ǵ� ��Ȳ�� ����
	if (AllHiddenCheck != AllHidden)
	{
		AllHidden = AllHiddenCheck;
		return true;
	}

	return false;
}

bool UPortfolio_Widget_Main::CheckAiming()
{
	// Portfolio_Character���� Aiming���¸� üũ�ϰ� ���� �����´�
    APortfolio_Character* MyCharacter = Cast<APortfolio_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));  //UGameplayStatics => #include "Kismet/GameplayStatics.h"��� �ʿ�
	bool AimingCheck = MyCharacter->AimingCheck;

	return AimingCheck;
}

bool UPortfolio_Widget_Main::CheckRangeItem()
{
	
	return true;
}
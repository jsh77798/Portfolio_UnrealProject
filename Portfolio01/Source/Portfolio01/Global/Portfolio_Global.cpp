// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_Global.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Portfolio_GlobalUserWidget.h"

class UPortfolio_GlobalUserWidget* UPortfolio_Global::DebugWidget = nullptr;
FRandomStream UPortfolio_Global::MainRandom;

void UPortfolio_Global::ARDebugTextInit()
{
	// 끝날을때 자동으로 지워지지만
	// delete를 한다고 
	DebugWidget = nullptr;
}

void UPortfolio_Global::ARDebugTextPrint(class AActor* _AActor, const FString& _Text)
{
	// 여기서 만약 위젯이 없다면
	// 만들어 내야 한다.
	// 위젯이 없어.
	if (nullptr == DebugWidget)
	{
		UWorld* World = _AActor->GetWorld();

		if (nullptr == World && false == World->IsValidLowLevel())
		{
			return;
		}

		// 

		// 이걸 런타임 중간에 알아내는 방법은

		FSoftClassPath ObjectClass("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/Global/WBP_GlobalDebug.WBP_GlobalDebug'");
		TSubclassOf<UUserWidget> SubClassValue = ObjectClass.TryLoadClass<UUserWidget>();

		if (nullptr == SubClassValue)
		{
			return;
		}

		UUserWidget* NewWidGet = CreateWidget<UUserWidget>(World, SubClassValue);

		if (nullptr == NewWidGet)
		{
			// 생성에 실패할때까 있을수 있으므로 이것도 처리해준다.
			return;
		}

		DebugWidget = Cast<UPortfolio_GlobalUserWidget>(NewWidGet);
		DebugWidget->AddToViewport(1000);
	}

	DebugWidget->AddDebugText(_Text);
}



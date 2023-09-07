// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Portfolio_Global.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Portfolio_GlobalUserWidget.h"

class UPortfolio_GlobalUserWidget* UPortfolio_Global::DebugWidget = nullptr;
FRandomStream UPortfolio_Global::MainRandom;

UWorld* UPortfolio_Global::GetCurrentWorld()
{
	// �𸮾� ���� ����ü�� ���� ����� �����ϴ� ������
	// GEngine->GetWorld();

	// ���尡 ���ÿ� �������� �����Ҷ��� �ִ�.

	for (const FWorldContext& Context : GEngine->GetWorldContexts())
	{
		EWorldType::Type GetWorldType = Context.WorldType;

		if (nullptr == Context.World())
		{
			continue;
		}

		FString Name = Context.World()->GetName();

		// UE_LOG(LogTemp, Error, TEXT("%s"), *Name);

		switch (GetWorldType)
		{
		case EWorldType::None:
			break;
		case EWorldType::Game:
			break;
		case EWorldType::Editor:
			break;
		case EWorldType::PIE:
			return Context.World();
		case EWorldType::EditorPreview:
			break;
		case EWorldType::GamePreview:
			break;
		case EWorldType::GameRPC:
		case EWorldType::Inactive:
			break;
		default:
			break;
		}
	}

	return nullptr;
}

void UPortfolio_Global::EditorTestFunction()
{
	// ������ ��ɰ� + �÷��� ����� ��ÿ� ����Ѵٴ� �̾߱Ⱑ �ȴ�.
	// �׷��� ������ ��찡 ������ ����.
	// �����Ϳ����� ��
	// GEngine


	// UGameplayStatics::GetWorld()

	// GetWorld();
	// UGameplayStatics::GetPlayerController()

	return;
}

void UPortfolio_Global::ARDebugTextInit()
{
	DebugWidget = nullptr;
}

void UPortfolio_Global::ARDebugTextPrint(class AActor* _AActor, const FString& _Text)
{
	if (nullptr == DebugWidget)
	{
		UWorld* World = _AActor->GetWorld();

		if (nullptr == World && false == World->IsValidLowLevel())
		{
			return;
		}

		FSoftClassPath ObjectClass("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/Global/WBP_GlobalDebug.WBP_GlobalDebug'");
		TSubclassOf<UUserWidget> SubClassValue = ObjectClass.TryLoadClass<UUserWidget>();

		if (nullptr == SubClassValue)
		{
			return;
		}

		UUserWidget* NewWidGet = CreateWidget<UUserWidget>(World, SubClassValue);

		if (nullptr == NewWidGet)
		{
			return;
		}

		DebugWidget = Cast<UPortfolio_GlobalUserWidget>(NewWidGet);
		DebugWidget->AddToViewport(1000);
	}

	DebugWidget->AddDebugText(_Text);
}



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Portfolio_Global.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO01_API UPortfolio_Global : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FRandomStream MainRandom;

	UFUNCTION(BlueprintCallable, Category = "Portfolio_Global")
		static void ARDebugTextInit();

	//����� �ؽ�Ʈ�� ������ ���ؼ� ȭ�鿡 �ѷ��ִ� �Լ�.
	UFUNCTION(BlueprintCallable, Category = "Portfolio_Global", meta = (DefaultToSelf = "_Object"))
		static void ARDebugTextPrint(class AActor* _Object, const FString& _Text);

	static class UPortfolio_GlobalUserWidget* DebugWidget;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "OneDog/UI/Marriage/UI_UserWidgetBase.h"
#include "UI_TipsWindow.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_TipsWindow : public UUI_UserWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Tips;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Confirm();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Cancel();
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	static UUI_TipsWindow* Show(UWorld* World, const FText& Tips, const FText& ConfirmText = FText(), const FText& CancelText = FText());
};

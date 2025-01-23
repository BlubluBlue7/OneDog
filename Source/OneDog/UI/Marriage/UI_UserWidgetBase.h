// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_UserWidgetBase.generated.h"

enum WIDGET_TYPE
{
	LAYER = 1,
	WINDOW = 2,
};
/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_UserWidgetBase : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUI_UserWidgetBase* ShowLayer(TSubclassOf<UUI_UserWidgetBase> UserWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI")
	UUI_UserWidgetBase* ShowWindow(TSubclassOf<UUI_UserWidgetBase> UserWidgetClass);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Close();

	virtual void Init();

	WIDGET_TYPE WidgetType;
};

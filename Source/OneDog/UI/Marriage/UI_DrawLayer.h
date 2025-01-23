// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_UserWidgetBase.h"
#include "Components/TextBlock.h"
#include "OneDog/Data/Marriage/Data_Role.h"
#include "UI_DrawLayer.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_DrawLayer : public UUI_UserWidgetBase
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Age;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Sex;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Height;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Weight;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Hobby;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Des;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Confirm();
	
	UData_Role* Role;
	virtual void NativeConstruct() override;
};

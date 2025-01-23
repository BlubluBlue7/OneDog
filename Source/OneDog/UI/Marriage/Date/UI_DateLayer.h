// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h" // 用于对象管理
#include "Components/ListView.h"
#include "OneDog/Data/Marriage/UData//UData_Role.h"
#include "OneDog/UI/Marriage/UI_UserWidgetBase.h"
#include "UI_DateLayer.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_DateLayer : public UUI_UserWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UListView* ListView_Male;

	UPROPERTY(meta = (BindWidget))
	UListView* ListView_Female;

	TArray<UUData_Role*> MaleList;
	TArray<UUData_Role*> FemaleList;
	UUData_Role* SelectMaleData;
	UUData_Role* SelectFemaleData;
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Confirm();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Cancel();

	UFUNCTION()
	void OnListItemCheckBoxClicked(bool bIsChecked, UUData_Role* Data);

	void OnListItemGenerated(UUserWidget& Widget);
	
	virtual void NativeConstruct() override;
};

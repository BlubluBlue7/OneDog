// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "OneDog/Data/Marriage/UData/UData_Couple.h"
#include "OneDog/UI/Marriage/UI_UserWidgetBase.h"
#include "UI_CoulpleLayer.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_CoulpleLayer : public UUI_UserWidgetBase
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UListView* ListView_Couple;

	TArray<UUData_Couple*> CoupleDataList;
	virtual void NativeConstruct() override;

	void OnListItemGenerated(UUserWidget& Widget);

	UFUNCTION()
	void OnListItemBtnClicked(UUData_Couple* Data);
};

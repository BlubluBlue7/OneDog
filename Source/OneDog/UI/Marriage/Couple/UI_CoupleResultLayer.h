// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "OneDog/Data/Marriage/UData/UData_Couple.h"
#include "OneDog/UI/Marriage/UI_UserWidgetBase.h"
#include "UI_CoupleResultLayer.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_CoupleResultLayer : public UUI_UserWidgetBase
{
	GENERATED_BODY()
	UUData_Couple* CoupleData;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_MaleName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_MaleDes;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FemaleName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FemaleDes;

	UPROPERTY(meta = (BindWidget))
	UListView* ListView_Result;
public:
	void UpdateCouple(UUData_Couple* Data);

	TArray<UUData_CoupleResult*> ResultList;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Add();
};

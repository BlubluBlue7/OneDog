// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "OneDog/Data/Marriage/UData/UData_Couple.h"
#include "OneDog/UI/Marriage/UI_UserWidgetBase.h"
#include "UI_Comp_CoupleCell.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_Comp_CoupleCell : public UUI_UserWidgetBase, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_MaleName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_MaleDes;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FemaleName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FemaleDes;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Select();

	UUData_Couple* CurData;
	// 实现 IUserObjectListEntry 接口
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeConstruct() override;
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBtnClicked, UUData_Couple*, Data);
	UPROPERTY(BlueprintAssignable)
	FOnBtnClicked OnSelectClicked;
};

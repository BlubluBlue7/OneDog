// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OneDog/Data/Marriage/UData/UData_Role.h"
#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "OneDog/UI/Marriage/UI_UserWidgetBase.h"
#include "UI_Comp_DateCell.generated.h"
/**
 * 
 */
UCLASS()
class ONEDOG_API UI_Comp_DateCell : public UUI_UserWidgetBase, public IUserObjectListEntry
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Info;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Des;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* CheckBox_Select;
	
	// 实现 IUserObjectListEntry 接口
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnCheckBoxStateChanged(bool bIsChecked);


	UUData_Role* CurData;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCheckBoxClickedSignature, bool, bIsChecked, UUData_Role*, Data);
	UPROPERTY(BlueprintAssignable)
	FOnCheckBoxClickedSignature OnCheckBoxClicked;

	void OnItemRefreshed();
};

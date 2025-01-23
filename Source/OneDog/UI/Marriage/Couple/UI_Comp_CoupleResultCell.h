// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "OneDog/UI/Marriage/UI_UserWidgetBase.h"
#include "UI_Comp_CoupleResultCell.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_Comp_CoupleResultCell : public UUI_UserWidgetBase, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Des;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};

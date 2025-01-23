// Fill out your copyright notice in the Description page of Project Settings.


#include "OneDog/UI/Marriage/Couple/UI_Comp_CoupleResultCell.h"

#include "Components/TextBlock.h"
#include "OneDog/Data/Marriage/UData/UData_CoupleResult.h"

void UUI_Comp_CoupleResultCell::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UUData_CoupleResult* Data = Cast<UUData_CoupleResult>(ListItemObject);
	if (Data)
	{
		Text_Des->SetText(FText::FromString(Data->Des));
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "OneDog/UI/Marriage/Couple/UI_Comp_CoupleCell.h"

void UUI_Comp_CoupleCell::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UUData_Couple* Data = Cast<UUData_Couple>(ListItemObject);
	if (Data)
	{
		CurData = Data;
		UData_Role* MaleData = Data->CoupleData->Male;
		UData_Role* FemaleData = Data->CoupleData->Female;
		Text_MaleName->SetText(FText::FromString(MaleData->Name));
		Text_MaleDes->SetText(FText::FromString(MaleData->Des));
		Text_FemaleName->SetText(FText::FromString(FemaleData->Name));
		Text_FemaleDes->SetText(FText::FromString(FemaleData->Des));
	}
}

void UUI_Comp_CoupleCell::NativeConstruct()
{
	Super::NativeConstruct(); 
}

void UUI_Comp_CoupleCell::Select()
{
	OnSelectClicked.Broadcast(CurData);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "OneDog/UI/Marriage/Couple/UI_CoulpleLayer.h"

#include "UI_Comp_CoupleCell.h"
#include "UI_CoupleResultLayer.h"
#include "OneDog/Data/Marriage/Data_Manager.h"

void UUI_CoulpleLayer::NativeConstruct()
{
	Super::NativeConstruct();
	
	UData_Bag* BagData = Data_Manager::GetInstance().Bag;
	CoupleDataList = BagData->GetCoupleList();

	ListView_Couple->SetListItems(CoupleDataList);
	ListView_Couple->OnEntryWidgetGenerated().AddLambda([this](UUserWidget& Widget)
	{
		OnListItemGenerated(Widget);
	});
}

void UUI_CoulpleLayer::OnListItemGenerated(UUserWidget& Widget)
{
	UUI_Comp_CoupleCell* Cell = Cast<UUI_Comp_CoupleCell>(&Widget);
	if (Cell)
	{
		Cell->OnSelectClicked.AddDynamic(this, &UUI_CoulpleLayer::OnListItemBtnClicked);
	}
}

void UUI_CoulpleLayer::OnListItemBtnClicked(UUData_Couple* Data)
{
	TSubclassOf<UUI_UserWidgetBase> TypeClass = LoadClass<UUI_UserWidgetBase>(nullptr, TEXT("/Game/UI/Marriage/Couple/BP_UI_CoupleResultLayer.BP_UI_CoupleResultLayer_C"));
	UUI_UserWidgetBase* Widget = ShowLayer(TypeClass);
	UUI_CoupleResultLayer* ResultLayer = Cast<UUI_CoupleResultLayer>(Widget);
	ResultLayer->UpdateCouple(Data);
}
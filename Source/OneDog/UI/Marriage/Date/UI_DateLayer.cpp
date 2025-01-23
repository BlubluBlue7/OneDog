// Fill out your copyright notice in the Description page of Project Settings.


#include "OneDog/UI/Marriage/Date/UI_DateLayer.h"

#include "UI_Comp_DateCell.h"
#include "OneDog/Data/Marriage/Data_Manager.h"
#include "OneDog/UI/Marriage/Common/UI_TipsWindow.h"

void UUI_DateLayer::NativeConstruct()
{
	Super::NativeConstruct();

	UData_Bag* BagData = Data_Manager::GetInstance().Bag;
	MaleList = BagData->GetRoleListBySex(1);
	FemaleList = BagData->GetRoleListBySex(2);

	
	ListView_Male->SetListItems(MaleList);
	ListView_Female->SetListItems(FemaleList);

	ListView_Male->OnEntryWidgetGenerated().AddLambda([this](UUserWidget& Widget)
	{
		OnListItemGenerated(Widget);
	});
	ListView_Female->OnEntryWidgetGenerated().AddLambda([this](UUserWidget& Widget)
	{
		OnListItemGenerated(Widget);
	});
}

void UUI_DateLayer::OnListItemGenerated(UUserWidget& Widget)
{
	UI_Comp_DateCell* Cell = Cast<UI_Comp_DateCell>(&Widget);
	if (Cell)
	{
		Cell->OnCheckBoxClicked.AddDynamic(this, &UUI_DateLayer::OnListItemCheckBoxClicked);
	}
}

void UUI_DateLayer::OnListItemCheckBoxClicked(bool bIsChecked, UUData_Role* Data)
{
	if(Data->IsSelect)
	{
		if(Data->Sex == 1)
		{
			if(SelectMaleData)
			{
				SelectMaleData->IsSelect = false;
				UUserWidget* Widget = ListView_Male->GetEntryWidgetFromItem(SelectMaleData);
				UI_Comp_DateCell* MyItemWidget = Cast<UI_Comp_DateCell>(Widget);
				if (MyItemWidget)
				{
					MyItemWidget->OnItemRefreshed();  // 执行方法
				}
			}
			SelectMaleData = Data;
		}
		else
		{
			if(SelectFemaleData)
			{
				SelectFemaleData->IsSelect = false;
				UUserWidget* Widget = ListView_Female->GetEntryWidgetFromItem(SelectMaleData);
				UI_Comp_DateCell* MyItemWidget = Cast<UI_Comp_DateCell>(Widget);
				if (MyItemWidget)
				{
					MyItemWidget->OnItemRefreshed();  // 执行方法
				}
			}
			SelectFemaleData = Data;
		}
	}
}

void UUI_DateLayer::Confirm()
{
	if(SelectMaleData == nullptr || SelectFemaleData == nullptr)
	{
		UUI_TipsWindow::Show(this->GetWorld(), FText::FromString(TEXT("请选择男女角色")));
		return;
	}

	Data_Manager::GetInstance().Bag->AddCouple(SelectMaleData->Role, SelectFemaleData->Role);
	Close();
}

void UUI_DateLayer::Cancel()
{
	Close();
}
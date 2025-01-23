#include "UI_Comp_DateCell.h"




void UI_Comp_DateCell::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UUData_Role* Data = Cast<UUData_Role>(ListItemObject);
	if (Data)
	{
		CurData = Data;
		OnItemRefreshed();
	}
}

void UI_Comp_DateCell::OnItemRefreshed()
{
	if (CurData)
	{
		if (Text_Name)
		{
			Text_Name->SetText(FText::FromString(CurData->Name));
		}
		if (Text_Info)
		{
			FString FormattedText = FString::Printf(TEXT("年龄：%d, 爱好: %s"), CurData->Age, *CurData->Hobby);
			Text_Info->SetText(FText::FromString(FormattedText));
		}
		if (Text_Des)
		{
			Text_Des->SetText(FText::FromString(CurData->Des));
		}

		if (CheckBox_Select)
		{
			CheckBox_Select->SetCheckedState(CurData->IsSelect ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
		}
	}
}

void UI_Comp_DateCell::NativeConstruct()
{
	Super::NativeConstruct();

	if (CheckBox_Select)
	{
		CheckBox_Select->OnCheckStateChanged.AddDynamic(this, &UI_Comp_DateCell::OnCheckBoxStateChanged);
	}
}

void UI_Comp_DateCell::OnCheckBoxStateChanged(bool bIsChecked)
{
	// 触发自定义事件
	CurData->IsSelect = bIsChecked;
	OnCheckBoxClicked.Broadcast(bIsChecked, CurData);
}
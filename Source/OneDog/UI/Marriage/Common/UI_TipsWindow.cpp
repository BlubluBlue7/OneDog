// Fill out your copyright notice in the Description page of Project Settings.


#include "OneDog/UI/Marriage/Common/UI_TipsWindow.h"

#include "Base/WorldManager.h"

void UUI_TipsWindow::Confirm()
{
	Close();
}

void UUI_TipsWindow::Cancel()
{
	Close();
}

UUI_TipsWindow* UUI_TipsWindow::Show(UWorld* World, const FText& Tips, const FText& ConfirmText, const FText& CancelText)
{
	// /Script/UMGEditor.WidgetBlueprint'/Game/UI/Marriage/Common/BP_UI_TipsWindow.BP_UI_TipsWindow'
	TSubclassOf<UUI_TipsWindow> BP_TipsWindowClass = LoadClass<UUI_TipsWindow>(nullptr, TEXT("/Game/UI/Marriage/Common/BP_UI_TipsWindow.BP_UI_TipsWindow_C"));
	
	UUI_UserWidgetBase* Widget = Cast<UUI_UserWidgetBase>(CreateWidget(World, BP_TipsWindowClass));
	WorldManager::GetInstance().RootLayer->AddToModel(Widget);

	UUI_TipsWindow* UserWidget = Cast<UUI_TipsWindow>(Widget);
	if (UserWidget)
	{
		UserWidget->Init();
		UserWidget->Text_Tips->SetText(Tips);
	}
	
	return UserWidget;
}
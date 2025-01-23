// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_UserWidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Base/WorldManager.h"

UUI_UserWidgetBase* UUI_UserWidgetBase::ShowLayer(TSubclassOf<UUI_UserWidgetBase> UserWidgetClass)
{
	UWorld* World = this->GetWorld();
	UUI_UserWidgetBase* Widget = Cast<UUI_UserWidgetBase>(CreateWidget(World, UserWidgetClass));
	WorldManager::GetInstance().AddToRoot(Widget);

	return Widget;
}

UUI_UserWidgetBase* UUI_UserWidgetBase::ShowWindow(TSubclassOf<UUI_UserWidgetBase> UserWidgetClass)
{
	UWorld* World = this->GetWorld();
	UUI_UserWidgetBase* Widget = Cast<UUI_UserWidgetBase>(CreateWidget(World, UserWidgetClass));
	
	WorldManager::GetInstance().RootLayer->AddToModel(Widget);

	UUI_UserWidgetBase* UserWidget = Cast<UUI_UserWidgetBase>(Widget);
	if (UserWidget)
	{
		UserWidget->Init();
	}
	
	return Widget;
}

void UUI_UserWidgetBase::Close()
{
	if (WidgetType == WIDGET_TYPE::LAYER)
	{
		WorldManager::GetInstance().RootLayer->Close();
	}
	else if (WidgetType == WIDGET_TYPE::WINDOW)
	{
		WorldManager::GetInstance().RootLayer->CloseWindow(this);
	}
}

void UUI_UserWidgetBase::Init()
{
}

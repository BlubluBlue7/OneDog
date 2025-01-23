// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "UI_UserWidgetBase.h"
#include "Components/TextBlock.h"
#include "UI_RootLayer.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_RootLayer : public UUI_UserWidgetBase
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* RootPanel;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ModelPanel;

	UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Width;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Height;
	
	TArray<UUserWidget*> LayerStack;
	UUserWidget* CurLayer;

	virtual void NativeConstruct() override;
public:
	void AddToRoot(UUI_UserWidgetBase* Layer);
	void Close();
	void CloseWindow(UUI_UserWidgetBase* Window);
	void AddToModel(UUI_UserWidgetBase* Layer);
};

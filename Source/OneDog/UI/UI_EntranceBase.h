// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Network/NetManager.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "UI_EntranceBase.generated.h"
/**
 * 
 */
UCLASS()
class ONEDOG_API UUI_EntranceBase : public UUserWidget
{
	GENERATED_BODY()
	NetManager* netManager;
public:
	UPROPERTY(meta = (BindWidget))
	UButton* serverBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* clientBtn;
	UPROPERTY(meta = (BindWidget))
	UButton* clientConnect;
	UPROPERTY(meta = (BindWidget))
	UMultiLineEditableTextBox* serverInput;
	UPROPERTY(meta = (BindWidget))
	UMultiLineEditableTextBox* clientInput;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* serverText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* clientText;

	FString serverContent;
	FString clientContent;
	
	void ServerStateChange(int state, FString str);
	void ClientStateChange(int state, FString str);
	
	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void Init();

	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void Close();
	
	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void ServerBtnClick();

	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void ClientBtnClick();

	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void ClientConnectClick();
	void UpdateServerText();
	void UpdateClientText();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Network/NetManager.h"
#include "../Data/Data.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
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
	UEditableText* Input_ID;

	UPROPERTY(meta = (BindWidget))
	UEditableText* Input_Password;

	void ServerStateChange(int state, FString str);
	void ClientStateChange(int state, FString str);
	
	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void Init();

	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void Close();

	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void Update();

	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void Login();
	
	UFUNCTION(BlueprintCallable, Category = "UI_Entrance")
	void Register();
};

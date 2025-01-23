// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "OneDog/Data/UserData.h"
#include "CoreMinimal.h"
#include "Message/MessageManager.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	UPROPERTY()
	UMessageManager* M;
	
	bool Tick(float DeltaTime);
};

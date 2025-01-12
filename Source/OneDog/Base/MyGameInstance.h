// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Comp_GameInstance.h"
#include "CoreMinimal.h"
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

	bool Tick(float DeltaTime);
};

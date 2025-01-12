// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldManager.h"
#include "MyGameInstance.h"

#include "OneDog/Network/NetManager.h"

void UMyGameInstance::Init()
{
	Super::Init();
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();
	
	WorldManager::GetInstance().Clear();
	NetManager::GetInstance().Close();
}

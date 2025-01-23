// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameInstance.h"
#include "WorldManager.h"
#include "Ctrl/Ctrl.h"
#include "OneDog/Network/NetManager.h"
#include "Tools/DeepSeek.h"

void UMyGameInstance::Init()
{
	Super::Init();
	M = NewObject<UMessageManager>(this);
	
	WorldManager::GetInstance().Init(this);
	Ctrl::GetInstance().Init();
	UserData::GetInstance().Init();
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	Ctrl::GetInstance().World->SendLeaveWorld(UserData::GetInstance().GetUserId());
	
	M = nullptr;
	WorldManager::GetInstance().Clear();
	NetManager::GetInstance().Close();
	UserData::GetInstance().Clear();
	DeepSeek::GetInstance().Clear();
}

// Fill out your copyright notice in the Description page of Project Settings.
#include "UI_EntranceBase.h"

#include "OneDog/Protobuf/ProtobufManager.h"
#include "../Protobuf/cl.pb.h"
#include "Ctrl/Ctrl.h"


void UUI_EntranceBase::Init()
{
	netManager = &NetManager::GetInstance();

	ServerStateChangeCB serverCB = std::bind(&UUI_EntranceBase::ServerStateChange, this, std::placeholders::_1, std::placeholders::_2);
	ClientStateChangeCB clientCB = std::bind(&UUI_EntranceBase::ClientStateChange, this, std::placeholders::_1, std::placeholders::_2);
	netManager->Init(serverCB, clientCB);
}

void UUI_EntranceBase::ServerStateChange(int state, FString str)
{

}

void UUI_EntranceBase::ClientStateChange(int state, FString str)
{

}


void UUI_EntranceBase::Close()
{
	// netManager->Close();
}

void UUI_EntranceBase::Update()
{
	// netManager->Recv();
}

void UUI_EntranceBase::Login()
{
	FText IDStr = Input_ID->GetText();
	FText Password = Input_Password->GetText();
	uint64_t UserId = FCString::Atoi(*IDStr.ToString());
	if (UserId == 0)
	{
		return;
	}

	FString account = IDStr.ToString();
	FString password = Password.ToString();
	Ctrl::GetInstance().Login->SendLogin(account, password);
}

void UUI_EntranceBase::Register()
{
	FText IDStr = Input_ID->GetText();
	FText Password = Input_Password->GetText();
	FString account = IDStr.ToString();
	FString password = Password.ToString();
	Ctrl::GetInstance().Login->SendCreateAccount(account, password);
}




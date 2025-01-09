// Fill out your copyright notice in the Description page of Project Settings.
#include "UI_EntranceBase.h"

void UUI_EntranceBase::Init()
{
	netManager = &NetManager::GetInstance();

	serverContent = TEXT("Server");
	clientContent = TEXT("Client");
	ServerStateChangeCB serverCB = std::bind(&UUI_EntranceBase::ServerStateChange, this, std::placeholders::_1, std::placeholders::_2);
	ClientStateChangeCB clientCB = std::bind(&UUI_EntranceBase::ClientStateChange, this, std::placeholders::_1, std::placeholders::_2);
	netManager->Init(serverCB, clientCB);
}

void UUI_EntranceBase::Close()
{
	netManager->Close();
}

void UUI_EntranceBase::ServerStateChange(int state, FString str)
{
	switch (state)
	{
	case 0:
		serverContent += TEXT("开始监听\n");
		UpdateServerText();
		break;
	case 1:
		serverContent += TEXT("客户端接入！\n");
		UpdateServerText();
		break;
	case 2:
		serverContent += FString::Printf(TEXT("服务器:%s\n"), *str);
		UpdateServerText();
		break;
	case 3:
		serverContent += FString::Printf(TEXT("客户端:%s\n"), *str);
		UpdateServerText();
		break;
	}
}

void UUI_EntranceBase::ClientStateChange(int state, FString str)
{
	switch (state)
	{
	case 0:
		clientContent += TEXT("开始连接\n");
		UpdateClientText();
		break;
	case 1:
		clientContent += TEXT("连接成功！\n");
		UpdateClientText();
		break;
	case 2:
		clientContent += FString::Printf(TEXT("客户端:%s\n"), *str);
		UpdateClientText();
		break;
	case 3:
		clientContent += FString::Printf(TEXT("服务器:%s\n"), *str);
		UpdateClientText();
		break;
	}
}

void UUI_EntranceBase::ClientBtnClick()
{
	netManager->Socket->Send(clientInput->Text.ToString());
	clientInput->SetText(FText::FromString(TEXT("")));
	netManager->Server->Recv();
}

void UUI_EntranceBase::ClientConnectClick()
{
	netManager->Socket->Connect();
}

void UUI_EntranceBase::ServerBtnClick()
{
	netManager->Server->Send(serverInput->Text.ToString());
	serverInput->SetText(FText::FromString(TEXT("")));
	netManager->Socket->Recv();
}

void UUI_EntranceBase::ServerListenClick()
{
	netManager->Server->StartServer();
}

void UUI_EntranceBase::UpdateClientText()
{
	clientText->SetText(FText::FromString(clientContent));
}

void UUI_EntranceBase::UpdateServerText()
{
	serverText->SetText(FText::FromString(serverContent));
}



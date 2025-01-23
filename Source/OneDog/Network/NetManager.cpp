#include "NetManager.h"

#include "OneDog/Level/Test/Level_Test.h"
#include "OneDog/Protobuf/ProtobufManager.h"

void NetManager::Init(ServerStateChangeCB serverCB, ClientStateChangeCB clientCB)
{
	Server = new ServerMonitor();
	Socket = new SocketInstance();

	
	Server->stateCB = serverCB;
	Socket->stateCB = clientCB;

	// ProtobufManager::GetInstance().UseProtobuf();
}


void NetManager::Close()
{
	// Server->EndServer();
	if(Socket)
	{
		Socket->Close();
	}
}

void NetManager::Send(std::string Message, MSG_TYPE Type)
{
	Socket->Send(Message, Type);
}

void NetManager::Recv()
{
	if(not Socket)
	{
		return;
	}
	MSG_TYPE Type = Socket->GetMsg(Buffer);
	while(Type != ID_NONE)
	{
		UE_LOG(LogTemp, Log, TEXT("Recv Type: %d"), Type);
		TArray<uint8> B = Buffer;
		WorldManager::GetInstance().GameInstance->M->SendMessage(Type, B);
		Buffer.Empty();
		Type = Socket->GetMsg(Buffer);
		// ProtobufManager::GetInstance().Decode(Buffer);
	}
}




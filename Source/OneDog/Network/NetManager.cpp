#include "NetManager.h"

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
	Server->EndServer();
	Socket->Close();
}

void NetManager::Send(std::string Message)
{
	Socket->Send(Message);
}

void NetManager::Recv()
{
	TArray<uint8> Buffer = Socket->GetMsg();
	if(Buffer.Num() > 0)
	{
		ProtobufManager::GetInstance().Decode(Buffer);
	}
}




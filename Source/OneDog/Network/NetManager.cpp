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
	Server->EndServer();
	Socket->Close();
}

void NetManager::Send(std::string Message, MSG_TYPE Type)
{
	Socket->Send(Message, Type);
}

void NetManager::Recv()
{
	MSG_TYPE Type = Socket->GetMsg(Buffer);
	if(Type != ID_NONE)
	{
		switch (Type)
		{
		case ID_L2C_EnterWorld:
			WorldManager::GetInstance().ChangeLevel(FName("Map_Test"));
			break;
		case ID_L2C_NotifyEnterWorld:
			AActor* Actor = WorldManager::GetInstance().BaseActor;
			ALevel_Test* Test = Cast<ALevel_Test>(Actor);
			if(Test != nullptr)
			{
				Test->AddEnemy();
			}
			break;
		}
		Buffer.Empty();
		// ProtobufManager::GetInstance().Decode(Buffer);
	}
}




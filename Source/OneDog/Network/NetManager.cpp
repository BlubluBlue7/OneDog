#include "NetManager.h"

void NetManager::Init(ServerStateChangeCB serverCB, ClientStateChangeCB clientCB)
{
	Server = new ServerMonitor();
	Socket = new SocketInstance();

	
	Server->stateCB = serverCB;
	Socket->stateCB = clientCB;
	
	Server->StartServer();
	Socket->Connect();
}




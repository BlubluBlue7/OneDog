#pragma once
#include "../Base/Base.h"
#include "SocketInstance.h"
#include "ServerMonitor.h"


class NetManager: public SingletonBase<NetManager>
{
private:

public:
	SocketInstance* Socket;
	ServerMonitor* Server;
	void Init(ServerStateChangeCB serverCB, ClientStateChangeCB clientCB);
	void Close();
};

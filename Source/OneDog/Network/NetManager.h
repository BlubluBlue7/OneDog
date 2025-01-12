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
	TArray<uint8> Buffer;
	void Init(ServerStateChangeCB serverCB, ClientStateChangeCB clientCB);
	void Close();

	void Send(std::string Message, MSG_TYPE Type);
	void Recv();
};

#pragma once

#include <functional>

using ServerStateChangeCB = std::function<void(int, FString)>;

class ServerMonitor
{
public:
	bool bIsRunning = false;
	FSocket* ServerSocket;
	TSharedPtr<FSocket> ClientSocket;

	ServerStateChangeCB stateCB;
	
	void HandleClientConnection();

	void Recv();
	void Send(FString Response);
	
	void StartServer();
	void EndServer();
};

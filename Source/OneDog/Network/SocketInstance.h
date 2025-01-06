#pragma once
#include <iostream>
#include <cstring>
#include <functional>

using ClientStateChangeCB = std::function<void(int, FString)>;

class SocketInstance
{
public:
	FSocket* ClientSocket;
	ClientStateChangeCB stateCB;
	bool bIsRunning = false;
	void Connect();
	void Send(FString Message);
	void Close();
	void Recv();
};

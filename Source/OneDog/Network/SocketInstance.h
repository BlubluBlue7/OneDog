#pragma once
#include <iostream>
#include <cstring>
#include <functional>
#include "../Protobuf/cl.pb.h"

using ClientStateChangeCB = std::function<void(int, FString)>;

class SocketInstance
{
private:
	TArray<uint8> EncodeMsg(std::string Message, MSG_TYPE Type);
	MSG_TYPE DecodeMsg(TArray<uint8> Buffer, TArray<uint8> Message);
public:
	FSocket* ClientSocket;
	ClientStateChangeCB stateCB;

	TQueue<TArray<uint8>> ByteArrayQueue; // 接收到的消息队列
	TArray<uint8> CurrentMsg; // 当前消息
	TArray<uint8> RecvBuffer; // 接收缓冲区
	uint32 BytesLeft = 0; // 当前消息剩余字节数
	
	bool bIsRunning = false;
	void AsyncConnect();
	bool Connect();
	void Send(std::string Message, MSG_TYPE Type);
	void Close();
	void Recv();

	MSG_TYPE GetMsg(TArray<uint8> Message);
};

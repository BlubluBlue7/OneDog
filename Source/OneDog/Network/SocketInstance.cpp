#include "SocketInstance.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"
#include "Common/TcpSocketBuilder.h"

void SocketInstance::Connect()
{
	bIsRunning = true;
	FIPv4Address IPAddress;
	FIPv4Address::Parse(TEXT("192.168.56.1"), IPAddress); // 服务端 IP 地址
	FIPv4Endpoint Endpoint(IPAddress, 9996); // 服务端端口号
	ClientSocket = FTcpSocketBuilder(TEXT("TCPClient"))
		.AsReusable()
		.BoundToEndpoint(Endpoint);
	stateCB(0, "");
	if (ClientSocket->Connect(*Endpoint.ToInternetAddr()))
	{
		stateCB(1, "");
		UE_LOG(LogTemp, Log, TEXT("Connected to server!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server!"));
	}
}

void SocketInstance::Close()
{
	bIsRunning = false;
	// 关闭连接
	ClientSocket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
	ClientSocket = nullptr;
}

void SocketInstance::Send(FString Message)
{
	// 发送消息
	FTCHARToUTF8 Convert(*Message);
	int32 BytesSent = 0;
	ClientSocket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);
	stateCB(2, Message);
}

void SocketInstance::Recv()
{
	// 接收响应
	uint32 BufferSize = 1024;
	TArray<uint8> Buffer;
	Buffer.SetNumUninitialized(BufferSize);

	int32 BytesRead = 0;
	if (ClientSocket->Recv(Buffer.GetData(), BufferSize, BytesRead))
	{
		FString ReceivedData = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(Buffer.GetData())));
		stateCB(3, ReceivedData);
		UE_LOG(LogTemp, Log, TEXT("Received from server: %s"), *ReceivedData);
	}
}




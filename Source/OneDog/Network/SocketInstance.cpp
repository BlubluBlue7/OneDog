#include "SocketInstance.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"
#include "Common/TcpSocketBuilder.h"

void SocketInstance::AsyncConnect()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
	{
		Connect();
	});
}
void SocketInstance::Connect()
{
	bIsRunning = true;

	// 获取 Socket 子系统
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (SocketSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get socket subsystem"));
		return;
	}

	// 创建客户端 Socket
	ClientSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("ClientSocket"), false);
	if (ClientSocket == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create client socket"));
		return;
	}
	// 设置服务器地址和端口
	FIPv4Address IPAddress;
	FIPv4Address::Parse(TEXT("120.55.165.7"), IPAddress); // 使用本地回环地址
	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
	Addr->SetIp(IPAddress.Value);
	Addr->SetPort(12345); // 设置端口号

	stateCB(0, "");
	// 连接到服务器
	if (!ClientSocket->Connect(*Addr))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server"));
		return;
	}

	stateCB(1, "");
	UE_LOG(LogTemp, Log, TEXT("Connected to server at 127.0.0.1:12345"));

	// FIPv4Address IPAddress;
	// FIPv4Address::Parse(TEXT("127.0.0.1"), IPAddress); // 服务端 IP 地址
	// FIPv4Endpoint Endpoint(IPAddress, 9996); // 服务端端口号
	// ClientSocket = FTcpSocketBuilder(TEXT("TCPClient"))
	// 	.AsReusable()
	// 	.BoundToEndpoint(Endpoint);
	// stateCB(0, "");
	// if (ClientSocket->Connect(*Endpoint.ToInternetAddr()))
	// {
	// 	stateCB(1, "");
	// 	UE_LOG(LogTemp, Log, TEXT("Connected to server!"));
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Failed to connect to server!"));
	// }
}

void SocketInstance::Close()
{
	bIsRunning = false;
	if (!ClientSocket)
	{
		return;
	}
	
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
	Recv();
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




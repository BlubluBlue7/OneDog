#include "ServerMonitor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"
#include "Common/TcpSocketBuilder.h"

void ServerMonitor::StartServer()
{
	// 获取 Socket 子系统
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (SocketSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get socket subsystem"));
		return;
	}

	// 创建服务器 Socket
	ServerSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("ServerSocket"), true);
	if (ServerSocket == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create server socket"));
		return;
	}

	// 绑定到本地回环地址和端口
	FIPv4Address IPAddress;
	FIPv4Address::Parse(TEXT("127.0.0.1"), IPAddress); // 使用本地回环地址
	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
	Addr->SetIp(IPAddress.Value);
	Addr->SetPort(12345); // 设置端口号

	if (!ServerSocket->Bind(*Addr))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to bind server socket"));
		return;
	}

	// 开始监听连接
	if (!ServerSocket->Listen(5)) // 设置最大连接队列长度
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to listen on server socket"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Server is listening on 127.0.0.1:12345"));
	
	// FIPv4Address IPAddress;
	// FIPv4Address::Parse(TEXT("127.0.0.1"), IPAddress); // 监听所有网络接口
	// FIPv4Endpoint Endpoint(IPAddress, 9996); // 监听端口 9996
	// ServerSocket = FTcpSocketBuilder(TEXT("TCPServer"))
	// 	.AsReusable()
	// 	.BoundToEndpoint(Endpoint)
	// 	.Listening(5);
	//
	if (ServerSocket)
	{
		stateCB(0, "");
		bIsRunning = true;
		UE_LOG(LogTemp, Log, TEXT("Server is listening on port 9996..."));


		// TArray<TSharedPtr<FInternetAddr>> LocalAddresses;
		// if (FPlatformMisc::GetLocalNetworkAddresses(LocalAddresses))
		// {
		// 	for (const TSharedPtr<FInternetAddr>& Address : LocalAddresses)
		// 	{
		// 		FString IPAddress = Address->ToString(false); // false 表示不包含端口
		// 		UE_LOG(LogTemp, Log, TEXT("Local IP Address: %s"), *IPAddress);
		// 	}
		// }
		// else
		// {
		// 	UE_LOG(LogTemp, Error, TEXT("Failed to get local network addresses!"));
		// }

		// 在后台线程中处理客户端连接
		Async(EAsyncExecution::Thread, [this]() { HandleClientConnection(); });
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to start server!"));
	}
}

void ServerMonitor::EndServer()
{
	bIsRunning = false;
	
	if (ServerSocket)
	{
		ServerSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ServerSocket);
		ServerSocket = nullptr;
	}
	
	if (ClientSocket)
	{
		ClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket.Get());
		ClientSocket = nullptr;
	}	
}



void ServerMonitor::HandleClientConnection()
{
	UE_LOG(LogTemp, Log, TEXT("11111111111111111111111111"));
	while (bIsRunning)
	{
		UE_LOG(LogTemp, Log, TEXT("222222222222222222222"));
		if (ServerSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(1)))
		{
			UE_LOG(LogTemp, Log, TEXT("3333333333333333"));
			ClientSocket = TSharedPtr<FSocket>(ServerSocket->Accept(TEXT("TCPClient")));
			if (ClientSocket)
			{
				UE_LOG(LogTemp, Log, TEXT("33333333333333333333333333333"));
				stateCB(1, "");
				Send(FString("Welcome to the server!"));
				UE_LOG(LogTemp, Log, TEXT("Client connected!"));
				break;
			}
		}
	}
}

void ServerMonitor::Send(FString Response)
{
	if(!ClientSocket) return;


	UE_LOG(LogTemp, Log, TEXT("Server Send"));
	// 发送响应
	FTCHARToUTF8 Convert(*Response);
	int32 BytesSent = 0;
	ClientSocket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);
	stateCB(2, Response);
}

void ServerMonitor::Recv()
{
	if(!ClientSocket) return;
	// 接收客户端消息
	uint32 BufferSize = 1024;
	TArray<uint8> Buffer;
	Buffer.SetNumUninitialized(BufferSize);

	int32 BytesRead = 0;
	if (ClientSocket->Recv(Buffer.GetData(), BufferSize, BytesRead))
	{
		FString ReceivedData = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(Buffer.GetData())));
		stateCB(3, ReceivedData);
		UE_LOG(LogTemp, Log, TEXT("Received from client: %s"), *ReceivedData);
	}
}


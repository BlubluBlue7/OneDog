#include "ServerMonitor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"
#include "Common/TcpSocketBuilder.h"

void ServerMonitor::StartServer()
{
	FIPv4Address IPAddress;
	FIPv4Address::Parse(TEXT("0.0.0.0"), IPAddress); // 监听所有网络接口
	FIPv4Endpoint Endpoint(IPAddress, 9996); // 监听端口 9996
	
	ServerSocket = FTcpSocketBuilder(TEXT("TCPServer"))
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(5);
	
	if (ServerSocket)
	{
		stateCB(0, "");
		bIsRunning = true;
		UE_LOG(LogTemp, Log, TEXT("Server is listening on port 9996..."));
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
	while (bIsRunning)
	{
		if (ServerSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(1)))
		{
			ClientSocket = TSharedPtr<FSocket>(ServerSocket->Accept(TEXT("TCPClient")));
			if (ClientSocket)
			{
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


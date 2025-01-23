#include "SocketInstance.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"
#include "Common/TcpSocketBuilder.h"
// #include <winsock2.h>

void SocketInstance::AsyncConnect()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
	{
		Connect();
	});
}
bool SocketInstance::Connect()
{
	bIsRunning = true;

	// 获取 Socket 子系统
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (SocketSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get socket subsystem"));
		return false;
	}

	// 创建客户端 Socket
	ClientSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("ClientSocket"), false);
	if (ClientSocket == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create client socket"));
		return false;
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
		ClientSocket = nullptr;
		return false;
	}

	stateCB(1, "");
	UE_LOG(LogTemp, Log, TEXT("Connected to server at 127.0.0.1:12345"));

	Async(EAsyncExecution::Thread, [this]() { Recv(); });
	return true;
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

void SocketInstance::Send(std::string Message, MSG_TYPE Type)
{
	if(ClientSocket == nullptr)
	{
		if(!Connect())
		{
			return;
		}
	}
	
	TArray<uint8> Buffer = EncodeMsg(Message, Type);
	// 发送消息
	int32 BytesSent = 0;
	ClientSocket->Send(Buffer.GetData(), Buffer.Num(), BytesSent);
	// stateCB(2, Message);
	// Recv();
}

// 判断主机字节序是否为小端序
int is_little_endian() {
	uint16_t num = 0x0001;
	return *(uint8_t *)&num == 0x01; // 如果低地址存储的是低位字节，则是小端序
}

// 将 32 位整数从主机字节序转换为网络字节序
uint32_t my_htonl(uint32_t hostlong) {
	if (is_little_endian()) {
		// 如果是小端序，交换字节顺序
		return ((hostlong & 0xFF000000) >> 24) |
			   ((hostlong & 0x00FF0000) >> 8)  |
			   ((hostlong & 0x0000FF00) << 8)  |
			   ((hostlong & 0x000000FF) << 24);
	} else {
		// 如果是大端序，直接返回
		return hostlong;
	}
}

// 将 32 位整数从网络字节序转换为主机字节序
uint32_t my_ntohl(uint32_t netlong) {
	// 逻辑与 htonl 相同
	if (is_little_endian()) {
		return ((netlong & 0xFF000000) >> 24) |
			   ((netlong & 0x00FF0000) >> 8)  |
			   ((netlong & 0x0000FF00) << 8)  |
			   ((netlong & 0x000000FF) << 24);
	} else {
		return netlong;
	}
}

TArray<uint8> SocketInstance::EncodeMsg(std::string Message, MSG_TYPE Type)
{
	uint32 MsgSize = Message.size();
	uint32 BufferSize = MsgSize + 20;
	TArray<uint8> Buffer;
	Buffer.SetNumUninitialized(BufferSize);

	// UE_LOG(LogTemp, Log, TEXT("发送新消息，长度: %d"), MsgSize);

	BufferSize = my_htonl(BufferSize);
	uint32_t TypeInt = my_htonl(Type);
	FMemory::Memcpy(Buffer.GetData(), &BufferSize, 4);
	FMemory::Memcpy(Buffer.GetData() + 4, &TypeInt, 4);
	// FMemory::Memcpy(Buffer.GetData() + 8, 0, 4);
	// FMemory::Memcpy(Buffer.GetData() + 12, 0, 4);
	// FMemory::Memcpy(Buffer.GetData() + 16, 0, 4);
	FMemory::Memcpy(Buffer.GetData() + 20, Message.data(), MsgSize);

	return Buffer;
}

void SocketInstance::Recv()
{
	// 接收响应
	uint32 BufferSize = 1024;
	TArray<uint8> Buffer;
	Buffer.SetNumUninitialized(BufferSize);
	int32 BytesRead = 0;
	uint32 uBytesRead = 0;
	uint32 CurrentPos;
	while(bIsRunning)
	{
		if (ClientSocket->Recv(Buffer.GetData(), BufferSize, BytesRead))
		{
			RecvBuffer.Append(Buffer.GetData(), BytesRead);
			CurrentPos = 0;
			uBytesRead = static_cast<uint32>(RecvBuffer.Num());
			while(true)
			{
				if(CurrentMsg.Num() == 0) // 没有消息在读
				{
					if(uBytesRead < 20) // 没有读到消息头
					{
						break;
					}
				
					// 读取Buffer的前4个字节，获取消息长度
					uint32 MsgSize = 0;
					FMemory::Memcpy(&MsgSize, RecvBuffer.GetData() + CurrentPos, 4);
					MsgSize = my_ntohl(MsgSize);
					// UE_LOG(LogTemp, Log, TEXT("新消息，长度: %d"), MsgSize);
					CurrentMsg.SetNumUninitialized(MsgSize);
					BytesLeft = MsgSize;
				}

				if(uBytesRead >= BytesLeft) // 当前消息全部读完
				{
					FMemory::Memcpy(CurrentMsg.GetData(), RecvBuffer.GetData() + CurrentPos, BytesLeft);
					CurrentPos += BytesLeft;
					uBytesRead -= BytesLeft;

					BytesLeft = 0;
					// UE_LOG(LogTemp, Log, TEXT("收到了消息"));
					ByteArrayQueue.Enqueue(CurrentMsg);
					CurrentMsg.Empty();
				}
				else
				{
					FMemory::Memcpy(CurrentMsg.GetData(), RecvBuffer.GetData() + CurrentPos, uBytesRead);
					CurrentPos += uBytesRead;
					uBytesRead = 0;
				
					BytesLeft -= uBytesRead;
					break;
				}
			}

			RecvBuffer.RemoveAt(0, CurrentPos);
		}
	}
}

MSG_TYPE SocketInstance::DecodeMsg(TArray<uint8>& Buffer, TArray<uint8>& Message)
{
	uint32 BufferSize = 0;
	FMemory::Memcpy(&BufferSize, Buffer.GetData(), 4);
	BufferSize = my_ntohl(BufferSize);
	MSG_TYPE Type;
	FMemory::Memcpy(&Type, Buffer.GetData() + 4, 4);
	Type = static_cast<MSG_TYPE>(my_ntohl(Type));

	uint32 MsgSize = BufferSize - 20;
	Message.SetNumUninitialized(MsgSize);

	//log
	UE_LOG(LogTemp, Log, TEXT("MsgSize1: %d, Type: %d"), MsgSize, Type);
	FMemory::Memcpy(Message.GetData(),Buffer.GetData() + 20, MsgSize);
	// UE_LOG(LogTemp, Log, TEXT("MsgSize2: %d Type: %d"), Message.Num(), Type);

	return Type;
}

MSG_TYPE SocketInstance::GetMsg(TArray<uint8>& Message)
{
	if(!bIsRunning)
	{
		return  ID_NONE;
	}
	
	TArray<uint8> Msg;
	if(ByteArrayQueue.IsEmpty())
	{
		return ID_NONE;
	}

	ByteArrayQueue.Dequeue(Msg);
	MSG_TYPE Type = DecodeMsg(Msg, Message);
	// UE_LOG(LogTemp, Log, TEXT("ByteArrayQueue MsgSize1: %d"), Msg.Num());
	// UE_LOG(LogTemp, Log, TEXT("ByteArrayQueue MsgSize2: %d"), Message.Num());
	return Type;
}

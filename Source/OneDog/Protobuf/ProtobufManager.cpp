#include "ProtobufManager.h"


std::string ProtobufManager::Encode()
{
	
	// game::Player PlayerData;
	// PlayerData.set_id(1);
	// PlayerData.set_name("PlayerOne");
	// PlayerData.set_score(100);

	// 序列化为二进制
	std::string BinaryData;
	// if (!PlayerData.SerializeToString(&BinaryData))
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Failed to serialize Player data!"));
	// }

	return BinaryData;
}

void ProtobufManager::Decode(TArray<uint8> Buffer)
{
	
	// // 1. 创建 Player 对象
	// game::Player PlayerProto;
	//
	// // 2. 解析 Protobuf 数据
	// if (PlayerProto.ParseFromArray(Buffer.GetData(), Buffer.Num()))
	// {
	// 	// 3. 获取解析后的数据
	// 	int32 PlayerID = PlayerProto.id();
	// 	FString PlayerName = UTF8_TO_TCHAR(PlayerProto.name().c_str());
	// 	int32 PlayerScore = PlayerProto.score();
	//
	// 	// 4. 打印解析结果
	// 	UE_LOG(LogTemp, Log, TEXT("Player ID: %d"), PlayerID);
	// 	UE_LOG(LogTemp, Log, TEXT("Player Name: %s"), *PlayerName);
	// 	UE_LOG(LogTemp, Log, TEXT("Player Score: %d"), PlayerScore);
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Failed to parse protobuf data!"));
	// }
}

#include "WorldCtrl.h"

#include "Network/NetManager.h"
#include "Protobuf/cl.pb.h"

void UWorldCtrl::Init()
{
	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UWorldCtrl>(ID_L2C_EnterWorld,
	this,
		&UWorldCtrl::RecvEnterWorld
	);
	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UWorldCtrl>(ID_L2C_LeaveWorld,
		this,
		&UWorldCtrl::RecvLeaveWorld
	);
	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UWorldCtrl>(ID_L2C_NotifyEnterWorld,
		this,
		&UWorldCtrl::RecvNotifyEnterWorld
	);
	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UWorldCtrl>(ID_L2C_NotifyLeaveWorld,
		this,
		&UWorldCtrl::RecvNotifyLeaveWorld
	);
}

void UWorldCtrl::SendEnterWorld(uint64 UserId)
{
	UserData::GetInstance().SetUserId(UserId);
	C2L_EnterWorld EnterWorld;
	EnterWorld.set_uid(UserId);
	Vector3* pos = new Vector3();
	pos->set_x(0);
	pos->set_y(0);
	pos->set_z(0);
	EnterWorld.set_allocated_pos(pos);
	
	// 序列化为二进制
	std::string BinaryData;
	if (!EnterWorld.SerializeToString(&BinaryData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to serialize Player data!"));
	}
	NetManager::GetInstance().Socket->Send(BinaryData, MSG_TYPE::ID_C2L_EnterWorld);
}

void UWorldCtrl::SendLeaveWorld(uint64 UserID)
{
	C2L_LeaveWorld LeaveWorld;
	LeaveWorld.set_uid(UserID);
	
	// 序列化为二进制
	std::string BinaryData;
	if (!LeaveWorld.SerializeToString(&BinaryData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to serialize Player data!"));
	}
	NetManager::GetInstance().Socket->Send(BinaryData, MSG_TYPE::ID_C2L_LeaveWorld);
}

void UWorldCtrl::RecvEnterWorld(TArray<uint8> Buffer)
{
	WorldManager::GetInstance().ChangeLevel(FName("Map_Test"));
}

void UWorldCtrl::RecvLeaveWorld(TArray<uint8> Buffer)
{
	
}

void UWorldCtrl::RecvNotifyEnterWorld(TArray<uint8> Buffer)
{
	L2C_EnterWorld EnterWorld;
	EnterWorld.ParseFromArray(Buffer.GetData(), Buffer.Num());
	uint64_t UserId = EnterWorld.uid();
	UserData* Data = &UserData::GetInstance();
	if(Data->IsMySelf(UserId) || Data->IsEnemyExist(UserId))
	{
		return;
	}

	Data->AddEnemy(UserId);
}

void UWorldCtrl::RecvNotifyLeaveWorld(TArray<uint8> Buffer)
{
	L2C_LeaveWorld LeaveWorld;
	LeaveWorld.ParseFromArray(Buffer.GetData(), Buffer.Num());
	uint64_t UserId = LeaveWorld.uid();
	UserData* Data = &UserData::GetInstance();
	if(Data->IsMySelf(UserId) || !Data->IsEnemyExist(UserId))
	{
		return;
	}

	Data->RemoveEnemy(UserId);
}



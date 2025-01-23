#include "CharacterCtrl.h"

#include "Ctrl.h"
#include "Level/Test/Level_Test.h"
#include "Network/NetManager.h"
#include "Protobuf/cl.pb.h"

void UCharacterCtrl::Init()
{
	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UCharacterCtrl>(ID_L2C_Move,
		this,
		&UCharacterCtrl::RecvMove
	);

	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UCharacterCtrl>(ID_L2C_StopMove,
		this,
		&UCharacterCtrl::RecvStopMove
	);
	
	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UCharacterCtrl>(ID_L2C_NotifyMove,
		this,
		&UCharacterCtrl::RecvNotifyMove
	);

	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UCharacterCtrl>(ID_L2C_NotifyStopMove,
		this,
		&UCharacterCtrl::RecvNotifyStopMove
	);

	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<UCharacterCtrl>(ID_L2C_NotifyPlayeStates,
		this,
		&UCharacterCtrl::RecvNotifyPlayerStates
	);
}

void UCharacterCtrl::SendMove(FVector Direction, float Speed, FVector pos)
{
	C2L_Move Move;
	uint64_t UserId = UserData::GetInstance().GetUserId();
	Move.set_uid(UserId);
	Vector3* ProtoDirection = Move.mutable_direction();
	ProtoDirection->set_x(Direction.X);
	ProtoDirection->set_y(Direction.Y);
	ProtoDirection->set_z(Direction.Z);
	Vector3* ProtoPos = Move.mutable_pos();
	ProtoPos->set_x(pos.X);
	ProtoPos->set_y(pos.Y);
	ProtoPos->set_z(pos.Z);
	Move.set_speed(Speed);
	// 序列化为二进制
	std::string BinaryData;
	if (!Move.SerializeToString(&BinaryData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to serialize Player data!"));
		return;
	}
	NetManager::GetInstance().Socket->Send(BinaryData, MSG_TYPE::ID_C2L_Move);
}

void UCharacterCtrl::SendStopMove(FVector pos)
{
	C2L_StopMove StopMove;
	StopMove.set_uid(UserData::GetInstance().GetUserId());
	Vector3* ProtoPos = StopMove.mutable_pos();
	ProtoPos->set_x(pos.X);
	ProtoPos->set_y(pos.Y);
	ProtoPos->set_z(pos.Z);
	// 序列化为二进制
	std::string BinaryData;
	if (!StopMove.SerializeToString(&BinaryData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to serialize Player data!"));
	}
	
	UE_LOG(LogTemp, Log, TEXT("Send End Pos: %f, %f, %f"), pos.X, pos.Y, pos.Z);
	NetManager::GetInstance().Socket->Send(BinaryData, MSG_TYPE::ID_C2L_StopMove);
}

void UCharacterCtrl::RecvMove(TArray<uint8> Buffer)
{
	
}

void UCharacterCtrl::RecvStopMove(TArray<uint8> Buffer)
{
	
}

void UCharacterCtrl::RecvNotifyMove(TArray<uint8> Buffer)
{
	L2C_NotifyMove NotifyMove;
	NotifyMove.ParseFromArray(Buffer.GetData(), Buffer.Num());
	uint64_t UserId = NotifyMove.uid();
	Vector3 Direction = NotifyMove.direction();
	float Speed = NotifyMove.speed();
	UserData* Data = &UserData::GetInstance();
	if(Data->IsMySelf(UserId))
	{
		return;
	}

	AActor* Actor = WorldManager::GetInstance().BaseActor;
	ALevel_Test* Test = Cast<ALevel_Test>(Actor);
	if(Test != nullptr)
	{
		FVector MoveDirection(Direction.x(), Direction.y(), Direction.z());
		Test->EnemyMove(UserId, MoveDirection, Speed);
	}
}

void UCharacterCtrl::RecvNotifyStopMove(TArray<uint8> Buffer)
{
	L2C_NotifyStopMove NotifyStopMove;
	NotifyStopMove.ParseFromArray(Buffer.GetData(), Buffer.Num());
	uint64_t UserId = NotifyStopMove.uid();
	UserData* Data = &UserData::GetInstance();
	if(Data->IsMySelf(UserId))
	{
		return;
	}

	AActor* Actor = WorldManager::GetInstance().BaseActor;
	ALevel_Test* Test = Cast<ALevel_Test>(Actor);
	if(Test != nullptr)
	{
		Test->EnemyEndMove(UserId);
	}
}

void UCharacterCtrl::RecvNotifyPlayerStates(TArray<uint8> Buffer)
{
	L2C_NotifyPlayeStates NotifyPlayerStates;
	NotifyPlayerStates.ParseFromArray(Buffer.GetData(), Buffer.Num());
	UserData* Data = &UserData::GetInstance();
	for(int i = 0; i < NotifyPlayerStates.player_states_size(); ++i)
	{
		PlayerState state = NotifyPlayerStates.player_states(i);
		int64 UserId = state.uid();
		Vector3 ProtoPos = state.pos();
		UE_LOG(LogTemp, Log, TEXT("ProtoPos: %f, %f, %f"), ProtoPos.x(), ProtoPos.y(), ProtoPos.z());
		if(UserId == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("UserId is 0"));
			continue;
		}
		if(!Data->IsMySelf(UserId) && !Data->IsEnemyExist(UserId))
		{
			Data->AddEnemy(UserId);
		}

		FVector Pos(ProtoPos.x(), ProtoPos.y(), ProtoPos.z());
		Data->UpdateEnemyPos(UserId, Pos);
	}
}







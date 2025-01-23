#include "UserData.h"
#include "OneDog/Level/Test/Level_Test.h"

void UserData::Init()
{
	EnemyCharacterDict.Empty();
}


void UserData::SetUserId(uint64_t UserId)
{
	MyUserId = UserId;
}

uint64_t UserData::GetUserId()
{
	return MyUserId;
}

bool UserData::IsMySelf(uint64_t UserId)
{
	return MyUserId == UserId;
}

bool UserData::IsEnemyExist(uint64_t EnemyId)
{
	return EnemyIdList.Contains(EnemyId);
}


void UserData::AddEnemy(uint64_t EnemyId)
{
	if(EnemyCharacterDict.Contains(EnemyId))
	{
		return;
	}
	
	EnemyIdList.Add(EnemyId);
	CharacterData* Data = new CharacterData();
	EnemyCharacterDict.Add(EnemyId, Data);
	AActor* Actor = WorldManager::GetInstance().BaseActor;
	ALevel_Test* Test = Cast<ALevel_Test>(Actor);
	if(Test != nullptr)
	{
		Test->AddEnemy(EnemyId, Data);
	}
}

void UserData::RemoveEnemy(uint64_t EnemyId)
{
	if(EnemyCharacterDict.Contains(EnemyId))
	{
		CharacterData* Data = EnemyCharacterDict[EnemyId];
		delete Data;
		EnemyCharacterDict.Remove(EnemyId);
	}
	EnemyIdList.Remove(EnemyId);

	AActor* Actor = WorldManager::GetInstance().BaseActor;
	ALevel_Test* Test = Cast<ALevel_Test>(Actor);
	if(Test != nullptr)
	{
		Test->RemoveEnemy(EnemyId);
	}
}

void UserData::UpdateEnemyPos(uint64_t EnemyId, FVector pos)
{
	if(!EnemyCharacterDict.Contains(EnemyId))
	{
		return;
	}
	
	CharacterData* Data = EnemyCharacterDict[EnemyId];
	Data->Pos = pos;
}


void UserData::Clear()
{
	MyUserId = 0;
	EnemyIdList.Empty();
	EnemyCharacterDict.Empty();
}

CharacterData* UserData::GetCharacterData(uint64_t EnemyId)
{
	return EnemyCharacterDict[EnemyId];
}

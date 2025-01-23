#pragma once
#include "CharacterData.h"
#include "../Base/Base.h"
class UserData: public SingletonBase<UserData>
{
	uint64_t MyUserId = 0;
public:
	TArray<uint64_t> EnemyIdList;
	TMap<uint64_t, CharacterData*> EnemyCharacterDict;

	void Init();
	void SetUserId(uint64_t UserId);
	uint64_t GetUserId();
	bool IsMySelf(uint64_t UserId);
	void AddEnemy(uint64_t EnemyId);
	void RemoveEnemy(uint64_t EnemyId);
	void UpdateEnemyPos(uint64_t EnemyId, FVector pos);

	bool IsEnemyExist(uint64_t EnemyId);
	
	void Clear();

	CharacterData* GetCharacterData(uint64_t EnemyId);
};

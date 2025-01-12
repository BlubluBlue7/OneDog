#pragma once
#include "SingletonBase.h"
#include "OneDog/Level/Level_Entrance.h"

class ALevel_Entrance;
class WorldManager: public SingletonBase<WorldManager>
{
public:
	UUserWidget* CurUI;
	ULevel* CurLevel;

	AActor* BaseActor;
	void ChangeUI(UUserWidget* UI);
	void ChangeLevel(FName Name);

	void Clear();
};

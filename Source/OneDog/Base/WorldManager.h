#pragma once
#include "MyGameInstance.h"
#include "SingletonBase.h"
#include "Message/MessageManager.h"
#include "OneDog/Level/Level_Entrance.h"
#include "OneDog/UI/Marriage/UI_RootLayer.h"

class ALevel_Entrance;
class UMyGameInstance;
class WorldManager: public SingletonBase<WorldManager>
{
public:
	UUserWidget* CurUI;
	ULevel* CurLevel;


	UMyGameInstance* GameInstance;

	AActor* BaseActor;
	void ChangeUI(UUserWidget* UI);
	void ChangeLevel(FName Name);

	UUI_RootLayer* RootLayer;
	void Init(UMyGameInstance* Instance);
	void SetRoot(UUI_RootLayer* Layer);
	void AddToRoot(UUI_UserWidgetBase* Layer);
	void Clear();
};

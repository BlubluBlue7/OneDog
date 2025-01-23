#include "WorldManager.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void WorldManager::Init(UMyGameInstance* Instance)
{
	GameInstance = Instance;
}

void WorldManager::ChangeUI(UUserWidget* UI)
{
	if(CurUI != nullptr)
	{
		CurUI->RemoveFromParent();
	}
	CurUI = UI;
	if(UI != nullptr)
	{
		UI->AddToViewport();
	}
}

void WorldManager::SetRoot(UUI_RootLayer* Layer)
{
	RootLayer = Layer;
	Layer->AddToViewport();
}

void WorldManager::AddToRoot(UUI_UserWidgetBase* UI)
{
	if(RootLayer == nullptr)
	{
		return;
	}

	RootLayer->AddToRoot(UI);
}

void WorldManager::ChangeLevel(FName Name)
{
	if(CurUI != nullptr)
	{
		UGameplayStatics::OpenLevel(CurUI, Name);
	}
	// BaseActor->OpenLevel(Name);
}

void WorldManager::Clear()
{

	CurUI = nullptr;
	CurLevel = nullptr;
	GameInstance = nullptr;
}




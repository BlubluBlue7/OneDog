#include "WorldManager.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


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
}




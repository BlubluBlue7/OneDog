// Fill out your copyright notice in the Description page of Project Settings.


#include "Level_Entrance.h"

#include "Kismet/GameplayStatics.h"
#include "OneDog/Network/NetManager.h"

// Sets default values
ALevel_Entrance::ALevel_Entrance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevel_Entrance::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = this->GetWorld();
	UUserWidget* Widget = UUserWidget::CreateWidgetInstance(*World, DefaultUI, FName("DefaultUI"));
	WorldManager::GetInstance().ChangeUI(Widget);
	WorldManager::GetInstance().BaseActor = this;

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = true;
	}
	
	SetLifeSpan(0);
	SetActorTickEnabled(true);
}

void ALevel_Entrance::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

// Called every frame
void ALevel_Entrance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevel_Entrance::OpenLevel(FName levelName)
{
	UGameplayStatics::OpenLevel(this, levelName);
}



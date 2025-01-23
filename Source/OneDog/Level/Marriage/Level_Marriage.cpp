// Fill out your copyright notice in the Description page of Project Settings.


#include "Level_Marriage.h"
#include "../../UI/Marriage/UI_RootLayer.h"
#include "../../UI/Marriage/UI_MainLayer.h"
// Sets default values
ALevel_Marriage::ALevel_Marriage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevel_Marriage::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = this->GetWorld();
	UUserWidget* Widget = UUserWidget::CreateWidgetInstance(*World, RootUI, FName("RootLayer"));
	UUI_RootLayer* RootLayer = Cast<UUI_RootLayer>(Widget);
	WorldManager::GetInstance().SetRoot(RootLayer);
	RootLayer->ShowLayer(DefaultUI);
	WorldManager::GetInstance().BaseActor = this;

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = true;
	}
}

// Called every frame
void ALevel_Marriage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


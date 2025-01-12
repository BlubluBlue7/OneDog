// Fill out your copyright notice in the Description page of Project Settings.


#include "Comp_GameMode.h"

// Sets default values for this component's properties
UComp_GameMode::UComp_GameMode()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComp_GameMode::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComp_GameMode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	NetManager::GetInstance().Recv();
}


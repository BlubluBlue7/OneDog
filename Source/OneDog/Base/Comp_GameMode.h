// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OneDog/Network/NetManager.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Comp_GameMode.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONEDOG_API UComp_GameMode : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComp_GameMode();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

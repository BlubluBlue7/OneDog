// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Base/Base.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Level_Entrance.generated.h"

UCLASS()
class ONEDOG_API ALevel_Entrance : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ALevel_Entrance();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> DefaultUI;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenLevel(FName levelName);
};

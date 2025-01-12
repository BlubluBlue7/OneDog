// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Base/Base.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Level_Test.generated.h"

UCLASS()
class ONEDOG_API ALevel_Test : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevel_Test();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSubclassOf<ACharacter> TestCharacterClass;

	// 用于存储生成的 BP_TestCharacter 实例
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ACharacter* MyCharacter;

	// 用于存储生成的 BP_TestCharacter 实例
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ACharacter* EnemyCharacter;

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void AddMapping();
	
	void Open();

	void AddEnemy();
	void EnemyMove(FVector Direction, float Speed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

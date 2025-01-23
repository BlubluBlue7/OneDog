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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSubclassOf<APlayerController> TestControllerClass;
	
	// 用于存储生成的 BP_TestCharacter 实例
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ACharacter* MyCharacter;

	TMap<uint64, ACharacter*> EnemyCharacterDict;

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void AddMapping();
	
	void Open();

	void AddEnemy(uint64 UserId, CharacterData* Data);
	void RemoveEnemy(uint64 UserId);
	void EnemyMove(uint64 UserId, FVector Direction, float Speed);
	void EnemyEndMove(uint64 UserId);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

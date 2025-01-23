// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OneDog/Protobuf/cl.pb.h"
#include "CoreMinimal.h"
#include "Data/CharacterData.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class ONEDOG_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ACharacterBase();
	
	FVector lastDirection;
	float lastSpeed = 0;
	int EndCount = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	CharacterData* Data = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Move")
	void Test();
	
	UFUNCTION(BlueprintCallable, Category = "Move")
	void BaseMove(FVector ForwardDirection, float ForwardSpeed, FVector RightDirection, float RightSpeed);

	UFUNCTION(BlueprintCallable, Category = "Move")
	void BaseMoveEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "Move")
	void EnemyMove();

	UFUNCTION(BlueprintImplementableEvent, Category = "Move")
	void EnemyMoveEnd();

	void SetData(CharacterData* CData);
	void TickModify();
};

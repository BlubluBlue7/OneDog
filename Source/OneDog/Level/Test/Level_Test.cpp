// Fill out your copyright notice in the Description page of Project Settings.


#include "Level_Test.h"

// Sets default values
ALevel_Test::ALevel_Test()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevel_Test::BeginPlay()
{
	Super::BeginPlay();

	FVector SpawnLocation(100, 0, 0); // 根据需要调整
	FRotator SpawnRotation(0, 0, 0); // 根据需要调整
	AActor* actor = GetWorld()->SpawnActor(TestCharacterClass, &SpawnLocation, &SpawnRotation);
	MyCharacter = Cast<ACharacter>(actor);


	
	GetWorld()->GetFirstPlayerController()->Possess(MyCharacter);

	AddMapping();
	WorldManager::GetInstance().BaseActor = this;
}

void ALevel_Test::AddEnemy()
{
	if(EnemyCharacter != nullptr)
	{
		return;
	}
	
	FVector SpawnLocation(100, 0, 0); // 根据需要调整
	FRotator SpawnRotation(0, 0, 0); // 根据需要调整
	AActor* actor = GetWorld()->SpawnActor(TestCharacterClass, &SpawnLocation, &SpawnRotation);
	EnemyCharacter = Cast<ACharacter>(actor);
}


void ALevel_Test::EnemyMove(FVector Direction, float Speed)
{
	if(EnemyCharacter == nullptr)
	{
		return;
	}

	EnemyCharacter->AddMovementInput(Direction, Speed);
}

// Called every frame
void ALevel_Test::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


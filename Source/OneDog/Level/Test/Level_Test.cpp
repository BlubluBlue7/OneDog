// Fill out your copyright notice in the Description page of Project Settings.


#include "Level_Test.h"

#include "Character/CharacterBase.h"

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

void ALevel_Test::AddEnemy(uint64 UserId, CharacterData* Data)
{
	if(EnemyCharacterDict.Contains(UserId))
	{
		return;
	}
	
	FVector SpawnLocation(100, 0, 0); // 根据需要调整
	FRotator SpawnRotation(0, 0, 0); // 根据需要调整
	AActor* actor = GetWorld()->SpawnActor(TestCharacterClass, &SpawnLocation, &SpawnRotation);
	ACharacterBase* Character = Cast<ACharacterBase>(actor);
	Character->SetData(Data);
	APlayerController* controller = Cast<APlayerController>(GetWorld()->SpawnActor(TestControllerClass, &SpawnLocation, &SpawnRotation));
	controller->Possess(Cast<APawn>(actor));
	
	EnemyCharacterDict.Add(UserId, Cast<ACharacter>(actor));
	bool t = EnemyCharacterDict.Contains(UserId);
	UE_LOG(LogTemp, Log, TEXT("AddEnemy: %s"), t ? TEXT("true") : TEXT("false"));
}

void ALevel_Test::RemoveEnemy(uint64 UserId)
{
	bool hasEnemy = EnemyCharacterDict.Contains(UserId);
	if(!hasEnemy)
	{
		return;
	}

	ACharacter* C = EnemyCharacterDict[UserId];
	C->Destroy();
	EnemyCharacterDict.Remove(UserId);
}



void ALevel_Test::EnemyMove(uint64 UserId, FVector Direction, float Speed)
{
	bool hasEnemy = EnemyCharacterDict.Contains(UserId);
	if(!hasEnemy)
	{
		return;
	}

	CharacterData* Data = UserData::GetInstance().GetCharacterData(UserId);
	if(!Data)
	{
		return;
	}
	Data->Direction = Direction;
	Data->Speed = Speed;
	Data->isMoving = true;
	// Direction.X = 1;
	// Direction.Y = 0;
	// Direction.Z = 0;
	// Speed = 1;
	ACharacter* C = EnemyCharacterDict[UserId];
	ACharacterBase* EnemyCharacter = Cast<ACharacterBase>(C);
	if(EnemyCharacter != nullptr)
	{
		EnemyCharacter->EnemyMove();
	}
}

void ALevel_Test::EnemyEndMove(uint64 UserId)
{
	bool hasEnemy = EnemyCharacterDict.Contains(UserId);
	if(!hasEnemy)
	{
		return;
	}

	CharacterData* Data = UserData::GetInstance().GetCharacterData(UserId);
	if(!Data || !Data->isMoving)
	{
		return;
	}
	Data->isMoving = false;

	ACharacter* C = EnemyCharacterDict[UserId];
	ACharacterBase* EnemyCharacter = Cast<ACharacterBase>(C);
	if(EnemyCharacter != nullptr)
	{
		EnemyCharacter->EnemyMoveEnd();
	}
}


// Called every frame
void ALevel_Test::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (const auto& Pair : EnemyCharacterDict)
	{
		int64_t UserId = Pair.Key;
		CharacterData* Data = UserData::GetInstance().GetCharacterData(UserId);
		if(Data != nullptr && Data->isMoving)
		{
			ACharacter* Character = Pair.Value;
			Character->AddMovementInput(Data->Direction, Data->Speed);
		}
	}
}


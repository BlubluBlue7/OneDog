// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "Ctrl/Ctrl.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OneDog/Network/NetManager.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
	UCharacterMovementComponent* CharacterMovement1 = GetCharacterMovement();
	UE_LOG(LogTemp, Log, TEXT("BrakingDecelerationWalking: %f, GroundFriction: %f, MaxAcceleration: %f"), CharacterMovement1->BrakingDecelerationWalking, CharacterMovement1->GroundFriction, CharacterMovement1->MaxAcceleration);
	CharacterMovement1->SetMovementMode(EMovementMode::MOVE_Walking);
	CharacterMovement1->BrakingDecelerationWalking = 40960.0f;  // 增大减速度
	CharacterMovement1->GroundFriction = 8.0f;  // 增大摩擦力
	CharacterMovement1->MaxAcceleration = 512.0f;  // 减小加速度
	// GetOwner()->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickModify();
	if(EndCount > 0)
	{
		EndCount--;
		FVector pos = GetActorLocation();
		UE_LOG(LogTemp, Log, TEXT("Send Tick Pos: %f, %f, %f, %d"), pos.X, pos.Y, pos.Z, EndCount);
		Ctrl::GetInstance().Character->SendStopMove(pos);
	}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::Test()
{
}

void ACharacterBase::BaseMove(FVector ForwardDirection, float ForwardSpeed, FVector RightDirection, float RightSpeed)
{
	// 计算整体方向
	FVector OverallDirection = (ForwardDirection * ForwardSpeed) + (RightDirection * RightSpeed);

	// 计算整体速度
	float OverallSpeed = FMath::Sqrt(FMath::Square(ForwardSpeed) + FMath::Square(RightSpeed));

	// 归一化整体方向（可选）
	OverallDirection.Normalize();
	
	FVector Direction = OverallDirection;
	float Speed = OverallSpeed;
	
	if(Direction.Equals(lastDirection) && Speed == lastSpeed)
	{
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("X: %f, Y: %f, Z: %f Speed: %f"), Direction.X, Direction.Y, Direction.Z, Speed);
	EndCount = 0;
	lastDirection = Direction;
	lastSpeed = Speed;

	FVector pos = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Send Pos: %f, %f, %f"), pos.X, pos.Y, pos.Z);
	Ctrl::GetInstance().Character->SendMove(Direction, Speed, pos);
}

void ACharacterBase::BaseMoveEnd()
{
	EndCount = 1;
	lastSpeed = 0;
	lastDirection.Set(0, 0, 0);

	FVector pos = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Send Pos: %f, %f, %f"), pos.X, pos.Y, pos.Z);
	Ctrl::GetInstance().Character->SendStopMove(pos);
}

void ACharacterBase::SetData(CharacterData* CData)
{
	this->Data = CData;
}

void ACharacterBase::TickModify()
{
	if(Data == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Tick Modify"));
	FVector CurPos = GetActorLocation();
	FVector TargetPos = Data->Pos;
	FVector Direction = TargetPos - CurPos;
	Direction.Z = 0;
	float Size = Direction.Size();
	UE_LOG(LogTemp, Log, TEXT("CurPos: %f, %f, %f"), CurPos.X, CurPos.Y, CurPos.Z);
	UE_LOG(LogTemp, Log, TEXT("TargetPos: %f, %f, %f"), TargetPos.X, TargetPos.Y, TargetPos.Z);
	UE_LOG(LogTemp, Log, TEXT("Direction: %f, %f, %f"), Direction.X, Direction.Y, Direction.Z);
	UE_LOG(LogTemp, Log, TEXT("Size: %f"), Size);
	if(Size > 0.01)
	{
		Direction.Normalize();
		if(Data->isMoving)
		{
			AddMovementInput(Direction, FMath::Abs(Data->Speed));
		}
		else
		{
			float Speed = 1;
			AddMovementInput(Direction, Speed);
		}
	}
}

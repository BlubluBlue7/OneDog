// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OneDog/Data/Marriage/Data_Role.h"
#include "UObject/NoExportTypes.h"
#include "UData_Role.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUData_Role : public UObject
{
	GENERATED_BODY()
public:
	UData_Role* Role = nullptr;
	FString Name;
	int Age = 0;
	int Height = 0;
	int Weight = 0;
	char Sex = 0;
	FString Hobby;
	FString Des;
	bool IsSelect = false;
};

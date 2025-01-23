// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OneDog/Data/Marriage/Data_Couple.h"
#include "UObject/NoExportTypes.h"
#include "UData_Couple.generated.h"

/**
 * 
 */
UCLASS()
class ONEDOG_API UUData_Couple : public UObject
{
	GENERATED_BODY()
public:
	Data_Couple* CoupleData;
};

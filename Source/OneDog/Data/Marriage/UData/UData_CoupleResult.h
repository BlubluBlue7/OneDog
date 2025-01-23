#pragma once

#include "CoreMinimal.h"
#include "OneDog/Data/Marriage/Data_Couple.h"
#include "UObject/NoExportTypes.h"
#include "UData_CoupleResult.generated.h"
class Data_Couple;
UCLASS()
class ONEDOG_API UUData_CoupleResult : public UObject
{
	GENERATED_BODY()
public:
	Data_Couple* CoupleData;
	FString Des;
};

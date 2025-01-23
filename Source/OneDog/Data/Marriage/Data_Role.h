#pragma once
#include "Data_Base.h"
#include "Data_Couple.h"
// #include "CoreMinimal.h"
// #include "Data_Role.generated.h"
// UCLASS()
class Data_Couple;
class UData_Role: public UData_Base
{
	// GENERATED_BODY()
public:
	Data_Couple* Couple = nullptr;
	FString Name;
	int Age = 0;
	int Height = 0;
	int Weight = 0;
	char Sex = 0;
	FString Hobby;
	FString Des;
	void InitFromJson(TSharedPtr<FJsonObject> Json);

	FString GetDes();
};

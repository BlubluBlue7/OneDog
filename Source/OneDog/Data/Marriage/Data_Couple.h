#pragma once
#include "Data_Role.h"
#include "UData/UData_CoupleResult.h"

class UData_Role;
class UUData_CoupleResult;
class Data_Couple
{
public:
	UData_Role* Male;
	UData_Role* Female;
	TArray<FString> ResultList;
	Data_Couple(UData_Role* A, UData_Role* B);

	TArray<UUData_CoupleResult*> GetResult();
	void AddResult(FString Result);
};

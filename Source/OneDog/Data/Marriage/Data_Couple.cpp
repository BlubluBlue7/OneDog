#include "Data_Couple.h"

Data_Couple::Data_Couple(UData_Role* A, UData_Role* B)
{
	Male = A;
	Female = B;
	A->Couple = this;
	B->Couple = this;
}

TArray<UUData_CoupleResult*> Data_Couple::GetResult()
{
	TArray<UUData_CoupleResult*> Result;
	for(int i = 0; i < ResultList.Num(); i++)
	{
		UUData_CoupleResult* Temp = NewObject<UUData_CoupleResult>();
		Temp->CoupleData = this;
		Temp->Des = ResultList[i];
		Result.Add(Temp);
	}

	return Result;
}

void Data_Couple::AddResult(FString Result)
{
	ResultList.Add(Result);
}
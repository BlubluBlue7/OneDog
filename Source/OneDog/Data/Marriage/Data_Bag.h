#pragma once
#include "Data_Base.h"
#include "Data_Couple.h"
#include "Data_Role.h"
#include "UData/UData_Couple.h"
#include "UData/UData_Role.h"
// #include "CoreMinimal.h"
// #include "Data_Bag.generated.h"
// UCLASS()
class UData_Bag: public UData_Base
{

	// GENERATED_BODY()
public:
	// UPROPERTY()
	TArray<UData_Role*> Roles;
	TArray<Data_Couple*> Couples;
	void Init() override;

	void AddRole(UData_Role* Role);
	void AddCouple(UData_Role* Male, UData_Role* Female);

	TArray<UUData_Role*> GetRoleListBySex(char Sex);
	TArray<UUData_Couple*> GetCoupleList();
};

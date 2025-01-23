#include "Data_Bag.h"


void UData_Bag::Init()
{
	for (auto Role : Roles)
	{
		delete Role;
	}
	Roles.Empty();

	for(auto Couple: Couples)
	{
		delete Couple;
	}
	Couples.Empty();
}

void UData_Bag::AddRole(UData_Role* Role)
{
	Roles.Add(Role);
}

void UData_Bag::AddCouple(UData_Role* Male, UData_Role* Female)
{
	if(Male->Couple != nullptr || Female->Couple != nullptr)
	{
		return;
	}
	
	Data_Couple* Couple = new Data_Couple(Male, Female);
	Couples.Add(Couple);
}


TArray<UUData_Role*> UData_Bag::GetRoleListBySex(char Sex)
{
	TArray<UUData_Role*> List;
	for (auto Role : Roles)
	{
		if (Role->Sex == Sex && Role->Couple == nullptr)
		{
			UUData_Role* URole = NewObject<UUData_Role>();
			URole->Role = Role;
			URole->Name = Role->Name;
			URole->Age = Role->Age;
			URole->Height = Role->Height;
			URole->Weight = Role->Weight;
			URole->Sex = Role->Sex;
			URole->Hobby = Role->Hobby;
			URole->Des = Role->Des;
			List.Add(URole);
		}
	}

	return List;
}

TArray<UUData_Couple*> UData_Bag::GetCoupleList()
{
	TArray<UUData_Couple*> List;
	for (auto Couple : Couples)
	{
		UUData_Couple* UCouple = NewObject<UUData_Couple>();
		UCouple->CoupleData = Couple;
		List.Add(UCouple);
	}

	return List;
}
		

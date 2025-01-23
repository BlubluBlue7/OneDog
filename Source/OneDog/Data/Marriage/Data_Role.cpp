#include "Data_Role.h"

void UData_Role::InitFromJson(TSharedPtr<FJsonObject> Json)
{
	Name = Json->GetStringField("Name");
	Age = Json->GetIntegerField("Age");
	Height = Json->GetIntegerField("Height");
	Weight = Json->GetIntegerField("Weight");
	Sex = Json->GetIntegerField("Sex");
	Hobby = Json->GetStringField("Hobby");
	Des = Json->GetStringField("Des");
}

FString UData_Role::GetDes()
{
	FString SexDes = Sex == 1 ? TEXT("男") : TEXT("女");
	FString TotalDes = "姓名：" + Name + "，年龄：" + FString::Printf(TEXT("%d"), Age) + "，性别：" + SexDes + "，身高："
		+ FString::Printf(TEXT("%d"), Height) + "，体重：" + FString::Printf(TEXT("%d"), Weight)
		+ "，职业：" + Hobby + "，信息：" + Des;
	return TotalDes;
}
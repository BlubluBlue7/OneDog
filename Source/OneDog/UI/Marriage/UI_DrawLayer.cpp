// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_DrawLayer.h"

#include "Data/Marriage/Data_Manager.h"
#include "Tools/DeepSeek.h"
#include <random>

void UUI_DrawLayer::NativeConstruct()
{
	Super::NativeConstruct();

	// 使用随机数引擎和分布
	std::random_device rd;  // 获取硬件随机数种子
	std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
	std::uniform_int_distribution<int32_t> dist(INT32_MIN, INT32_MAX); // 设置生成范围为int32_t的最小和最大值

	// 生成一个随机的int32数
	int32_t random_num = dist(gen);
	
	FString systemStr = TEXT("角色信息生成。规则：1. 随机生成以下属性：姓名：随机中文名字。年龄：18 到 50 之间的随机整数。性别：1表示男2表示女。身高：150 到 190 之间的随机整数。体重：45 到 100 之间的随机整数。职业：随机。信息：随机生成家庭背景、性格、爱好。直接返回Json格式，示例：{\"Name\":\"姓名\",\"Age\":18,\"Sex\":\"1\",\"Height\":160,\"Weight\":50,\"Hobby\":\"职业\",\"Des\":\"随机生成家庭背景、性格、爱好，30字左右\"}");
	FString userStr = TEXT("有创意，多样，好坏皆有，信息要结合性别来确定。本次随机种子为") + FString::FromInt(random_num);
	// Role = NewObject<UData_Role>();
	Role = new UData_Role();
	DeepSeek::GetInstance().CallDeepSeekAPI(systemStr, userStr,[this](int ret, const FString& msg)
	{
		//删去msg{之前的内容
		int32 index = msg.Find(TEXT("{"));
		FString realMsg = msg.RightChop(index);
		//删去msg}之后的内容
		index = realMsg.Find(TEXT("}"));
		realMsg = realMsg.Left(index + 1);
		
		//msg 转换成json
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(realMsg);
		if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			Role->InitFromJson(JsonObject);
			Text_Name->SetText(FText::FromString(Role->Name));
			Text_Age->SetText(FText::FromString(FString::Printf(TEXT("%d"), Role->Age)));
			Text_Sex->SetText(Role->Sex == 1 ? FText::FromString(TEXT("男")) : FText::FromString(TEXT("女")));
			Text_Height->SetText(FText::FromString(FString::Printf(TEXT("%d"), Role->Height)));
			Text_Weight->SetText(FText::FromString(FString::Printf(TEXT("%d"), Role->Weight)));
			Text_Hobby->SetText(FText::FromString(Role->Hobby));
			Text_Des->SetText(FText::FromString(Role->Des));
		}
	});
}

void UUI_DrawLayer::Confirm()
{
	if (Role)
	{
		Data_Manager::GetInstance().Bag->AddRole(Role);
		Role = nullptr;
	}

	Close();
}


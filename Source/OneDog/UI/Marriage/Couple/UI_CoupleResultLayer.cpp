// Fill out your copyright notice in the Description page of Project Settings.


#include "OneDog/UI/Marriage/Couple/UI_CoupleResultLayer.h"

#include "Components/ListView.h"
#include "Tools/DeepSeek.h"

void UUI_CoupleResultLayer::UpdateCouple(UUData_Couple* Data)
{
	CoupleData = Data;

	UData_Role* MaleData = Data->CoupleData->Male;
	UData_Role* FemaleData = Data->CoupleData->Female;
	Text_MaleName->SetText(FText::FromString(MaleData->Name));
	Text_MaleDes->SetText(FText::FromString(MaleData->Des));
	Text_FemaleName->SetText(FText::FromString(FemaleData->Name));
	Text_FemaleDes->SetText(FText::FromString(FemaleData->Des));

	ResultList = Data->CoupleData->GetResult();
	ListView_Result->SetListItems(ResultList);
}

void UUI_CoupleResultLayer::Add()
{
	FString MaleDes = CoupleData->CoupleData->Male->GetDes();
	FString FemaleDes = CoupleData->CoupleData->Female->GetDes();
	FString systemStr = TEXT("根据男女双方的信息，生成他们在一起之后的故事。男生的信息是：") + MaleDes + TEXT("，女生的信息是：") + FemaleDes;
	FString userStr = TEXT("");
	for (auto Result : CoupleData->CoupleData->ResultList)
	{
		userStr += Result + TEXT("。");
	}
	userStr += TEXT("结合以上信息生成他们在一起以后的一段故事，100字以内。");
	DeepSeek::GetInstance().CallDeepSeekAPI(systemStr, userStr,[this](int ret, const FString& msg)
	{
		CoupleData->CoupleData->AddResult(msg);
		ResultList = CoupleData->CoupleData->GetResult();
		ListView_Result->SetListItems(ResultList);
	});
}

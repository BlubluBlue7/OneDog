#pragma once
#include "CtrlBase.h"
#include "Base/Base.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LoginCtrl.generated.h"

UCLASS()
class ONEDOG_API ULoginCtrl : public UCtrlBase
{
	GENERATED_BODY()
public:
	void Init() override;
	void SendLogin(FString& account, FString& password);
	void SendCreateAccount(FString& account, FString& password);

	void RecvLogin(TArray<uint8> Buffer);
	void RecvCreateAccount(TArray<uint8> Buffer);
};

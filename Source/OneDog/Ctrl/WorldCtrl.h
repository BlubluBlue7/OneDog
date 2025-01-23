#pragma once
#include "CtrlBase.h"
#include "Base/Base.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldCtrl.generated.h"

UCLASS()
class ONEDOG_API UWorldCtrl : public UCtrlBase
{
	GENERATED_BODY()
public:
	void Init() override;
	void SendEnterWorld(uint64 UserId);
	void SendLeaveWorld(uint64 UserId);

	void RecvEnterWorld(TArray<uint8> Buffer);
	void RecvLeaveWorld(TArray<uint8> Buffer);
	void RecvNotifyEnterWorld(TArray<uint8> Buffer);
	void RecvNotifyLeaveWorld(TArray<uint8> Buffer);
};

#pragma once
#include "CtrlBase.h"
#include "Base/Base.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCtrl.generated.h"

UCLASS()
class ONEDOG_API UCharacterCtrl : public UCtrlBase
{
	GENERATED_BODY()
public:
	void Init() override;
	void SendMove(FVector Direction, float Speed, FVector pos);
	void SendStopMove(FVector pos);

	void RecvMove(TArray<uint8> Buffer);
	void RecvStopMove(TArray<uint8> Buffer);
	void RecvNotifyMove(TArray<uint8> Buffer);
	void RecvNotifyStopMove(TArray<uint8> Buffer);
	void RecvNotifyPlayerStates(TArray<uint8> Buffer);
};

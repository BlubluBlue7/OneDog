#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CtrlBase.generated.h"

UCLASS()
class ONEDOG_API UCtrlBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Init();
};

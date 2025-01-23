#pragma once
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
// #include "CoreMinimal.h"
// #include "Data_Base.generated.h"

//UCLASS()
//class UData_Base: public UObject
class UData_Base
{
	//GENERATED_BODY()
public:
	// 虚析构函数
	virtual ~UData_Base() = default;
	
	virtual void Init();
};

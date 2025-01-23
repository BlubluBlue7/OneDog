#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MessageManager.generated.h"

// 定义消息委托类型
DECLARE_DELEGATE_OneParam(FMessageDelegate, const TArray<TSharedPtr<void>>& /*PayloadArray*/);

/**
 * 消息管理器
 */
UCLASS()
class ONEDOG_API UMessageManager : public UObject
{
	GENERATED_BODY()

public:
	UMessageManager();
	~UMessageManager();
	// 注册消息接收器
	template <typename T, typename... PayloadTypes>
	void RegisterMessageReceiver(int32 Key, T* Object, void (T::*Callback)(PayloadTypes...));

	// 发送消息
	template <typename... PayloadTypes>
	void SendMessage(int32 Key, PayloadTypes&&... Payload);

	// 按对象反注册
	void UnregisterMessageReceiverByObject(UObject* Object);

private:
	// 保存消息的接收器列表
	TMap<int32, TArray<FMessageDelegate>> MessageReceivers;

	// 保存对象与 Key 的映射
	TMap<UObject*, TArray<int32>> ObjectToKeysMap;
};

template <typename T, typename... PayloadTypes>
void UMessageManager::RegisterMessageReceiver(int32 Key, T* Object, void (T::*Callback)(PayloadTypes...))
{
	// 创建委托
	FMessageDelegate Delegate;
	Delegate.BindLambda([Object, Callback](const TArray<TSharedPtr<void>>& PayloadArray)
	{
		// 检查参数数量
		if (PayloadArray.Num() != sizeof...(PayloadTypes))
		{
			UE_LOG(LogTemp, Error, TEXT("Payload count mismatch. Expected: %d, Actual: %d"),
				sizeof...(PayloadTypes), PayloadArray.Num());
			return;
		}

		// 解包参数并调用回调
		int32 Index = 0;
		(Object->*Callback)(
			*StaticCastSharedPtr<std::decay_t<PayloadTypes>>(PayloadArray[Index++])...
		);
	});

	// 注册到消息接收器
	if (!MessageReceivers.Contains(Key))
	{
		MessageReceivers.Add(Key, TArray<FMessageDelegate>());
	}
	MessageReceivers[Key].Add(Delegate);

	// 注册对象与 Key 的映射
	if (!ObjectToKeysMap.Contains(Object))
	{
		ObjectToKeysMap.Add(Object, TArray<int32>());
	}
	ObjectToKeysMap[Object].Add(Key);
}

template <typename... PayloadTypes>
void UMessageManager::SendMessage(int32 Key, PayloadTypes&&... Payload)
{
	// 构造消息的有效载荷
	TArray<TSharedPtr<void, ESPMode::ThreadSafe>> PayloadArray;
	(..., PayloadArray.Add(MakeShared<std::decay_t<PayloadTypes>>(Forward<PayloadTypes>(Payload))));

	// 检查是否有接收器
	if (!MessageReceivers.IsEmpty() && MessageReceivers.Contains(Key))
	{
		for (const FMessageDelegate& Delegate : MessageReceivers[Key])
		{
			Delegate.ExecuteIfBound(PayloadArray);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No receiver found for key: %d"), Key);
	}
}
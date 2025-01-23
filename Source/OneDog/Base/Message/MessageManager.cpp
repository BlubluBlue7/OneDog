#include "MessageManager.h"

UMessageManager::UMessageManager()
{
    // 初始化
    UE_LOG(LogTemp, Log, TEXT("--------------------------------------------------------------构造UMessageManager::UMessageManager"));
}

UMessageManager::~UMessageManager()
{
    UE_LOG(LogTemp, Log, TEXT("---------------------------------------------------------------析构~UMessageManager::UMessageManager"));
    ObjectToKeysMap.Empty();
    MessageReceivers.Empty();
}
void UMessageManager::UnregisterMessageReceiverByObject(UObject* Object)
{
    // 查找对象注册的所有 Key
    if (ObjectToKeysMap.Contains(Object))
    {
        for (int32 Key : ObjectToKeysMap[Object])
        {
            // 移除与该对象相关的所有回调
            if (MessageReceivers.Contains(Key))
            {
                TArray<FMessageDelegate>& Delegates = MessageReceivers[Key];
                Delegates.RemoveAll([Object](const FMessageDelegate& Delegate)
                {
                    return Delegate.GetUObject() == Object;
                });

                // 如果该 Key 没有回调，移除 Key
                if (Delegates.Num() == 0)
                {
                    MessageReceivers.Remove(Key);
                }
            }
        }

        // 移除对象的记录
        ObjectToKeysMap.Remove(Object);
    }
}

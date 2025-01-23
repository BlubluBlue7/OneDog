#pragma once
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Dom/JsonObject.h"
#include "OneDog/Base/SingletonBase.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"


class DeepSeek: public SingletonBase<DeepSeek>
{
public:
	//CallDeepSeekAPI 参数为字符串，和返回字符串的回调函数
	void CallDeepSeekAPI(FString systemStr, FString userStr, TFunction<void(int ret, const FString&)> Callback);
	void ParseResponse(const FString& ResponseString);

	//记录回调函数
	TFunction<void(int ret, const FString&)> CurCallback;
	void Clear();
};

#include "DeepSeek.h"


static FString CreateRequestBody(const TArray<TSharedPtr<FJsonValue>>& Messages)
{
	// Create the root JSON object
	TSharedPtr<FJsonObject> RequestBodyObject = MakeShared<FJsonObject>();

	// Set the "model" field
	RequestBodyObject->SetStringField("model", "deepseek-chat");
	RequestBodyObject->SetNumberField("temperature", 2.0f);

	// Set the "messages" field
	TArray<TSharedPtr<FJsonValue>> MessagesArray;
	for (const TSharedPtr<FJsonValue>& Message : Messages)
	{
		MessagesArray.Add(Message);
	}
	RequestBodyObject->SetArrayField("messages", MessagesArray);

	// // Set the "stream" field
	// RequestBodyObject->SetBoolField("stream", false);

	// Serialize the JSON object to a string
	FString RequestBody;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestBodyObject.ToSharedRef(), JsonWriter);

	return RequestBody;
}

void DeepSeek::CallDeepSeekAPI(FString systemStr, FString userStr, TFunction<void(int ret, const FString&)> Callback)
{
	if(CurCallback)
	{
		Callback(0, "");
		return;
	}
	CurCallback = Callback;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(TEXT("https://api.deepseek.com/chat/completions"));
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetHeader(TEXT("Authorization"), TEXT("Bearer sk-20a1beee7dfc40c193caddcda2250b23")); // 替换为你的 API Key
	HttpRequest->SetTimeout(15);
	TSharedPtr<FJsonObject> SystemMessage = MakeShared<FJsonObject>();
	SystemMessage->SetStringField("role", "system");
	SystemMessage->SetStringField("content", systemStr);
	TSharedPtr<FJsonObject> UserMessage = MakeShared<FJsonObject>();
	UserMessage->SetStringField("role", "user");
	UserMessage->SetStringField("content", userStr);
	
	TArray<TSharedPtr<FJsonValue>> Messages;
	Messages.Add(MakeShared<FJsonValueObject>(SystemMessage));
	Messages.Add(MakeShared<FJsonValueObject>(UserMessage));
	FString RequestBody = CreateRequestBody(Messages);
	
	HttpRequest->SetContentAsString(RequestBody);
	HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			FString ResponseString = Response->GetContentAsString();
			ParseResponse(ResponseString);
		}
		else
		{
			CurCallback(0, "");
			CurCallback = nullptr;
			UE_LOG(LogTemp, Error, TEXT("Request failed!"));
		}
	});

	HttpRequest->ProcessRequest();
}

void DeepSeek::ParseResponse(const FString& ResponseString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		FString AssistantMessage = JsonObject->GetArrayField("choices")[0]->AsObject()->GetObjectField("message")->GetStringField("content");
		CurCallback(1, AssistantMessage);
		CurCallback = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response!"));
		CurCallback(0, "");
		CurCallback = nullptr;
	}
}

void DeepSeek::Clear()
{
	CurCallback = nullptr;
}

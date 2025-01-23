#include "LoginCtrl.h"

#include "Ctrl.h"
#include "Network/NetManager.h"
#include "Protobuf/cl.pb.h"

void ULoginCtrl::Init()
{
	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<ULoginCtrl>(ID_L2C_Login,
		this,
		&ULoginCtrl::RecvLogin
	);

	WorldManager::GetInstance().GameInstance->M->RegisterMessageReceiver<ULoginCtrl>(ID_L2C_CreateAccount,
		this,
		&ULoginCtrl::RecvCreateAccount
	);
}

void ULoginCtrl::SendLogin(FString& account, FString& password)
{
	C2L_Login Login;
	std::string AccountStdString = TCHAR_TO_UTF8(*account);
	std::string PasswordStdString = TCHAR_TO_UTF8(*password);
	Login.set_account(AccountStdString);
	Login.set_password(PasswordStdString);
	
	// 序列化为二进制
	std::string BinaryData;
	if (!Login.SerializeToString(&BinaryData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to serialize Player data!"));
	}
	NetManager::GetInstance().Socket->Send(BinaryData, MSG_TYPE::ID_C2L_Login);	
}

void ULoginCtrl::SendCreateAccount(FString& account, FString& password)
{
	C2L_CreateAccount CreateAccount;
	std::string AccountStdString = TCHAR_TO_UTF8(*account);
	std::string PasswordStdString = TCHAR_TO_UTF8(*password);
	CreateAccount.set_account(AccountStdString);
	CreateAccount.set_password(PasswordStdString);
	
	// 序列化为二进制
	std::string BinaryData;
	if (!CreateAccount.SerializeToString(&BinaryData))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to serialize Player data!"));
	}
	NetManager::GetInstance().Socket->Send(BinaryData, MSG_TYPE::ID_C2L_CreateAccount);
}

void ULoginCtrl::RecvLogin(TArray<uint8> Buffer)
{
	L2C_Login Login;
	Login.ParseFromArray(Buffer.GetData(), Buffer.Num());
	std::string Account = Login.account();
	std::string Password = Login.password();
	uint64_t UserId = Login.uid();
	Ctrl::GetInstance().World->SendEnterWorld(UserId);
}

void ULoginCtrl::RecvCreateAccount(TArray<uint8> Buffer)
{
	L2C_CreateAccount CreateAccount;
	CreateAccount.ParseFromArray(Buffer.GetData(), Buffer.Num());
	std::string Account = CreateAccount.account();
	std::string Password = CreateAccount.password();
	uint64 UID = CreateAccount.uid();
	
	UE_LOG(LogTemp, Log, TEXT("Account: %s, Password: %s, UID: %d"), UTF8_TO_TCHAR(Account.c_str()), UTF8_TO_TCHAR(Password.c_str()), UID);
}



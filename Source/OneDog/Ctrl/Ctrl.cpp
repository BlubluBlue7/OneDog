#include "Ctrl.h"
#include "Protobuf/cl.pb.h"

void Ctrl::Init()
{
	Login = NewObject<ULoginCtrl>();
	Login->Init();

	World = NewObject<UWorldCtrl>();
	World->Init();

	Character = NewObject<UCharacterCtrl>();
	Character->Init();
}
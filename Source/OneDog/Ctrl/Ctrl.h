#pragma once
#include "CharacterCtrl.h"
#include "LoginCtrl.h"
#include "WorldCtrl.h"

class Ctrl: public SingletonBase<Ctrl>
{
public:
	ULoginCtrl* Login;
	UWorldCtrl* World;
	UCharacterCtrl* Character;
	void Init();
};

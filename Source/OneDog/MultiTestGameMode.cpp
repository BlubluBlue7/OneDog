// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiTestGameMode.h"
#include "character/MultiTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiTestGameMode::AMultiTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/James/BP_James2"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

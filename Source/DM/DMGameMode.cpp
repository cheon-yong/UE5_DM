// Copyright Epic Games, Inc. All Rights Reserved.

#include "DMGameMode.h"
#include "DMCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADMGameMode::ADMGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

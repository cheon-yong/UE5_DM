// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/DMGameMode.h"
#include "Character/DMCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Game/DMGameStateBase.h"

ADMGameMode::ADMGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ADMGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ADMGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
}



void ADMGameMode::AddScore(ADMPlayerController* ScoredPlayer)
{
	if (ADMGameStateBase* DMGameState = Cast<ADMGameStateBase>(GameState))
	{
		DMGameState->AddGameScore();
	}
}

int32 ADMGameMode::GetScore() const
{
	return int32();
}

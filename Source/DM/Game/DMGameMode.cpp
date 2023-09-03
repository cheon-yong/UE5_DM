// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/DMGameMode.h"
#include "Character/DMCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Game/DMGameStateBase.h"
#include "Controller/DMPlayerController.h"

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

void ADMGameMode::AddScore(AActor* ScoredPlayer)
{
	if (ADMGameStateBase* DMGameState = Cast<ADMGameStateBase>(GameState))
	{
		DMGameState->AddGameScore();

		int32 NowScore = DMGameState->GetTotalGameScore();
		OnUpdateScore.Broadcast(NowScore);
		if (NowScore >= ScoreToClear)
		{
			DMGameState->SetGameState(EGameState::Clear);
		}
	}
}

void ADMGameMode::SetGameState(EGameState NewState)
{
	if (ADMGameStateBase* DMGameState = Cast<ADMGameStateBase>(GameState))
	{
		if (DMGameState->GetGameState() == NewState)
			return;

		DMGameState->SetGameState(NewState);
		OnChangeGameState.Broadcast(NewState);
	}
}

int32 ADMGameMode::GetScore() const
{
	if (ADMGameStateBase* DMGameState = Cast<ADMGameStateBase>(GameState))
	{
		return DMGameState->GetTotalGameScore();
	}

	return 0;
}

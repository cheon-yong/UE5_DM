// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DMGameStateBase.h"

ADMGameStateBase::ADMGameStateBase()
{
	TotalGameScore = 0;
	GameState = EGameState::Ready;
}

int32 ADMGameStateBase::GetTotalGameScore() const
{
	return TotalGameScore;
}

void ADMGameStateBase::AddGameScore()
{
	TotalGameScore++;
}

void ADMGameStateBase::SetGameState(EGameState NewState)
{
	if (GameState == NewState)
		return;

	GameState = NewState;
}

bool ADMGameStateBase::IsGameCleared() const
{
	if (GameState == EGameState::Clear)
		return true;

	return false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/GameOverWidgetController.h"
#include "Game/DMGameMode.h"

void UGameOverWidgetController::BroadcastInitialValues()
{
}

void UGameOverWidgetController::BindCallbacksToDependencies()
{
}

void UGameOverWidgetController::OnClickGameRestartButton()
{
	auto GameMode = GetWorld()->GetAuthGameMode();
	if (ADMGameMode* DMGameMode = Cast<ADMGameMode>(GameMode))
	{
		DMGameMode->SetGameState(EGameState::Playing);
	}
}

void UGameOverWidgetController::OnClickTitleButton()
{
	auto GameMode = GetWorld()->GetAuthGameMode();
	if (ADMGameMode* DMGameMode = Cast<ADMGameMode>(GameMode))
	{
		DMGameMode->SetGameState(EGameState::Ready);
	}
}

void UGameOverWidgetController::OnClickGameExitButton()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/IntroWidgetController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/HUD/DMHUD.h"
#include "UI/Widget/DMUserWidget.h"

void UIntroWidgetController::BroadcastInitialValues()
{
}

void UIntroWidgetController::BindCallbacksToDependencies()
{
}

void UIntroWidgetController::OnClickGameStartButton()
{
	auto GameMode = GetWorld()->GetAuthGameMode();
	if (ADMGameMode* DMGameMode = Cast<ADMGameMode>(GameMode))
	{
		DMGameMode->SetGameState(EGameState::Playing);
	}
}

void UIntroWidgetController::OnClickGameExitButton()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

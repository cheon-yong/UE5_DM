// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/IntroWidgetController.h"
#include "Game/DMGameMode.h"

void UIntroWidgetController::BroadcastInitialValues()
{
}

void UIntroWidgetController::BindCallbacksToDependencies()
{
	auto GameMode = GetWorld()->GetAuthGameMode();
	if (ADMGameMode* DMGameMode = Cast<ADMGameMode>(GameMode))
	{
		//DMGameMode->OnChangeGameState.AddDynamic
	}
}

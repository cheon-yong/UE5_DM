// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/IntroWidgetController.h"
#include "Game/DMGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/HUD/DMHUD.h"
#include "UI/Widget/DMUserWidget.h"

void UIntroWidgetController::BroadcastInitialValues()
{
}

void UIntroWidgetController::BindCallbacksToDependencies()
{
	auto GameMode = GetWorld()->GetAuthGameMode();
	if (ADMGameMode* DMGameMode = Cast<ADMGameMode>(GameMode))
	{
		DMGameMode->OnChangeGameState.AddDynamic(this, &UIntroWidgetController::AttachOrDetachWidget);
	}
}

void UIntroWidgetController::AttachOrDetachWidget(EGameState NewState)
{
	switch (NewState)
	{
	case EGameState::Ready:
	{
		if (ADMHUD* DMHUD = Cast<ADMHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			DMHUD->IntroWidget->SetVisibility(ESlateVisibility::Visible);
		}
		break;
	}
	case EGameState::Playing:
	{
		if (ADMHUD* DMHUD = Cast<ADMHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
		{
			DMHUD->IntroWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	}
		
	case EGameState::Clear:
		break;
	case EGameState::Fail:
		break;
	}
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

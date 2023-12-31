// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DMHUD.h"
#include "UI/Widget/DMUserWidget.h"
#include "Game/DMGameMode.h"
#include "UI/Controller/OverlayWidgetController.h"
#include "UI/Controller/AttributeMenuWidgetController.h"
#include "UI/Controller/IntroWidgetController.h"
#include "UI/Controller/GameOverWidgetController.h"

void ADMHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ADMGameMode* DMGameMode = Cast<ADMGameMode>(GetWorld()->GetAuthGameMode()))
	{
		DMGameMode->OnChangeGameState.AddDynamic(this, &ADMHUD::SetWidgets);
	}

	SetWidgets(EGameState::Ready);
}

UOverlayWidgetController* ADMHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}


UAttributeMenuWidgetController* ADMHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}

	return AttributeMenuWidgetController;
}

UIntroWidgetController* ADMHUD::GetIntroWidgetController(const FWidgetControllerParams& WCParams)
{
	if (IntroWidgetController == nullptr)
	{
		IntroWidgetController = NewObject<UIntroWidgetController>(this, IntroWidgetControllerClass);
		IntroWidgetController->SetWidgetControllerParams(WCParams);
		IntroWidgetController->BindCallbacksToDependencies();
	}

	return IntroWidgetController;
}

UGameOverWidgetController* ADMHUD::GetGameOverWidgetController(const FWidgetControllerParams& WCParams)
{
	if (GameOverWidgetController == nullptr)
	{
		GameOverWidgetController = NewObject<UGameOverWidgetController>(this, GameOverWidgetControllerClass);
		GameOverWidgetController->SetWidgetControllerParams(WCParams);
		GameOverWidgetController->BindCallbacksToDependencies();
	}

	return GameOverWidgetController;
}

void ADMHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(OverlayWidgetClass);
	check(OverlayWidgetControllerClass);

	// OverlayWidget
	OverlayWidget = CreateWidget<UDMUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
	
	// WidgetController
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
}

void ADMHUD::InitIntro(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// IntroWidget
	IntroWidget = CreateWidget<UDMUserWidget>(GetWorld(), IntroWidgetClass);
	IntroWidget->AddToViewport();

	// WidgetController
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UIntroWidgetController* WidgetController = GetIntroWidgetController(WidgetControllerParams);
	IntroWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
}

void ADMHUD::InitGameOver(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// GameOverWidget
	GameOverWidget = CreateWidget<UDMUserWidget>(GetWorld(), GameOverWidgetClass);
	GameOverWidget->AddToViewport();

	// WidgetController
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UGameOverWidgetController* WidgetController = GetGameOverWidgetController(WidgetControllerParams);
	GameOverWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
}

void ADMHUD::InitHUD(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	InitOverlay(PC, PS, ASC, AS);
	InitIntro(PC, PS, ASC, AS);
	InitGameOver(PC, PS, ASC, AS);
}

void ADMHUD::SetWidgets(EGameState NewState)
{
	switch (NewState)
	{
	case EGameState::Ready:
	{
		IntroWidget->SetVisibility(ESlateVisibility::Visible);
		OverlayWidget->SetVisibility(ESlateVisibility::Hidden);
		GameOverWidget->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	case EGameState::Playing:
	{
		IntroWidget->SetVisibility(ESlateVisibility::Hidden);
		OverlayWidget->SetVisibility(ESlateVisibility::Visible);
		GameOverWidget->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
	case EGameState::Clear:
		IntroWidget->SetVisibility(ESlateVisibility::Hidden);
		OverlayWidget->SetVisibility(ESlateVisibility::Hidden);
		GameOverWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case EGameState::Fail:
		IntroWidget->SetVisibility(ESlateVisibility::Hidden);
		OverlayWidget->SetVisibility(ESlateVisibility::Hidden);
		GameOverWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

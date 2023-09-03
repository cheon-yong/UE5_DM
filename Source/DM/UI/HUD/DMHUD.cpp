// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DMHUD.h"
#include "UI/Widget/DMUserWidget.h"
#include "UI/Controller/OverlayWidgetController.h"
#include "UI/Controller/AttributeMenuWidgetController.h"
#include "UI/Controller/IntroWidgetController.h"

void ADMHUD::BeginPlay()
{
	Super::BeginPlay();

	
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


void ADMHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(OverlayWidgetClass);
	check(OverlayWidgetControllerClass);

	// OverlayWidget
	OverlayWidget = CreateWidget<UDMUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
	//OverlayWidget = Widget;

	// IntroWidget
	IntroWidget = CreateWidget<UDMUserWidget>(GetWorld(), IntroWidgetClass);
	IntroWidget->AddToViewport();
	

	// WidgetController
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
}
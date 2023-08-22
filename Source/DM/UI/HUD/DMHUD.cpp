// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/DMHUD.h"
//#include "UI/Widget/DMUserWidget.h"
#include "UI/WIdget/DMOverlayWidget.h"
#include "UI/Widget/DMAttributeMenuWidget.h"

void ADMHUD::BeginPlay()
{
	Super::BeginPlay();

	
}

void ADMHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// Widget
	UDMOverlayWidget* Widget = CreateWidget<UDMOverlayWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
	OverlayWidget = Widget;
	
	check(OverlayWidget);
	check(OverlayWidgetClass);

	// WidgetController Set
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	OverlayWidget->SetWidgetControllerParams(WidgetControllerParams);
	OverlayWidget->BindCallbacksToDependencies();
	OverlayWidget->BroadcastInitialValues();
}

UDMAttributeMenuWidget* ADMHUD::GetAttributeMenuWidget(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidget == nullptr)
	{
		AttributeMenuWidget = CreateWidget<UDMAttributeMenuWidget>(GetWorld(), AttributeMenuWidgetClass);
		AttributeMenuWidget->AddToViewport();
		FVector2D position(500, 50);
		AttributeMenuWidget->SetPositionInViewport(position);
		AttributeMenuWidget->SetWidgetControllerParams(WCParams);
		AttributeMenuWidget->BroadcastInitialValues();
	}

	return AttributeMenuWidget;
}

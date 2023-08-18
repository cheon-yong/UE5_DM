// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/DMUserWidget.h"
#include "AbilitySystemComponent.h"

void UDMUserWidget::SetParentWidget(UDMUserWidget* ParentWidget)
{
	Parent = ParentWidget;
	ParentSet();
}

void UDMUserWidget::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;

	ParentSet();
}

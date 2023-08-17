// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DMUserWidget.h"
#include "AbilitySystemComponent.h"

void UDMUserWidget::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

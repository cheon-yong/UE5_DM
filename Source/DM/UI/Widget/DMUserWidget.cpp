// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/DMUserWidget.h"
#include "AbilitySystemComponent.h"

void UDMUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
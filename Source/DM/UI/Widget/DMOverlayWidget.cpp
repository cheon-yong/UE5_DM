// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/DMOverlayWidget.h"
#include "AbilitySystem/DMAttributeSet.h"

void UDMOverlayWidget::BroadcastInitialValues()
{
	const UDMAttributeSet* DMAttributeSet = CastChecked<UDMAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(DMAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DMAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(DMAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(DMAttributeSet->GetMaxStamina());
}

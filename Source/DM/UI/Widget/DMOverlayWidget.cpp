// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/DMOverlayWidget.h"
#include "AbilitySystem/DMAttributeSet.h"
#include "AbilitySystem/DMAbilitySystemComponent.h"

void UDMOverlayWidget::BroadcastInitialValues()
{
	const UDMAttributeSet* DMAttributeSet = CastChecked<UDMAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(DMAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DMAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(DMAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(DMAttributeSet->GetMaxStamina());
}

void UDMOverlayWidget::BindCallbacksToDependencies()
{
	const UDMAttributeSet* DMAttributeSet = CastChecked<UDMAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DMAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DMAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DMAttributeSet->GetStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DMAttributeSet->GetMaxStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStaminaChanged.Broadcast(Data.NewValue);
		}
	);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DMAttributeSet.h"
#include "Net/UnrealNetwork.h"

UDMAttributeSet::UDMAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitStamina(50.f);
	InitMaxStamina(100.f);
}

void UDMAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDMAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDMAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDMAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDMAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UDMAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDMAttributeSet, Health, OldValue);
}

void UDMAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDMAttributeSet, MaxHealth, OldValue);
}

void UDMAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDMAttributeSet, Stamina, OldValue);
}

void UDMAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDMAttributeSet, MaxStamina, OldValue);
}

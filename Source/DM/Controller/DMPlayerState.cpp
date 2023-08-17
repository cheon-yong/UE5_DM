// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DMPlayerState.h"
#include <AbilitySystem/DMAbilitySystemComponent.h>
#include <AbilitySystem/DMAttributeSet.h>

ADMPlayerState::ADMPlayerState()
{
	// AbilitySystem
	AbilitySystemComponent = CreateDefaultSubobject<UDMAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDMAttributeSet>(TEXT("AttributeSet"));
}

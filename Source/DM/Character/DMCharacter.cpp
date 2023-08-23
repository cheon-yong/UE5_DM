// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/DMCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <AbilitySystem/DMAttributeSet.h>
#include <AbilitySystem/DMAbilitySystemComponent.h>

//////////////////////////////////////////////////////////////////////////
// ADMCharacter

ADMCharacter::ADMCharacter()
{
	

}

void ADMCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();


}

void ADMCharacter::InitializeDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondAttributes, 1.f); 
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}


void ADMCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

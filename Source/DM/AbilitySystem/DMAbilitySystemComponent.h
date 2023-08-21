// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DMAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);

/**
 * 
 */
UCLASS()
class DM_API UDMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();

	void EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& ES, FActiveGameplayEffectHandle AGEH);

public:
	FEffectAssetTags EffectAssetTags;
};

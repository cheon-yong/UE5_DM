// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DMGameplayAbility.h"
#include "DMProjectileSpell.generated.h"

/**
 * 
 */
class ADMProjectile;

UCLASS()
class DM_API UDMProjectileSpell : public UDMGameplayAbility
{
	GENERATED_BODY()
	
protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ADMProjectile> ProjectileClass;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DMProjectileSpell.h"
#include "DMMousePointSpell.generated.h"

/**
 * 
 */
UCLASS()
class DM_API UDMMousePointSpell : public UDMProjectileSpell
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable)
	AActor* CreateCursor();

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PointCursorClass;
};

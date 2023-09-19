// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DMGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DM_API UDMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ApplyEffect(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	AActor* CheckRange();

	UFUNCTION(BlueprintImplementableEvent)
	void ContinueAbility();
	void EndAbilityByController();

public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditAnywhere)
	float AbilityRange = 20.f;

	UPROPERTY(EditAnywhere)
	float AbilityRadius = 20.f;
};

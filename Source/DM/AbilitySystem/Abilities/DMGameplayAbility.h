// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DMGameplayAbility.generated.h"

/**
 * 
 */
class UAnimMontage;

UCLASS()
class DM_API UDMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ApplyEffect(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	AActor* CheckRange();

	UFUNCTION(BlueprintCallable)
	void Casting();

	UFUNCTION(BlueprintImplementableEvent)
	void ContinueAbility();

	void EndAbilityByController();

public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> CastingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CastingTime = 0.f;

	UPROPERTY(EditAnywhere)
	float AbilityRange = 20.f;

	UPROPERTY(EditAnywhere)
	float AbilityRadius = 20.f;
};

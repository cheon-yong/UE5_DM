// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DMAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/DMGameplayAbility.h"

void UDMAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.RemoveAll(this);
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDMAbilitySystemComponent::ClientEffectApplied);
}

void UDMAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& ES, FActiveGameplayEffectHandle AGEH)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("Effect Applied"));

	FGameplayTagContainer TagContainer;
	ES.GetAllAssetTags(OUT TagContainer);

	/*for (const FGameplayTag& Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GE TAG : %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Msg);
	}*/

	EffectAssetTags.Broadcast(TagContainer);
}

void UDMAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		//GiveAbility(AbilitySpec);
		//GiveAbilityAndActivateOnce(AbilitySpec);

		if (const UDMGameplayAbility* DMAbility = Cast<UDMGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(DMAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UDMAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
		return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);

			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UDMAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
		return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}


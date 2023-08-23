// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/OverlayWidgetController.h"
#include "AbilitySystem/DMAttributeSet.h"
#include "AbilitySystem/DMAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UDMAttributeSet* DMAttributeSet = CastChecked<UDMAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(DMAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(DMAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(DMAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(DMAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DMAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DMAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UDMAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));


				// "Message.HealthPotion".MathcesTag("Message") => true;
				// "Message".MathcesTag("Message.HealthPotion") => false;
				// Contain 같은 느낌?

				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					// TODO

					MessageWidgetRowDelegate.Broadcast(*Row);
				}


				/*const FString Msg = FString::Printf(TEXT("GE TAG : %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Msg);*/
			}
		}
	);
}
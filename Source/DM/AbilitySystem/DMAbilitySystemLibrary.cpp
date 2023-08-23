// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DMAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/DMPlayerState.h"
#include "UI/HUD/DMHUD.h"
#include "UI/Controller/DMWidgetController.h"
#include "UI/Controller/AttributeMenuWidgetController.h"


UOverlayWidgetController* UDMAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADMHUD* DMHUD = Cast<ADMHUD>(PC->GetHUD()))
		{
			ADMPlayerState* PS = PC->GetPlayerState<ADMPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DMHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UDMAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ADMHUD* DMHUD = Cast<ADMHUD>(PC->GetHUD()))
		{
			ADMPlayerState* PS = PC->GetPlayerState<ADMPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DMHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

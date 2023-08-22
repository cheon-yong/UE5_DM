// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/DMAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/DMPlayerState.h"
#include "UI/HUD/DMHUD.h"
#include "UI/Widget/DMUserWidget.h"

FWidgetControllerParams UDMAbilitySystemLibrary::GetFWidgetControllerParams(const UObject* WorldObjectContext)
{

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldObjectContext, 0))
	{
		if (ADMHUD* DMHUD = Cast<ADMHUD>(PC->GetHUD()))
		{
			auto* PS = PC->GetPlayerState<ADMPlayerState>();
			auto* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return WidgetControllerParams;
		}
	}

	return FWidgetControllerParams();
}

UDMAttributeMenuWidget* UDMAbilitySystemLibrary::GetDMAttributeMenuWidget(const UObject* WorldObjectContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldObjectContext, 0))
	{
		if (ADMHUD* DMHUD = Cast<ADMHUD>(PC->GetHUD()))
		{
			auto* PS = PC->GetPlayerState<ADMPlayerState>();
			auto* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return DMHUD->GetAttributeMenuWidget(WidgetControllerParams);
		}
	}

	return nullptr;
}



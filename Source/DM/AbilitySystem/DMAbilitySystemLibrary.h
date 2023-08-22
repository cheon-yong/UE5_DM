// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DMAbilitySystemLibrary.generated.h"

/**
 * 
 */

UCLASS()
class DM_API UDMAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category="DMAbilitySystemLibrary|UUserWidget")
	static struct FWidgetControllerParams GetFWidgetControllerParams(const UObject* WorldObjectContext);

	UFUNCTION(BlueprintPure, Category = "DMAbilitySystemLibrary|UUserWidget")
	static class UDMAttributeMenuWidget* GetDMAttributeMenuWidget(const UObject* WorldObjectContext);
};

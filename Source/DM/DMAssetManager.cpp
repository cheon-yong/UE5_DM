// Fill out your copyright notice in the Description page of Project Settings.


#include "DMAssetManager.h"
#include "DMGameplayTags.h"
#include "AbilitySystemGlobals.h"

UDMAssetManager& UDMAssetManager::Get()
{
	UDMAssetManager* DMAssetManager = Cast<UDMAssetManager>(GEngine->AssetManager);
	return *DMAssetManager;
}

void UDMAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FDMGameplayTags::InitializeNativeGameplayTags();

	UAbilitySystemGlobals::Get().InitGlobalData();
}

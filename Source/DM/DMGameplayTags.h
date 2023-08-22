// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FDMGameplayTags
{
public:
	static const FDMGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

public:
	FGameplayTag Attribute_Primary_Attack;
	FGameplayTag Attribute_Primary_Defense;
	FGameplayTag Attribute_Primary_Critical;
	FGameplayTag Attribute_Primary_MoveSpeed;

	FGameplayTag Attribute_Second_AttackSpeed;
	FGameplayTag Attribute_Second_CriticalDamage;
	FGameplayTag Attribute_Second_CooltimeReduction;
	FGameplayTag Attribute_Second_MaxHealth;
	FGameplayTag Attribute_Second_MaxMana;

private:
	static FDMGameplayTags GameplayTags;
};
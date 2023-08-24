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

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

private:
	static FDMGameplayTags GameplayTags;
};
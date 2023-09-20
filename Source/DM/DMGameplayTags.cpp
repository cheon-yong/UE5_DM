// Fill out your copyright notice in the Description page of Project Settings.


#include "DMGameplayTags.h"
#include "GameplayTagsManager.h"

FDMGameplayTags FDMGameplayTags::GameplayTags;

void FDMGameplayTags::InitializeNativeGameplayTags()
{
	// Primary
	GameplayTags.Attribute_Primary_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Attack"),
		FString("Increase Attack Damage")
	);
	GameplayTags.Attribute_Primary_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Defense"),
		FString("Decrease Damage taken")
	);
	GameplayTags.Attribute_Primary_Critical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Critical"),
		FString("Sometimes give stronger damage")
	);
	GameplayTags.Attribute_Primary_MoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MoveSpeed"),
		FString("Increase Move Speed")
	);

	// Second
	GameplayTags.Attribute_Second_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Second.AttackSpeed"),
		FString("Increase Attack Speed")
	);
	GameplayTags.Attribute_Second_CriticalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Second.CriticalDamage"),
		FString("Increase Critical Damage")
	);
	GameplayTags.Attribute_Second_CooltimeReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Second.CooltimeReduction"),
		FString("Decrease Cool time")
	);
	GameplayTags.Attribute_Second_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Second.MaxHealth"),
		FString("Increase Max Health")
	);
	GameplayTags.Attribute_Second_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Second.MaxMana"),
		FString("Increase Max Mana")
	);

	// Input
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
	);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Left Mouse Button")
	);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
	);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
	);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
	);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
	);

	// Event
	GameplayTags.Event_Montage_Projectile = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Montage.Projectile"),
		FString("Create Projectile")
	);

	GameplayTags.Event_Montage_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Montage.Attack"),
		FString("Attack")
	);

	// Monster
	GameplayTags.Monster_Attack_Default = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Monster.Attack.Default"),
		FString("Monster.Attack.Default")
	);
}
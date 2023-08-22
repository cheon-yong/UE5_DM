// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DMAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)			\
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)	\
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)				\
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)				\
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class DM_API UDMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UDMAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Attack(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Critical(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue) const;
	
public:
	// Vital Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, MaxMana);

	// Primary Attributes
	// 공격력, 방어력, 크리티컬, 이동속도, 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Attack, Category = "Primary Attributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, Attack);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Primary Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, Defense);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Critical, Category = "Primary Attributes")
	FGameplayAttributeData Critical;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, Critical);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, Category = "Primary Attributes")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, MoveSpeed);
 
	// Secondary Attibutes
	// 공격속도, 쿨타임감소, 크리티컬 공증
};

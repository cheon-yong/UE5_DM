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
	void OnRep_Stamina(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const;

	
public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UDMAttributeSet, MaxStamina);
};

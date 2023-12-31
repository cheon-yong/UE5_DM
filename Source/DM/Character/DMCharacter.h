// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"
#include "DMCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;



UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Living,
	Casting,
	Dead,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCharacterState, const ECharacterState, CharacterState);

UCLASS(config=Game)
class ADMCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ADMCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void InitAbilityActorInfo() {}

	void InitializeDefaultAttributes();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level);

	virtual int32 GetPlayerLevel() { return 0; };

	ECharacterState GetCharacterState() { return CharacterState; }

	UFUNCTION(BlueprintCallable)
	virtual void SetCharacterState(ECharacterState NewState);

	UPROPERTY(BlueprintAssignable)
	FOnChangeCharacterState OnChangeCharacterState;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondAttributes;

	UPROPERTY(BlueprintReadOnly)
	ECharacterState CharacterState;

public:
	void AddCharacterAbilities();

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	virtual FVector GetCombatSocketLocation() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName BodySocketName;
};


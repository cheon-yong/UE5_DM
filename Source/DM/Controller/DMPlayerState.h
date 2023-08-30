// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "DMPlayerState.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;
class UAttributeSet;



UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Living,
	Dead,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeCharacterState, const ECharacterState);

UCLASS()
class DM_API ADMPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ADMPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int32 GetPlayerLevel() { return Level; }

	ECharacterState GetCharacterState() { return CharacterState; }

	void SetCharacterState(ECharacterState NewState);

	UFUNCTION()
	void OnReq_Level(int32 OldLevel);

	FOnChangeCharacterState OnChangeCharacterState;
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnReq_Level)
	int32 Level = 1;

	UPROPERTY()
	ECharacterState CharacterState;
};
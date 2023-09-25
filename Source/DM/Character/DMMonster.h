// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DMCharacter.h"
#include "../Interface/EnemyInterface.h"
#include "UI/Controller/OverlayWidgetController.h"
#include "DMMonster.generated.h"


/**
 * 
 */
class UWidgetComponent;

UCLASS()
class DM_API ADMMonster : public ADMCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	ADMMonster();

	virtual void BeginPlay() override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual void InitAbilityActorInfo() override;

	virtual void SetCharacterState(ECharacterState NewState) override;

	virtual int32 GetPlayerLevel() override { return Level; }

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character")
	int32 Level = 1;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
};

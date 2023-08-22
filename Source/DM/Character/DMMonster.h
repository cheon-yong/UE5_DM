// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DMCharacter.h"
#include "../Interface/EnemyInterface.h"
#include "DMMonster.generated.h"

/**
 * 
 */
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

	virtual int32 GetPlayerLevel() override { return Level; }

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character")
	int32 Level = 1;
};

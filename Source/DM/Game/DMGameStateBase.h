// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DMGameStateBase.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Ready,
	Playing,
	Fail,
	Clear
};


/**
 * 
 */
UCLASS()
class DM_API ADMGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADMGameStateBase();

public:
	int32 GetTotalGameScore() const;
	void AddGameScore();

	void SetGameState(EGameState NewState);
	bool IsGameCleared() const;

private:
	UPROPERTY()
	EGameState GameState;

	UPROPERTY(Transient)
	int32 TotalGameScore;
};

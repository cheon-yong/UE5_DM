// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Game/DMGameStateBase.h"
#include "DMGameMode.generated.h"

class ADMPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateScore, int32, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeGameState, EGameState, NewState);

UCLASS(minimalapi)
class ADMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADMGameMode();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
	void AddScore(class AActor* ScoredPlayer);
	void SetGameState(EGameState NewState);

	UFUNCTION(BlueprintCallable)
	int32 GetScore() const;	

	UPROPERTY(BlueprintAssignable)
	FOnUpdateScore OnUpdateScore;

	UPROPERTY(BlueprintAssignable)
	FOnChangeGameState OnChangeGameState;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ScoreToClear = 0;
};




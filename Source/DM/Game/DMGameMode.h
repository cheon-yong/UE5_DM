// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Game/DMGameStateBase.h"
#include "DMGameMode.generated.h"

class ADMPlayerController;
class ADMMonster;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateScore, int32, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateMonster, int32, MonsterCount);
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

	UPROPERTY(BlueprintAssignable)
	FOnUpdateMonster OnUpdateMonster;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ScoreToClear = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ADMMonster> DMMonsterClass;

	FTimerHandle SpawnActorHandle;

	TMap<FString, TObjectPtr<ADMMonster>> Monsters;

	void SpawnActor();

};




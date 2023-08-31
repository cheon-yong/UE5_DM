// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DMGameMode.generated.h"

class ADMPlayerController;
class ADMGameStateBase;

UCLASS(minimalapi)
class ADMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADMGameMode();

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void AddScore(class ADMPlayerController* ScoredPlayer);
	int32 GetScore() const;	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ScoreToClear = 0;
};




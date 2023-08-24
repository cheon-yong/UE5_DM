// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DMCharacter.h"
#include "DMPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DM_API ADMPlayer : public ADMCharacter
{
	GENERATED_BODY()
	
public:
	ADMPlayer();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual int32 GetPlayerLevel() override;

private:
	virtual void InitAbilityActorInfo() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

};

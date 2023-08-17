// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DMHUD.generated.h"

class UDMUserWidget;

/**
 * 
 */

UCLASS()
class DM_API ADMHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	TObjectPtr<UDMUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDMUserWidget> OverlayWidgetClass;
};

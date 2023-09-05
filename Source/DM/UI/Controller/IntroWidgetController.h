// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/DMWidgetController.h"
#include "Game/DMGameStateBase.h"
#include "IntroWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DM_API UIntroWidgetController : public UDMWidgetController
{
	GENERATED_BODY()
	
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable)
	void OnClickGameStartButton();

	UFUNCTION(BlueprintCallable)
	void OnClickGameExitButton();
};

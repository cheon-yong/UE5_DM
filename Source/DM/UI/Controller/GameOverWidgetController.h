// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/DMWidgetController.h"
#include "GameOverWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class DM_API UGameOverWidgetController : public UDMWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable)
	void OnClickGameRestartButton();

	UFUNCTION(BlueprintCallable)
	void OnClickTitleButton();

	UFUNCTION(BlueprintCallable)
	void OnClickGameExitButton();
};

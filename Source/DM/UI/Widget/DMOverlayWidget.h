// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/DMUserWidget.h"
#include "DMOverlayWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

/**
 * 
 */
UCLASS()
class DM_API UDMOverlayWidget : public UDMUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attribute")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attribute")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attribute")
	FOnAttributeChangedSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attribute")
	FOnAttributeChangedSignature OnMaxStaminaChanged;
};

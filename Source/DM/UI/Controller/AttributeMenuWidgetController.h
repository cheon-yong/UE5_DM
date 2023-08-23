// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/DMWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FDMAttributeInfo&, Info);
/**
 * 
 */
class UAttributeInfo;

UCLASS(BlueprintType, Blueprintable)
class DM_API UAttributeMenuWidgetController : public UDMWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	void BroadcastAttributeInfo(const struct FGameplayTag& AttributeTag, const struct FGameplayAttribute& Attribute) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;
};

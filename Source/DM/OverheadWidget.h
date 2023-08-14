// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

/**
 * 
 */
UCLASS()
class DM_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayText(FString Text);
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerNetRole(APawn* Pawn);

public:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* DisplayText;
	
};

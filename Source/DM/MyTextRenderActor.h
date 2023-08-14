// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "MyTextRenderActor.generated.h"

/**
 * 
 */
UCLASS()
class DM_API AMyTextRenderActor : public ATextRenderActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	FString GetNetMode();
};

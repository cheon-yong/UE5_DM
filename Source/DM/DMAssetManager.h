// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DMAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DM_API UDMAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UDMAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};

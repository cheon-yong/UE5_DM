// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DMAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;
/**
 * 
 */
UCLASS()
class DM_API ADMAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ADMAIController();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	UFUNCTION(BlueprintCallable)
	void RunAI();

	UFUNCTION(BlueprintCallable)
	void StopAI();


protected:
	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	UBlackboardData* BlackBoardAsset;
};

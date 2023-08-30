// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class DM_API UBTDecorator_CanAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_CanAttack();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackRange = 20.f;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AI/DMAIController.h"
#include "Character/DMCharacter.h"
#include "Character/DMMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystem/DMAbilitySystemComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DMMonster = Cast<ADMMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DMMonster)
		return EBTNodeResult::Failed;

	auto Target = Cast<ADMCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADMAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	if (UDMAbilitySystemComponent* DMASC = Cast<UDMAbilitySystemComponent>(DMMonster->GetAbilitySystemComponent()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("Success DMASC"));
		DMASC->AbilityInputTagHeld(AttackTag);
		EBTNodeResult::Succeeded;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("Fail DMASC"));
	}

	return EBTNodeResult::Failed;
}

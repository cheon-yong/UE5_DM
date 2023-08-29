// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToTarget.h"
#include "AI/DMAIController.h"
#include "Character/DMCharacter.h"
#include "Character/DMMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DMMonster = Cast<ADMMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DMMonster)
		return EBTNodeResult::Failed;

	auto Target = Cast<ADMCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADMAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - DMMonster->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	DMMonster->SetActorRotation(FMath::RInterpTo(DMMonster->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), TurnSpeed));

	return EBTNodeResult::Succeeded;
}

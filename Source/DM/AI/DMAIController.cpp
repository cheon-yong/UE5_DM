// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DMAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ADMAIController::HomePosKey(TEXT("HomePos"));
const FName ADMAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ADMAIController::TargetKey(TEXT("Target"));

ADMAIController::ADMAIController()
{
}

void ADMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void ADMAIController::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BlackBoardAsset, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
	Blackboard = BlackboardComp;
}

void ADMAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

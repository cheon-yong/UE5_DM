// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "DMAIController.h"
#include "Character/DMPlayer.h"

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = TEXT("DetectPlayer");
	Interval = TickInterval;
}

void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory,DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	

	if (nullptr == World)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADMAIController::TargetKey, nullptr);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			ADMPlayer* DMPlayer = Cast<ADMPlayer>(OverlapResult.GetActor());

			if (DMPlayer && DMPlayer->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ADMAIController::TargetKey, DMPlayer);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, DMPlayer->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), DMPlayer->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
}

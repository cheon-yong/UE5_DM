// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DMMousePointSpell.h"
#include "Controller/DMPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UDMMousePointSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


}

AActor* UDMMousePointSpell::CreateCursor()
{
	if (ADMPlayerController* DMPC = Cast<ADMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (DMPC->GetActivatingAbility() != nullptr)
			return nullptr;


		FVector Location = FVector::Zero();
		FActorSpawnParameters ActorSpawnParameters;

		AActor* Cursor = GetWorld()->SpawnActor<AActor>(
			PointCursorClass,
			Location, 
			FRotator::ZeroRotator, 
			ActorSpawnParameters
		);

		DMPC->SetActivatingAbility(this);

		return Cursor;
	}

	return nullptr;
}

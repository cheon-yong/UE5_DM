// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DMProjectileSpell.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/CombatInterface.h"
#include "Actor/DMProjectile.h"

void UDMProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	
}

void UDMProjectileSpell::SpawnProjectile()
{
	//UKismetSystemLibrary::PrintString(this, FString("ActivateAbility(C++)"), true, true, FLinearColor::Yellow, 3);
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
		return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		ADMProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADMProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		Projectile->FinishSpawning(SpawnTransform);
	}
}

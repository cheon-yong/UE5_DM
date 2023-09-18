// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DMGameplayAbility.h"

void UDMGameplayAbility::ApplyEffect(AActor* OtherActor)
{

}

AActor* UDMGameplayAbility::CheckRange()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, GetAvatarActorFromActorInfo());
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetAvatarActorFromActorInfo()->GetActorLocation(),
		GetAvatarActorFromActorInfo()->GetActorLocation() 
		+ GetAvatarActorFromActorInfo()->GetActorForwardVector() * AbilityRange,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(AbilityRadius),
		Params);

	// Debug
	FVector TraceVec = GetAvatarActorFromActorInfo()->GetActorForwardVector() * AbilityRange;
	FVector Center = GetAvatarActorFromActorInfo()->GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AbilityRange * 0.5f + AbilityRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AbilityRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);

	return HitResult.GetActor();
}

void UDMGameplayAbility::EndAbilityByController()
{
	EndAbility(GetCurrentAbilitySpecHandle(),
		GetCurrentActorInfo(),
		GetCurrentActivationInfo(),
		true,
		false);
}
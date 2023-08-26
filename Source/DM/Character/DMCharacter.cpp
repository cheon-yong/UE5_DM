// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/DMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <AbilitySystem/DMAttributeSet.h>
#include <AbilitySystem/DMAbilitySystemComponent.h>
#include "Components/CapsuleComponent.h"
#include "DM/DM.h"

//////////////////////////////////////////////////////////////////////////
// ADMCharacter

ADMCharacter::ADMCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

}

void ADMCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();


}

void ADMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADMCharacter::InitializeDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondAttributes, 1.f); 
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}


void ADMCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ADMCharacter::AddCharacterAbilities()
{
	UDMAbilitySystemComponent* DMASC = CastChecked<UDMAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority())
		return;

	DMASC->AddCharacterAbilities(StartupAbilities);
}

FVector ADMCharacter::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DMPlayerState.h"
#include "AbilitySystem/DMAbilitySystemComponent.h"
#include "AbilitySystem/DMAttributeSet.h"
#include "Net/UnrealNetwork.h"

ADMPlayerState::ADMPlayerState()
{
	CharacterState = ECharacterState::Living;

	// AbilitySystem
	AbilitySystemComponent = CreateDefaultSubobject<UDMAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UDMAttributeSet>("AttributeSet");
	if (UDMAttributeSet* DMAttributeSet = Cast<UDMAttributeSet>(AttributeSet))
	{
		DMAttributeSet->OnHealthIsZero.AddLambda(
			[this]()
			{
				SetCharacterState(ECharacterState::Dead);
			}
		);
	}
}

void ADMPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ADMPlayerState, Level, COND_None, REPNOTIFY_Always);
}

void ADMPlayerState::SetCharacterState(ECharacterState NewState)
{
	CharacterState = NewState;
	OnChangeCharacterState.Broadcast(CharacterState);
}

void ADMPlayerState::OnReq_Level(int32 OldLevel)
{

}

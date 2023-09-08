// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DMMonster.h"
#include "AbilitySystem/DMAbilitySystemComponent.h"
#include "AbilitySystem/DMAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/DMUserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Game/DMGameMode.h"

ADMMonster::ADMMonster()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDMAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UDMAttributeSet>(TEXT("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

}

void ADMMonster::BeginPlay()
{
	Super::BeginPlay();

	UnHighlightActor();

	InitAbilityActorInfo();

	AddCharacterAbilities();

	if (UDMUserWidget* DMUserWidget = Cast<UDMUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		DMUserWidget->SetWidgetController(this);
	}

	if (UDMAttributeSet* DMAS = Cast<UDMAttributeSet>(AttributeSet))
	{
		// 임시
		GetCharacterMovement()->MaxWalkSpeed = 200;

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DMAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(DMAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		DMAS->OnHealthIsZero.AddLambda(
			[this](FEffectProperties* Props)
			{
				SetCharacterState(ECharacterState::Dead);
				GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				if (ADMGameMode* DMGameMode = Cast<ADMGameMode>(GetWorld()->GetAuthGameMode()))
				{
					int32 NewScore = DMGameMode->GetScore() + 1;
					DMGameMode->SetScore(Props->SourceAvatarActor, NewScore);
				}
			}
		);

		OnHealthChanged.Broadcast(DMAS->GetHealth());
		OnMaxHealthChanged.Broadcast(DMAS->GetMaxHealth());
	}
}

void ADMMonster::HighlightActor()
{
	bHighlighted = true;

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
	//Weapon->SetRenderCustomDepth(true);
}

void ADMMonster::UnHighlightActor()
{
	bHighlighted = false;

	GetMesh()->SetRenderCustomDepth(false);
	//Weapon->SetRenderCustomDepth(false);
}

void ADMMonster::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UDMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void ADMMonster::SetCharacterState(ECharacterState NewState)
{
	Super::SetCharacterState(NewState);
}

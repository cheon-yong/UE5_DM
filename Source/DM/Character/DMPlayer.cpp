// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DMPlayer.h"
#include "Gameframework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Controller/DMPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Controller/DMPlayerController.h"
#include "Controller/DMPlayerState.h"
#include "UI/HUD/DMHUD.h"
#include "AbilitySystem/DMAbilitySystemComponent.h"
#include "AbilitySystem/DMAttributeSet.h"
#include "Game/DMGameMode.h"



ADMPlayer::ADMPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 750.f;
	CameraBoom->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Follow Camera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
}

void ADMPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server 시점
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ADMPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client 시점
	InitAbilityActorInfo();
}

int32 ADMPlayer::GetPlayerLevel()
{
	ADMPlayerState* PS = GetPlayerState<ADMPlayerState>();
	check(PS);
	return PS->GetPlayerLevel();
}

void ADMPlayer::InitAbilityActorInfo()
{
	ADMPlayerState* DMPlayerState = GetPlayerState<ADMPlayerState>();
	check(DMPlayerState);
	DMPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(DMPlayerState, this);

	AbilitySystemComponent = DMPlayerState->GetAbilitySystemComponent();
	Cast<UDMAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = DMPlayerState->GetAttributeSet();

	if (UDMAttributeSet* DMAS = Cast<UDMAttributeSet>(AttributeSet))
	{
		DMAS->OnHealthIsZero.AddLambda(
			[this](TObjectPtr<AActor> Actor)
			{
				SetCharacterState(ECharacterState::Dead);
				Cast<ADMGameMode>(GetWorld()->GetAuthGameMode())->SetGameState(EGameState::Fail);
			}
		);
	}

	if (ADMPlayerController* DMPlayerController = Cast<ADMPlayerController>(GetController()))
	{
		if (ADMHUD* DMHUD = Cast<ADMHUD>(DMPlayerController->GetHUD()))
		{
			DMHUD->InitOverlay(DMPlayerController, DMPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}

void ADMPlayer::SetCharacterState(ECharacterState NewState)
{
	Super::SetCharacterState(NewState);

	ADMPlayerController* DMController = Cast<ADMPlayerController>(GetController());
	switch (CharacterState)
	{
	case ECharacterState::Living:
		DMController->EnableInput(DMController);
		break;
	case ECharacterState::Dead:
		DMController->DisableInput(DMController);
		break;
	default:
		break;
	}
}

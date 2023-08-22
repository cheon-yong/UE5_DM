// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DMPlayer.h"
#include "Actor/DMProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Controller/DMPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Controller/DMPlayerController.h"
#include "Controller/DMPlayerState.h"
#include "UI/HUD/DMHUD.h"
#include "AbilitySystem/DMAbilitySystemComponent.h"

ADMPlayer::ADMPlayer()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void ADMPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server 시점
	InitAbilityActorInfo();
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

	if (ADMPlayerController* DMPlayerController = Cast<ADMPlayerController>(GetController()))
	{
		if (ADMHUD* DMHUD = Cast<ADMHUD>(DMPlayerController->GetHUD()))
		{
			DMHUD->InitOverlay(DMPlayerController, DMPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}

void ADMPlayer::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ADMPlayer::GetHasRifle()
{
	return bHasRifle;
}

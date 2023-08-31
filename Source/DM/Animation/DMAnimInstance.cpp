// Fill out your copyright notice in the Description page of Project Settings.



#include "Animation/DMAnimInstance.h"
#include "Controller/DMPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"

void UDMAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
		
		
	}
}

void UDMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (bIsDead)
	{
		return;
	}

	if (ADMCharacter* DMCharacter = Cast<ADMCharacter>(Character))
	{
		bIsDead = DMCharacter->GetCharacterState() == ECharacterState::Dead ? true : false;
	}


	if (MovementComponent)
	{
		Velocity = MovementComponent->Velocity;
		
		GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
		
		FRotator MoveRotator = Character->GetActorRotation();
		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, MoveRotator);
		
		FVector Acceleration = MovementComponent->GetCurrentAcceleration();
		if (Acceleration != FVector::ZeroVector && GroundSpeed > 3.0f)
		{
			bShouldMove = true;
		}
		else
		{
			bShouldMove = false;
		}

		bIsCrouching = Character->bIsCrouched;
		bIsFalling = MovementComponent->IsFalling();
	}
}

void UDMAnimInstance::SetCharacterState(ECharacterState CharacterState)
{
	UE_LOG(LogTemp, Warning, TEXT("SetCharacterState in AnimInstance"));
	switch (CharacterState)
	{
	case ECharacterState::Living:
		bIsDead = false;
		break;
	case ECharacterState::Dead:
		bIsDead = true;
		break;
	}
}

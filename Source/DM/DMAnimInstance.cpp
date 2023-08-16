// Fill out your copyright notice in the Description page of Project Settings.



#include "DMAnimInstance.h"
#include "DMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"

void UDMAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
		MovementComponent = Character->GetCharacterMovement();
}

void UDMAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent)
	{
		Velocity = MovementComponent->Velocity;
		
		GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
		
		FRotator MoveRotator = Character->GetActorRotation();
		Direction = CalculateDirection(Velocity, MoveRotator);
		
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

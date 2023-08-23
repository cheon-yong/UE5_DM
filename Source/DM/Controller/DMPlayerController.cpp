// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DMPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

void ADMPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	GetCharacter()->GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void ADMPlayerController::SetupInputComponent()
{
	// Call the base class  
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//Jumping
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ADMPlayerController::Jump);
	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADMPlayerController::StopJumping);

	//Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADMPlayerController::Move);

	//Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADMPlayerController::Look);

	//Crouching
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ADMPlayerController::Crouch);
}

void ADMPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	// add movement 
	auto ControlledCharacter = GetCharacter();
	ControlledCharacter->AddMovementInput(ControlledCharacter->GetActorForwardVector(), MovementVector.Y);
	ControlledCharacter->AddMovementInput(ControlledCharacter->GetActorRightVector(), MovementVector.X);
}

void ADMPlayerController::Jump()
{
	auto ControlledCharacter = GetCharacter();
	ControlledCharacter->Jump();
	ControlledCharacter->UnCrouch();
}

void ADMPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	auto ControlledCharacter = GetCharacter();
	// add yaw and pitch input to controller
	ControlledCharacter->AddControllerYawInput(LookAxisVector.X);
	ControlledCharacter->AddControllerPitchInput(LookAxisVector.Y);
}

void ADMPlayerController::Crouch()
{
	auto ControlledCharacter = GetCharacter();
	ControlledCharacter->bIsCrouched ? ControlledCharacter->UnCrouch() : ControlledCharacter->Crouch();
}

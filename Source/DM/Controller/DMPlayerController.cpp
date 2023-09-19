// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DMPlayerController.h"
#include "Controller/DMPlayerState.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "../Interface/EnemyInterface.h"
#include "Input/DMInputComponent.h"
#include "Character/DMPlayer.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Animation/DMAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/DMAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "DMGameplayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/Abilities/DMGameplayAbility.h"

ADMPlayerController::ADMPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	
}

void ADMPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	check(DMContext)

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DMContext, 0);
	}

	if (ADMGameMode* DMGameMode = Cast<ADMGameMode>(GetWorld()->GetAuthGameMode()))
	{
		DMGameMode->OnChangeGameState.AddDynamic(this, &ADMPlayerController::SetControllerInputMode);
	}

	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	SetInputMode(UIInputMode);
}

void ADMPlayerController::SetupInputComponent()
{
	// Call the base class  
	Super::SetupInputComponent();

	//UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	UDMInputComponent* DMInputComponent = CastChecked<UDMInputComponent>(InputComponent);

	//Moving
	DMInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADMPlayerController::Move);
	DMInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &ADMPlayerController::ShiftPressed);
	DMInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ADMPlayerController::ShiftReleased);
	
	DMInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ADMPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TickCursorTrace();
	AutoRun();
}


void ADMPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ADMPlayerController::TickCursorTrace()
{
	FHitResult CursorHit;

	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit) == false)
		return;

	IEnemyInterface* LocalTargetActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LocalTargetActor == nullptr)
	{
		// 원래 있었는데, 없어짐
		if (TargetActor)
		{
			TargetActor->UnHighlightActor();
		}
	}
	else
	{
		if (TargetActor)
		{
			// 원래 있었는데 다른 애였음
			if (TargetActor != LocalTargetActor)
			{
				TargetActor->UnHighlightActor();
				LocalTargetActor->HighlightActor();
			}

			// 동일한 애면 무시
		}
		else
		{
			// 원래 없었고 새로 주시
			LocalTargetActor->HighlightActor();
		}
	}

	// 저장
	TargetActor = LocalTargetActor;
}

void ADMPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
	if (InputTag.MatchesTagExact(FDMGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = (TargetActor != nullptr) ? true : false;
		bAutoRunning = false;
	}
}

void ADMPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());
	if (InputTag.MatchesTagExact(FDMGameplayTags::Get().InputTag_RMB))
	{
		if (ActivatingAbility != nullptr)
		{
			ActivatingAbility->EndAbilityByController();
			ActivatingAbility = nullptr;
			bAutoRunning = false;
			return;
		}

		APawn* ControllerPawn = GetPawn();

		if (FollowTime <= ShortPressThreshold && ControllerPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControllerPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 1.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
		UE_LOG(LogTemp, Error, TEXT("Released Moving"));
	}
	else if (InputTag.MatchesTagExact(FDMGameplayTags::Get().InputTag_LMB))
	{
		if (ActivatingAbility != nullptr)
		{
			ActivatingAbility->ContinueAbility();
			ActivatingAbility = nullptr;
			return;
		}
	}
	else 
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
}

void ADMPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, *InputTag.ToString());

	// 우클릭 처리
	if (InputTag.MatchesTagExact(FDMGameplayTags::Get().InputTag_RMB))
	{
		if (ActivatingAbility != nullptr)
			return;

		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
	else
	{
		if (ActivatingAbility != nullptr)
		{
			return;
		}

		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
}

void ADMPlayerController::SetActivatingAbility(UDMGameplayAbility* Ability)
{
	ActivatingAbility = Ability;
}

UDMAbilitySystemComponent* ADMPlayerController::GetASC()
{
	if (DMAbilitySystemComponent == nullptr)
	{
		DMAbilitySystemComponent = Cast<UDMAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return DMAbilitySystemComponent;
}

void ADMPlayerController::AutoRun()
{
	if (!bAutoRunning)
		return;

	if (APawn* ControlledPawn = GetPawn())
	{
		if (ADMPlayer* DMPlayer = Cast<ADMPlayer>(ControlledPawn))
		{
			auto AnimInstance = DMPlayer->GetMesh()->GetAnimInstance();
			AnimInstance->StopAllMontages(0.25);
		}

		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void ADMPlayerController::SetControllerInputMode(EGameState GameState)
{
	GameInputMode.SetConsumeCaptureMouseDown(false);
	switch (GameState)
	{
	case EGameState::Ready:
		SetInputMode(UIInputMode);
		break;
	case EGameState::Playing:
		SetInputMode(GameInputMode);
		break;
	case EGameState::Fail:
		SetInputMode(UIInputMode);
		break;
	case EGameState::Clear:
		SetInputMode(UIInputMode);
		break;
	}
}

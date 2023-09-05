// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "Game/DMGameMode.h"
#include "DMPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class UDMInputConfig;
class UDMAbilitySystemComponent;
class USplineComponent;
class IEnemyInterface;

UCLASS()
class DM_API ADMPlayerController : public APlayerController
{
	GENERATED_BODY()

	ADMPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	/** Called for movement input */
	void Move(const struct FInputActionValue& Value);

private:
	void TickCursorTrace();

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DMContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	IEnemyInterface* TargetActor;

public:
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UDMAbilitySystemComponent* GetASC();

	void AutoRun();

	void ShiftPressed() { bShiftKeyDown = true; }
	void ShiftReleased() { bShiftKeyDown = false; }

	UFUNCTION()
	void SetControllerInputMode(EGameState GameState);

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UDMInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UDMAbilitySystemComponent> DMAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;


	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
	bool bShiftKeyDown = false;
	
private:
	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};

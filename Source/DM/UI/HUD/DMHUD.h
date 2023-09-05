// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Game/DMGameMode.h"
#include "DMHUD.generated.h"

class UDMUserWidget;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
struct FWidgetControllerParams;
class UAttributeMenuWidgetController;
class UIntroWidgetController;
class UGameOverWidgetController;

/**
 * 
 */

UCLASS()
class DM_API ADMHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	void InitIntro(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	void InitGameOver(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	void InitHUD(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	void SetWidgets(EGameState NewState);

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	UIntroWidgetController* GetIntroWidgetController(const FWidgetControllerParams& WCParams);
	UGameOverWidgetController* GetGameOverWidgetController(const FWidgetControllerParams& WCParams);


public:
	UPROPERTY()
	TObjectPtr<UDMUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDMUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UDMUserWidget> IntroWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDMUserWidget> IntroWidgetClass;

	UPROPERTY()
	TObjectPtr<UDMUserWidget> GameOverWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDMUserWidget> GameOverWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UIntroWidgetController> IntroWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIntroWidgetController> IntroWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UGameOverWidgetController> GameOverWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameOverWidgetController> GameOverWidgetControllerClass;

};

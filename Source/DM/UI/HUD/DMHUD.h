// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DMHUD.generated.h"

class UDMUserWidget;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
struct FWidgetControllerParams;
class UAttributeMenuWidgetController;
class UIntroWidgetController;

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

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	UIntroWidgetController* GetIntroWidgetController(const FWidgetControllerParams& WCParams);

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
};

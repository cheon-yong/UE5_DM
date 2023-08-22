// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DMHUD.generated.h"

class UDMUserWidget;
class UDMOverlayWidget;
class APlayerController;
class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;
class UDMAttributeMenuWidget;
struct FWidgetControllerParams;

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

	UDMAttributeMenuWidget* GetAttributeMenuWidget(const FWidgetControllerParams& WCParams);

public:
	UPROPERTY()
	TObjectPtr<UDMOverlayWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDMOverlayWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UDMAttributeMenuWidget> AttributeMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDMAttributeMenuWidget> AttributeMenuWidgetClass;
};

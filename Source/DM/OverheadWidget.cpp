// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString Text)
{
	if (DisplayText)
		DisplayText->SetText(FText::FromString(Text));
}

void UOverheadWidget::SetPlayerNetRole(APawn* Pawn)
{
	ENetRole LocalRole = Pawn->GetLocalRole();

	FString LocalRoleStr;
	switch (LocalRole)
	{
	case ENetRole::ROLE_Authority:
		LocalRoleStr = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		LocalRoleStr = FString("Autonomous");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		LocalRoleStr = FString("Simulated");
		break;
	}

	ENetRole RemoteRole = Pawn->GetRemoteRole();

	FString RemoteRoleStr;
	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority:
		RemoteRoleStr = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		RemoteRoleStr = FString("Autonomous");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		RemoteRoleStr = FString("Simulated");
		break;
	}

	FString ResultStr = FString::Printf(TEXT("Local : %s\n Remote : %s"), *LocalRoleStr, *RemoteRoleStr);
	SetDisplayText(ResultStr);
}

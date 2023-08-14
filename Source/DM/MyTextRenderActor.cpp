// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTextRenderActor.h"

FString AMyTextRenderActor::GetNetMode()
{
	FString NetModeString;
	ENetMode NetMode = GetWorld()->GetNetMode();

	switch (NetMode)
	{
	case NM_Standalone:
		NetModeString = TEXT("Standalone");
		break;
	case NM_ListenServer:
		NetModeString = TEXT("ListenServer");
		break;
	case NM_DedicatedServer:
		NetModeString = TEXT("DedicatedServer");
		break;
	case NM_Client:
		NetModeString = TEXT("Client");
		break;
	}

	return NetModeString;
}

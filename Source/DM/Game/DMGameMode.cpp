// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game/DMGameMode.h"
#include "Character/DMCharacter.h"
#include "Character/DMPlayer.h"
#include "Character/DMMonster.h"
#include "AbilitySystem/DMAttributeSet.h"
#include "UObject/ConstructorHelpers.h"
#include "Game/DMGameStateBase.h"
#include "Controller/DMPlayerController.h"

ADMGameMode::ADMGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));*/


	DefaultPawnClass = DMPlayerClass;
}

void ADMGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ADMGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
}

void ADMGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetGameState(EGameState::Ready);

	GetWorldTimerManager().SetTimer(SpawnActorHandle, this, &ADMGameMode::SpawnActor, 5.0f, true, 5.0f);
	GetWorldTimerManager().PauseTimer(SpawnActorHandle);

	OnChangeGameState.AddDynamic(this, &ADMGameMode::SetGameMode);
}


void ADMGameMode::SetScore(class AActor* ScoredPlayer, int32 NewScore)
{
	if (ADMGameStateBase* DMGameState = Cast<ADMGameStateBase>(GameState))
	{
		DMGameState->SetGameScore(NewScore);

		OnUpdateScore.Broadcast(NewScore);
		if (NewScore >= ScoreToClear)
		{
			SetGameState(EGameState::Clear);
		}
	}
}

void ADMGameMode::SetGameState(EGameState NewState)
{
	if (ADMGameStateBase* DMGameState = Cast<ADMGameStateBase>(GameState))
	{
		if (DMGameState->GetGameState() == NewState)
			return;

		DMGameState->SetGameState(NewState);
		OnChangeGameState.Broadcast(NewState);
	}
}

void ADMGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

}

int32 ADMGameMode::GetScore() const
{
	if (ADMGameStateBase* DMGameState = Cast<ADMGameStateBase>(GameState))
	{
		return DMGameState->GetTotalGameScore();
	}

	return 0;
}

void ADMGameMode::SpawnActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Spawn Actor");
	if (DMMonsterClass != nullptr)
	{
		FVector Location = FVector::Zero();
		Location.X = FMath::FRandRange(200.f, 2500.f);
		Location.Y = FMath::FRandRange(200.f, 2500.f);
		Location.Z = 88.0f;
		FActorSpawnParameters ActorSpawnParameters;

		TObjectPtr<ADMMonster> Monster = GetWorld()->SpawnActor<ADMMonster>(DMMonsterClass, Location, FRotator::ZeroRotator, ActorSpawnParameters);
		if (UDMAttributeSet* DMAS = Cast<UDMAttributeSet>(Monster->GetAttributeSet()))
		{
			DMAS->OnHealthIsZero.AddLambda(
				[this](FEffectProperties* Props)
				{
					Monsters.Remove(Props->TargetAvatarActor->GetName());
					OnUpdateMonster.Broadcast(Monsters.Num());
				}
			); 
		}

		Monsters.Add(Monster->GetName(), Monster);
		OnUpdateMonster.Broadcast(Monsters.Num());
	}
}

void ADMGameMode::SetGameMode(EGameState NewState)
{
	switch (NewState)
	{
	case EGameState::Ready:
	{
		GetWorldTimerManager().PauseTimer(SpawnActorHandle);
		break;
	}
	case EGameState::Playing:
	{
		GetWorldTimerManager().UnPauseTimer(SpawnActorHandle);
		ClearMonsters();
		SetScore(nullptr, 0);
		break;
	}
	case EGameState::Fail:
	{
		GetWorldTimerManager().PauseTimer(SpawnActorHandle);
		break;
	}
	case EGameState::Clear:
	{
		GetWorldTimerManager().PauseTimer(SpawnActorHandle);
		break;
	}
	}
}

void ADMGameMode::ClearMonsters()
{
	for (auto It = Monsters.CreateIterator(); It; ++It)
	{
		TObjectPtr<ADMMonster> Monster = It->Value;
		Monster->Destroy();
	}

	Monsters.Reset();
	OnUpdateMonster.Broadcast(Monsters.Num());
}

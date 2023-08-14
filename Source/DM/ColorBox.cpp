// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorBox.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AColorBox::AColorBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AColorBox::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicates(true);

	// Variable Replication Test
	if (HasAuthority())
	{
		Counter = FMath::RandRange(0, 1000);
		OnRep_Counter();
	}
}

// Called every frame
void AColorBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorBox::OnRep_Counter()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("%d"), Counter));
}

void AColorBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AColorBox, Counter);
}

void AColorBox::MulticastRPC_Implementation()
{
}

void AColorBox::ServerRPC_Implementation(int32 AddHealth)
{
}

bool AColorBox::ServerRPC_Validate(int32 AddHealth)
{
	// Cheating
	if (AddHealth > 10000)
		return false;

	return true;
}


void AColorBox::ClientRPC_Implementation()
{
}
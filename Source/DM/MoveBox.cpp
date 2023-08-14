// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveBox.h"

// Sets default values
AMoveBox::AMoveBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AMoveBox::BeginPlay()
{
	Super::BeginPlay();

	// 꼭 BeginPlay 이후에 코드를 추가할 것.

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called every frame
void AMoveBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Offset = GetActorForwardVector() * DeltaTime * 200.f;
		AddActorWorldOffset(Offset, true);
	}
}


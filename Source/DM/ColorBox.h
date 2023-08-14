// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorBox.generated.h"

UCLASS()
class DM_API AColorBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

protected:
	// Variable Replication

	// 블루프린트에서 Replicated까지 한 과정
	/*UPROPERTY(Replicated)
	int32 Counter = 0;*/

	UPROPERTY(ReplicatedUsing = OnRep_Counter)
	int32 Counter = 0;

	UFUNCTION()
	void OnRep_Counter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPC(int32 AddHealth);

	UFUNCTION(Client, Reliable)
	void ClientRPC();
};

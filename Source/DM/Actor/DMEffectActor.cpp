// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DMEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/DMAttributeSet.h"

// Sets default values
ADMEffectActor::ADMEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ADMEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADMEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADMEffectActor::EndOverlap);
}

void ADMEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UDMAttributeSet* DMAttributeSet = Cast<UDMAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UDMAttributeSet::StaticClass()));

		UDMAttributeSet* MutableDMAttriubteSet = const_cast<UDMAttributeSet*>(DMAttributeSet);
		MutableDMAttriubteSet->SetHealth(DMAttributeSet->GetHealth() - 25.f);
		
		Destroy();
	}
}

void ADMEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



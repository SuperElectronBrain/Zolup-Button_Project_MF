// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActorObject.h"
#include "Components/SphereComponent.h"
#include "MagneticComponent.h"
#include "GamePlayerCharacter.h"
#include "MagneticFieldEffectComponent.h"
#include "MagneticMovementComponent.h"

// Sets default values
ATestActorObject::ATestActorObject()
{
	PrimaryActorTick.bCanEverTick = true;

	/*Sphere*/
	RootComponent = Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	/**Effect*/
	FieldEffect = CreateDefaultSubobject<UMagneticFieldEffectComponent>(TEXT("EFFECT"));
	FieldEffect->SetupAttachment(RootComponent);
}

void ATestActorObject::BeginPlay()
{
	Super::BeginPlay();
}

void ATestActorObject::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if (APawn* player = GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		TArray<USceneComponent*> components;
		player->GetRootComponent()->GetChildrenComponents(true, components);

		for (USceneComponent* component : components)
		{
			UMagneticComponent* magnet = Cast<UMagneticComponent>(component);
			if (magnet && magnet->GetCurrentMagnetMovementType()!=EMagnetMoveType::NONE) {

				UE_LOG(LogTemp, Warning, TEXT("움직이네!!: %f"), type++)
				return;
			}

		}

	}
}



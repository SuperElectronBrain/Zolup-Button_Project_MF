// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerMovementComponent.h"

// Sets default values for this component's properties
UPowerMovementComponent::UPowerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UPowerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	OriginPosition = GetRelativeLocation();
}


// Called every frame
void UPowerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetRelativeLocation(OriginPosition);

	if (bActingState == true)
	{	
		CurrentMovement = FMath::Clamp<float>(CurrentMovement + (ActingSpeed * DeltaTime), 0, ActingRange);
		FVector MovementVector = GetRelativeTransform().GetUnitAxis(EAxis::X) * CurrentMovement;
		SetRelativeLocation(OriginPosition + MovementVector);
	}
	else if (bActingState == false)
	{
		CurrentMovement = FMath::Clamp<float>(CurrentMovement - (ActingSpeed * DeltaTime), 0, ActingRange);
		FVector MovementVector = GetRelativeTransform().GetUnitAxis(EAxis::X) * CurrentMovement;
		SetRelativeLocation(OriginPosition + MovementVector);
	}
	// ...
}

void UPowerMovementComponent::StartAction()
{
	bActingState = true;
}

void UPowerMovementComponent::EndAction()
{
	bActingState = false;
}


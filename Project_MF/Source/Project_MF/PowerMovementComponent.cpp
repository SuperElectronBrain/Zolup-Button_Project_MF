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


	if (bActingState == true)
	{	
		FVector MovementVector = GetForwardVector() * (ActingSpeed * DeltaTime);
		CurrentMovement = CurrentMovement + (MovementVector - GetForwardVector()).Size();
		if (CurrentMovement < ActingRange)
		{
			AddRelativeLocation(MovementVector - GetForwardVector());
		}
		else if (CurrentMovement > ActingRange)
		{
			CurrentMovement = ActingRange;
		}
	}
	else if (bActingState == false)
	{
		FVector MovementVector = GetForwardVector() * (ActingSpeed * DeltaTime);
		CurrentMovement = CurrentMovement - (GetForwardVector() - MovementVector).Size();
		if (CurrentMovement > 0)
		{
			AddRelativeLocation(GetForwardVector() - MovementVector);
		}
		else if (CurrentMovement < 0)
		{
			CurrentMovement = 0;
		}
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


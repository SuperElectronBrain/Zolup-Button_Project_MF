// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerDirectionMovementComponent.h"

UPowerDirectionMovementComponent::UPowerDirectionMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	if (IsRunningCommandlet() == false)
	{
		if (ArrowComponent)
		{
			ArrowComponent->ArrowColor = FColor(150, 200, 255);

			ArrowComponent->ArrowSize = 1.0f;
			ArrowComponent->bTreatAsASprite = true;
			ArrowComponent->SetupAttachment(this);
			ArrowComponent->bIsScreenSizeScaled = true;
		}
	}
#endif
}

void UPowerDirectionMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	OriginPosition = GetRelativeLocation();
}

void UPowerDirectionMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
}
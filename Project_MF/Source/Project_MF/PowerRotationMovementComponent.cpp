// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerRotationMovementComponent.h"

UPowerRotationMovementComponent::UPowerRotationMovementComponent()
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
			ArrowComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
		}
	}
#endif
}

void UPowerRotationMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	OriginRotation = GetOwner()->GetActorQuat().Rotator().Yaw;
}

void UPowerRotationMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bActingState == true)
	{
		CurrentMovement = FMath::Clamp<float>(CurrentMovement + (ActingSpeed * DeltaTime), 0, ActingRange);
		//UE_LOG(LogTemp, Warning, TEXT("(%f, %f, %f)"), GetUpVector().X, GetUpVector().Y, GetUpVector().Z);
		GetOwner()->SetActorRelativeRotation(FQuat(FRotator(GetOwner()->GetActorQuat().Rotator().Pitch, OriginRotation + CurrentMovement, GetOwner()->GetActorQuat().Rotator().Roll)));
		//SetRelativeRotation(FQuat(FVector(0.0f, 0.0f, 1.0f), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
		//SetRelativeRotation(FQuat(GetUpVector(), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
		//SetRelativeRotation(FQuat(GetRelativeTransform().GetUnitAxis(EAxis::Z), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
	}
	else if (bActingState == false)
	{
		CurrentMovement = FMath::Clamp<float>(CurrentMovement - (ActingSpeed * DeltaTime), 0, ActingRange);
		GetOwner()->SetActorRelativeRotation(FQuat(FRotator(GetOwner()->GetActorQuat().Rotator().Pitch, OriginRotation + CurrentMovement, GetOwner()->GetActorQuat().Rotator().Roll)));
		//SetRelativeRotation(FQuat(FVector(0.0f, 0.0f, 1.0f), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
		//SetRelativeRotation(FQuat(GetUpVector(), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
		//SetRelativeRotation(FQuat(GetRelativeTransform().GetUnitAxis(EAxis::Z), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
	}
}
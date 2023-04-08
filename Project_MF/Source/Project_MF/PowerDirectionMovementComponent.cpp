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
			ArrowComponent->SetupAttachment(this);
			ArrowComponent->ArrowSize = 1.0f;
			ArrowComponent->bTreatAsASprite = true;
			ArrowComponent->bIsScreenSizeScaled = true;
		}
	}
#endif
}

void UPowerDirectionMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	OriginPosition = GetOwner()->GetActorLocation();
}

void UPowerDirectionMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Action(DeltaTime);
}

void UPowerDirectionMovementComponent::Action(float DeltaTime)
{
	if (ObserveTarget != nullptr)
	{
		UPowerExecutionComponent* ObserveTargetExecutionComponent = ObserveTarget->FindComponentByClass<UPowerExecutionComponent>();
		if (::IsValid(ObserveTargetExecutionComponent) == true)
		{
			if (ObserveTargetExecutionComponent->GetPowerState() == true)
			{
				CurrentMovement = FMath::Clamp<float>(CurrentMovement + (ActingSpeed * DeltaTime), 0, ActingRange);
				if (CurrentMovement < ActingRange)
				{
					GetOwner()->AddActorLocalOffset(FVector::ForwardVector * (ActingSpeed * DeltaTime));
				}
				//FVector MovementVector = GetOwner()->GetActorTransform().GetUnitAxis(EAxis::X) * CurrentMovement;
				//GetOwner()->SetActorLocation(OriginPosition + MovementVector);
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{
				CurrentMovement = FMath::Clamp<float>(CurrentMovement - (ActingSpeed * DeltaTime), 0, ActingRange);
				if (CurrentMovement > 0)
				{
					GetOwner()->AddActorLocalOffset(FVector::ForwardVector * (-ActingSpeed * DeltaTime));
				}
				//FVector MovementVector = GetOwner()->GetActorTransform().GetUnitAxis(EAxis::X) * CurrentMovement;
				//GetOwner()->SetActorLocation(OriginPosition + MovementVector);
			}
		}
	}
}
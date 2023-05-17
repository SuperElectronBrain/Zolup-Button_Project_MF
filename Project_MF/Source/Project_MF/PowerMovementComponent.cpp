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

void UPowerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (::IsValid(ObserveTarget.Get()) == true)
	{
		ObserveTargetExecutionComponent = ObserveTarget->FindComponentByClass<UPowerComponent>();
	}
	else if (::IsValid(ObserveTarget.Get()) == false)
	{
		USceneComponent* ParentComponent = GetAttachParent();
		while (::IsValid(ParentComponent) == true)
		{
			UPowerComponent* ParentExecutionComponent = Cast<UPowerComponent>(ParentComponent);
			if (::IsValid(ParentExecutionComponent) == true)
			{
				ObserveTargetExecutionComponent = ParentExecutionComponent;
				ParentComponent = nullptr;
			}
			else if (::IsValid(ParentExecutionComponent) == false)
			{
				ParentComponent = ParentComponent->GetAttachParent();
			}
		}
	}
}

void UPowerMovementComponent::StartAction()
{
	bActingState = true;
}

void UPowerMovementComponent::EndAction()
{
	bActingState = false;
}
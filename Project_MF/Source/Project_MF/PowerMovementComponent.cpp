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
		ObserveTargetExecutionComponent = ObserveTarget->FindComponentByClass<UPowerExecutionComponent>();
	}
	else if (::IsValid(ObserveTarget.Get()) == false)
	{
		USceneComponent* ParentComponent = GetAttachParent();
		while (::IsValid(ParentComponent) == true)
		{
			UPowerComponent* ParentPowerComponent = Cast<UPowerComponent>(ParentComponent);
			if (::IsValid(ParentPowerComponent) == true)
			{
				ObserveTargetExecutionComponent = ParentPowerComponent;
				ParentComponent = nullptr;
			}
			else if (::IsValid(ParentPowerComponent) == false)
			{
				ParentComponent = ParentComponent->GetAttachParent();
			}
		}

		if (::IsValid(ObserveTargetExecutionComponent.Get()) == false)
		{
			TArray<USceneComponent*> ParentsComponents = GetAttachParent()->GetAttachChildren();
			for (int i = 0; i < ParentsComponents.Num(); i = i + 1)
			{
				UPowerComponent* PowerComponent = Cast<UPowerComponent>(ParentsComponents[i]);
				if (::IsValid(PowerComponent) == true)
				{
					ObserveTargetExecutionComponent = PowerComponent;
					break;
				}
			}
		}

		if (::IsValid(ObserveTargetExecutionComponent.Get()) == false)
		{
			ObserveTargetExecutionComponent = GetOwner()->FindComponentByClass<UPowerComponent>();
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
// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerLightControlComponent.h"
#include "Components/LightComponent.h"

UPowerLightControlComponent::UPowerLightControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPowerLightControlComponent::BeginPlay()
{
}

void UPowerLightControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Action(DeltaTime);
}

void UPowerLightControlComponent::Action(float DeltaTime)
{
	if (ObserveTarget != nullptr)
	{
		UPowerExecutionComponent* ObserveTargetExecutionComponent = ObserveTarget->FindComponentByClass<UPowerExecutionComponent>();
		if (::IsValid(ObserveTargetExecutionComponent) == true)
		{
			if (ObserveTargetExecutionComponent->GetPowerState() == true)
			{
				ULightComponent* ObserveTargetLightComponent = GetOwner()->FindComponentByClass<ULightComponent>();
				if (::IsValid(ObserveTargetLightComponent) == true)
				{
					ObserveTargetLightComponent->SetVisibility(true);
				}
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{
				ULightComponent* ObserveTargetLightComponent = GetOwner()->FindComponentByClass<ULightComponent>();
				if (::IsValid(ObserveTargetLightComponent) == true)
				{
					ObserveTargetLightComponent->SetVisibility(false);
				}
			}
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerLightControlComponent.h"
#include "Components/LightComponent.h"

UPowerLightControlComponent::UPowerLightControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ReversAction = false;
	NonReversibleAction = false;
}

void UPowerLightControlComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPowerLightControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
					if (ObserveTargetLightComponent->IsVisible() == ReversAction)
					{
						ObserveTargetLightComponent->SetVisibility(!ReversAction);
					}
				}
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{
				if (NonReversibleAction == false)
				{
					ULightComponent* ObserveTargetLightComponent = GetOwner()->FindComponentByClass<ULightComponent>();
					if (::IsValid(ObserveTargetLightComponent) == true)
					{
						if (ObserveTargetLightComponent->IsVisible() == !ReversAction)
						{
							ObserveTargetLightComponent->SetVisibility(ReversAction);
						}
					}
				}
			}
		}
	}
}
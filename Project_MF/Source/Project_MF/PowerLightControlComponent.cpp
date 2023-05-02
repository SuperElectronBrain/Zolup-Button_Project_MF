// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerLightControlComponent.h"
#include "Components/LightComponent.h"

UPowerLightControlComponent::UPowerLightControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ReversAction = false;
	NonReversibleAction = false;
	UseDisableColor = false;
}

void UPowerLightControlComponent::BeginPlay()
{
	Super::BeginPlay();

	ULightComponent* ObserveTargetLightComponent = GetOwner()->FindComponentByClass<ULightComponent>();
	OriginalColor = ObserveTargetLightComponent->GetLightColor().ToFColor(false);

	if (::IsValid(ObserveTarget.Get()) == true)
	{
		if (::IsValid(ObserveTargetLightComponent) == true)
		{
			if (UseDisableColor == false)
			{
				ObserveTargetLightComponent->SetVisibility(ReversAction);
			}
			else if (UseDisableColor == true)
			{
				ObserveTargetLightComponent->SetLightColor(ReversAction == true ? OriginalColor : DisableColor);
			}
		}
	}
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
				if (bActingState == false)
				{
					ULightComponent* ObserveTargetLightComponent = GetOwner()->FindComponentByClass<ULightComponent>();
					if (::IsValid(ObserveTargetLightComponent) == true)
					{
						if (UseDisableColor == false)
						{
							if (ObserveTargetLightComponent->IsVisible() == ReversAction)
							{
								ObserveTargetLightComponent->SetVisibility(!ReversAction);
							}
						}
						else if (UseDisableColor == true)
						{
							ObserveTargetLightComponent->SetLightColor(ReversAction == false ? OriginalColor : DisableColor);
						}
					}

					if (NonReversibleAction == true)
					{
						SetComponentTickEnabled(false);
					}

					bActingState = true;
				}
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{
				if (bActingState == true)
				{
					if (NonReversibleAction == false)
					{
						ULightComponent* ObserveTargetLightComponent = GetOwner()->FindComponentByClass<ULightComponent>();
						if (::IsValid(ObserveTargetLightComponent) == true)
						{
							if (UseDisableColor == false)
							{
								if (ObserveTargetLightComponent->IsVisible() == !ReversAction)
								{
									ObserveTargetLightComponent->SetVisibility(ReversAction);
								}
							}
							else if (UseDisableColor == true)
							{
								ObserveTargetLightComponent->SetLightColor(ReversAction == true ? OriginalColor : DisableColor);
							}
						}
					}
					bActingState = false;
				}
			}
		}
	}
}
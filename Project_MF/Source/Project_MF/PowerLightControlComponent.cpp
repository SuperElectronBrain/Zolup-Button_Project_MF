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

	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		LightComponent = GetOwner()->FindComponentByClass<ULightComponent>();
		OriginalColor = LightComponent->GetLightColor().ToFColor(false);

		if (::IsValid(LightComponent.Get()) == true)
		{
			if (UseDisableColor == false)
			{
				LightComponent->SetVisibility(ReversAction);
			}
			else if (UseDisableColor == true)
			{
				LightComponent->SetLightColor(ReversAction == true ? OriginalColor : DisableColor);
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
	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			if (bActingState == false)
			{
				if (::IsValid(LightComponent.Get()) == true)
				{
					if (UseDisableColor == false)
					{
						if (LightComponent->IsVisible() == ReversAction)
						{
							LightComponent->SetVisibility(!ReversAction);
						}
					}
					else if (UseDisableColor == true)
					{
						LightComponent->SetLightColor(ReversAction == false ? OriginalColor : DisableColor);
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
					if (::IsValid(LightComponent.Get()) == true)
					{
						if (UseDisableColor == false)
						{
							if (LightComponent->IsVisible() == !ReversAction)
							{
								LightComponent->SetVisibility(ReversAction);
							}
						}
						else if (UseDisableColor == true)
						{
							LightComponent->SetLightColor(ReversAction == true ? OriginalColor : DisableColor);
						}
					}
				}
				bActingState = false;
			}
		}
	}
}
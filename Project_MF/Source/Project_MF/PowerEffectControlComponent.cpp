// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerEffectControlComponent.h"

UPowerEffectControlComponent::UPowerEffectControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ReversAction = false;
	NonReversibleAction = false;
}

void UPowerEffectControlComponent::BeginPlay()
{
	Super::BeginPlay();

	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		UFXSystemComponent* FXSystemComponent = GetOwner()->FindComponentByClass<UFXSystemComponent>();
		if (::IsValid(FXSystemComponent) == true)
		{
			if (ReversAction == false)
			{
				FXSystemComponent->Deactivate();
			}
			else if (ReversAction == true)
			{
				FXSystemComponent->Activate(true);
			}
		}
	}
}

void UPowerEffectControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Action(DeltaTime);
}

void UPowerEffectControlComponent::Action(float DeltaTime)
{
	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			if (bActingState == false)
			{
				UFXSystemComponent* FXSystemComponent = GetOwner()->FindComponentByClass<UFXSystemComponent>();
				if (::IsValid(FXSystemComponent) == true)
				{
					if (ReversAction == false)
					{
						FXSystemComponent->Activate(true);
					}
					else if (ReversAction == true)
					{
						FXSystemComponent->Deactivate();
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
					UFXSystemComponent* FXSystemComponent = GetOwner()->FindComponentByClass<UFXSystemComponent>();
					if (::IsValid(FXSystemComponent) == true)
					{
						if (ReversAction == false)
						{
							FXSystemComponent->Deactivate();
						}
						else if (ReversAction == true)
						{
							FXSystemComponent->Activate(true);
						}
					}
				}
				bActingState = false;
			}
		}
	}
}
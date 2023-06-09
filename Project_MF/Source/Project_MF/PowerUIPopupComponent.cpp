// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUIPopupComponent.h"

UPowerUIPopupComponent::UPowerUIPopupComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ReversAction = false;
	NonReversibleAction = true;
}

void UPowerUIPopupComponent::BeginPlay()
{
	Super::BeginPlay();

	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (::IsValid(UMGClass) == true)
		{
			UMGInstance = CreateWidget<UUserWidget>(GetWorld(), UMGClass);
			UMGInstance->AddToViewport();
			
			if (ReversAction == false)
			{
				UMGInstance->SetVisibility(ESlateVisibility::Collapsed);
			}
			else if (ReversAction == true)
			{
				UMGInstance->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UPowerUIPopupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Action(DeltaTime);
}

void UPowerUIPopupComponent::Action(float DeltaTime)
{
	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			if (bActingState == false)
			{
				if (::IsValid(UMGInstance) == true)
				{
					if (ReversAction == false)
					{
						UMGInstance->SetVisibility(ESlateVisibility::Visible);
					}
					else if (ReversAction == true)
					{
						UMGInstance->SetVisibility(ESlateVisibility::Collapsed);
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
					if (::IsValid(UMGInstance) == true)
					{
						if (ReversAction == false)
						{
							UMGInstance->SetVisibility(ESlateVisibility::Collapsed);
						}
						else if (ReversAction == true)
						{
							UMGInstance->SetVisibility(ESlateVisibility::Visible);
						}
					}
				}

				bActingState = false;
			}
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerVisibleControlComponent.h"

UPowerVisibleControlComponent::UPowerVisibleControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ReversAction = true;
	NonReversibleAction = false;
	UseCollisionControl = true;
}

void UPowerVisibleControlComponent::BeginPlay()
{
	Super::BeginPlay();

	if (::IsValid(ObserveTarget.Get()) == true)
	{
		GetAttachParent()->SetVisibility(ReversAction);
		if (UseCollisionControl == true)
		{
			ParentPrimitive = Cast<UPrimitiveComponent>(GetAttachParent());
			if (::IsValid(ParentPrimitive.Get()) == true)
			{
				OriginCollisionProfile = ParentPrimitive->GetCollisionProfileName().ToString();
				ParentPrimitive->SetCollisionProfileName(ReversAction == true ? *OriginCollisionProfile : TEXT("NoCollision"));
			}
		}
	}
}

void UPowerVisibleControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Action(DeltaTime);
}

void UPowerVisibleControlComponent::Action(float DeltaTime)
{
	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			if (bActingState == false)
			{
				if (GetAttachParent()->GetVisibleFlag() == ReversAction)
				{
					GetAttachParent()->SetVisibility(!ReversAction);
					if (UseCollisionControl == true)
					{
						if (::IsValid(ParentPrimitive.Get()) == true)
						{
							if (OriginCollisionProfile != TEXT(""))
							{
								ParentPrimitive->SetCollisionProfileName(ReversAction == false ? *OriginCollisionProfile : TEXT("NoCollision"));
							}
						}
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
					if (GetAttachParent()->GetVisibleFlag() == !ReversAction)
					{
						GetAttachParent()->SetVisibility(ReversAction);
						if (UseCollisionControl == true)
						{
							if (::IsValid(ParentPrimitive.Get()) == true)
							{
								if (OriginCollisionProfile != TEXT(""))
								{
									ParentPrimitive->SetCollisionProfileName(ReversAction == true ? *OriginCollisionProfile : TEXT("NoCollision"));
								}
							}
						}
					}
				}
				bActingState = false;
			}
		}
	}
}
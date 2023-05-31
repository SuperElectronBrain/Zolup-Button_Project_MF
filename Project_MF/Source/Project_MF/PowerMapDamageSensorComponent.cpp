// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerMapDamageSensorComponent.h"

// Sets default values for this component's properties
UPowerMapDamageSensorComponent::UPowerMapDamageSensorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ReversSignal = false;
	NonReversibleSignal = true;
	// ...
}


// Called when the game starts
void UPowerMapDamageSensorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (::IsValid(ObserveTarget.Get()) == true)
	{
		ObserveTargetGameMapSectionComponent = ObserveTarget->FindComponentByClass<UGameMapSectionComponent>();
	}

	if (::IsValid(ReceivingTarget.Get()) == true)
	{
		ReceivingTargetGenerateComponent = ReceivingTarget->FindComponentByClass<UPowerGenerateComponent>();
	}
	else if (::IsValid(ReceivingTarget.Get()) == false)
	{
		USceneComponent* ParentComponent = GetAttachParent();
		while (::IsValid(ParentComponent) == true)
		{
			UPowerComponent* ParentGenerateComponent = Cast<UPowerComponent>(ParentComponent);
			if (::IsValid(ParentGenerateComponent) == true)
			{
				ReceivingTargetGenerateComponent = ParentGenerateComponent;
				ParentComponent = nullptr;
			}
			else if (::IsValid(ParentGenerateComponent) == false)
			{
				ParentComponent = ParentComponent->GetAttachParent();
			}
		}

		if (::IsValid(ReceivingTargetGenerateComponent.Get()) == false)
		{
			TArray<USceneComponent*> ParentsComponents = GetAttachParent()->GetAttachChildren();
			for (int i = 0; i < ParentsComponents.Num(); i = i + 1)
			{
				UPowerComponent* PowerGenerateComponent = Cast<UPowerComponent>(ParentsComponents[i]);
				if (::IsValid(PowerGenerateComponent) == true)
				{
					ReceivingTargetGenerateComponent = PowerGenerateComponent;
					break;
				}
			}
		}

		if (::IsValid(ReceivingTargetGenerateComponent.Get()) == false)
		{
			ReceivingTargetGenerateComponent = GetOwner()->FindComponentByClass<UPowerComponent>();
		}
	}

	if (::IsValid(ReceivingTargetGenerateComponent.Get()) == true)
	{
		if (::IsValid(ObserveTargetGameMapSectionComponent.Get()) == true)
		{
			ReceivingTargetGenerateComponent->SetPowerState(ReversSignal, true);
		}
	}
}


// Called every frame
void UPowerMapDamageSensorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (::IsValid(ReceivingTargetGenerateComponent.Get()) == true && ::IsValid(ObserveTargetGameMapSectionComponent.Get()) == true)
	{
		if (ObserveTargetGameMapSectionComponent->GetCurrSectionDMGCount() == TriggerCount)
		{
			if (ReceivingTargetGenerateComponent->GetPowerState() == ReversSignal)
			{
				ReceivingTargetGenerateComponent->SetPowerState(!ReversSignal, true);
			}

			if (NonReversibleSignal == true)
			{
				SetComponentTickEnabled(false);
			}
		}
		else if (ObserveTargetGameMapSectionComponent->GetCurrSectionDMGCount() != TriggerCount)
		{
			if (NonReversibleSignal == false)
			{
				if (ReceivingTargetGenerateComponent->GetPowerState() == !ReversSignal)
				{
					ReceivingTargetGenerateComponent->SetPowerState(ReversSignal, true);
				}
			}
		}
	}
}


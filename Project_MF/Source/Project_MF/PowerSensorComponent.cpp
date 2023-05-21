// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerSensorComponent.h"
#include "GameFramework/Character.h"

UPowerSensorComponent::UPowerSensorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MinimumWeight = 0.0f;
	PlayerOnly = false;
	ReversSignal = false;
	NonReversibleSignal = false;
}

void UPowerSensorComponent::BeginPlay()
{
	Super::BeginPlay();
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetGenerateOverlapEvents(true);

	if (::IsValid(ReceivingTarget) == true)
	{
		ReceivingTargetGenerateComponent = ReceivingTarget->FindComponentByClass<UPowerGenerateComponent>();
		if (::IsValid(ReceivingTargetGenerateComponent.Get()) == true)
		{
			ReceivingTargetGenerateComponent->SetPowerState(ReversSignal, true);
		}
	}
	else if (::IsValid(ReceivingTarget) == false)
	{
		USceneComponent* ParentComponent = GetAttachParent();
		while (::IsValid(ParentComponent) == true)
		{
			UPowerGenerateComponent* ParentGenerateComponent = Cast<UPowerGenerateComponent>(ParentComponent);
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
	}
}

void UPowerSensorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (::IsValid(ReceivingTargetGenerateComponent.Get()) == true)
	{
		int Count = 0;
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);
		for (int i = 0; i < OverlappingActors.Num(); i = i + 1)
		{
			if (OverlappingActors[i] != GetOwner())
			{
				if (OverlappingActors[i]->GetRootComponent()->Mobility == EComponentMobility::Movable)
				{
					UPrimitiveComponent* OverlapActorsPrimitive = Cast<UPrimitiveComponent>(OverlappingActors[i]->GetRootComponent());
					if (::IsValid(OverlapActorsPrimitive) == true)
					{
						float ActorMass = 0.0f;
						if (OverlapActorsPrimitive->IsSimulatingPhysics() == true) { ActorMass = OverlapActorsPrimitive->GetMass(); }
						else if(OverlapActorsPrimitive->IsSimulatingPhysics() == false) { ActorMass = 0.1f; }

						if (ActorMass > MinimumWeight)
						{
							if (PlayerOnly == true)
							{
								if (::IsValid(Cast<ACharacter>(OverlappingActors[i])) == true)
								{
									Count = Count + 1;
									break;
								}
							}
							else if (PlayerOnly == false)
							{
								Count = Count + 1;
								break;
							}
						}
					}
				}
			}
		}

		if (Count > 0)
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
		else if (Count < 1)
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
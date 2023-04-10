// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerSensorComponent.h"
#include "GameFramework/Character.h"

UPowerSensorComponent::UPowerSensorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetGenerateOverlapEvents(true);

	PlayerOnly = false;
	ReversSignal = false;
	NonReversibleSignal = false;
}

//void UPowerSensorComponent::BeginPlay()
//{
//}

void UPowerSensorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (::IsValid(ReceivingTarget) == true)
	{
		UPowerGenerateComponent* ReceivingTargetGenerateComponent = ReceivingTarget->FindComponentByClass<UPowerGenerateComponent>();
		if (::IsValid(ReceivingTargetGenerateComponent) == true)
		{
			int Count = 0;
			TArray<AActor*> OverlappingActors;
			GetOverlappingActors(OverlappingActors);
			for (int i = 0; i < OverlappingActors.Num(); i = i + 1)
			{
				if (OverlappingActors[i]->GetRootComponent()->Mobility == EComponentMobility::Movable)
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

			if (Count > 0)
			{
				if (ReceivingTargetGenerateComponent->GetPowerState() == ReversSignal)
				{
					ReceivingTargetGenerateComponent->SetPowerState(!ReversSignal, true);
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
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerObjectSpawnerComponent.h"

UPowerObjectSpawnerComponent::UPowerObjectSpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	OneTime = true;
}

void UPowerObjectSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> ParentsComponents = GetAttachParent()->GetAttachChildren();
	for (int i = 0; i < ParentsComponents.Num(); i = i + 1)
	{
		UArrowComponent* Arrow = Cast<UArrowComponent>(ParentsComponents[i]);
		if (::IsValid(Arrow) == true)
		{
			ArrowComponent = Arrow;
			ArrowComponent->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform);
			break;
		}
	}
}

void UPowerObjectSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Action(DeltaTime);
}


void UPowerObjectSpawnerComponent::Action(float DeltaTime)
{
	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			if (bActingState == false)
			{
				bActingState = true;

				if (::IsValid(ArrowComponent.Get()) == true)
				{
					GetWorld()->SpawnActor<AActor>(OriginActor, ArrowComponent->GetComponentLocation(), ArrowComponent->GetComponentRotation());
				}


				if (OneTime == true)
				{
					SetComponentTickEnabled(false);
				}
			}
		}
		else if (ObserveTargetExecutionComponent->GetPowerState() == false)
		{
			if (bActingState == true)
			{
				bActingState = false;
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerEmissiveControlComponent.h"

UPowerEmissiveControlComponent::UPowerEmissiveControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ReversAction = false;
	NonReversibleAction = false;
	ParameterName = "Emissive";
}

void UPowerEmissiveControlComponent::BeginPlay()
{
	Super::BeginPlay();

	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		UStaticMeshComponent* ParentStaticMeshComponent = Cast<UStaticMeshComponent>(GetAttachParent());
		if (::IsValid(ParentStaticMeshComponent) == true)
		{
			UStaticMesh* ParentStaticMesh = ParentStaticMeshComponent->GetStaticMesh();
			if (::IsValid(ParentStaticMesh) == true)
			{
				UMaterialInterface* ParentMaterial = ParentStaticMeshComponent->GetMaterial(0);
				if (::IsValid(ParentMaterial) == true)
				{
					DynamicMaterial = UMaterialInstanceDynamic::Create(ParentMaterial, ParentStaticMeshComponent);
					if (::IsValid(DynamicMaterial) == true)
					{
						ParentStaticMeshComponent->SetMaterial(0, DynamicMaterial);
					}
				}
			}
		}
		else if (::IsValid(ParentStaticMeshComponent) == false)
		{
			if (GetOwner()->GetRootComponent() != GetAttachParent())
			{
				UStaticMeshComponent* OwnerStaticMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
				if (::IsValid(OwnerStaticMeshComponent) == true)
				{
					UStaticMesh* OwnerStaticMesh = OwnerStaticMeshComponent->GetStaticMesh();
					if (::IsValid(OwnerStaticMesh) == true)
					{
						UMaterialInterface* OwnerMaterial = OwnerStaticMeshComponent->GetMaterial(0);
						if (::IsValid(OwnerMaterial) == true)
						{
							DynamicMaterial = UMaterialInstanceDynamic::Create(OwnerMaterial, OwnerStaticMeshComponent);
							if (::IsValid(DynamicMaterial) == true)
							{
								OwnerStaticMeshComponent->SetMaterial(0, DynamicMaterial);
							}
						}
					}
				}
			}
		}
		
		if (::IsValid(DynamicMaterial) == true)
		{
			OriginalStrength = DynamicMaterial->K2_GetScalarParameterValue(*ParameterName);
			DynamicMaterial->SetScalarParameterValue(*ParameterName, ReversAction == true ? OriginalStrength : 0.0f);
		}
	}
}

void UPowerEmissiveControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Action(DeltaTime);
}

void UPowerEmissiveControlComponent::Action(float DeltaTime)
{
	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			if (bActingState == false)
			{
				if (::IsValid(DynamicMaterial) == true)
				{
					DynamicMaterial->SetScalarParameterValue(*ParameterName, ReversAction == false ? OriginalStrength : 0.0f);
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
					if (::IsValid(DynamicMaterial) == true)
					{
						DynamicMaterial->SetScalarParameterValue(*ParameterName, ReversAction == true ? OriginalStrength : 0.0f);
					}
				}
				bActingState = false;
			}
		}
	}
}
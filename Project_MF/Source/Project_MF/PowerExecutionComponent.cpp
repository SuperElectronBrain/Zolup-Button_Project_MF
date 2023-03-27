// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerExecutionComponent.h"
#include "PowerMovementComponent.h"

UPowerExecutionComponent::UPowerExecutionComponent()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (SM_BOX.Succeeded() == true) { MeshOrigin = SM_BOX.Object; }
	static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Game/Resource/Materials/M_MFMaterial.M_MFMaterial"));
	if (M_MATERIAL.Succeeded() == true) { MaterialOrigin = M_MATERIAL.Object; }

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(this);
	if (SM_BOX.Succeeded() == true)
	{
		Mesh->SetStaticMesh(SM_BOX.Object);
		if (M_MATERIAL.Succeeded() == true)
		{
			Mesh->SetMaterial(0, M_MATERIAL.Object);
		}
	}

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(this);
	Collider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	Collider->SetCollisionProfileName(TEXT("Collider"));
}

void UPowerExecutionComponent::BeginPlay()
{
	UpdateMaterialColor();
}

void UPowerExecutionComponent::UpdateMaterialColor()
{
	UMaterialInstanceDynamic* DynamicMaterial = Mesh->CreateDynamicMaterialInstance(0);
	if (DynamicMaterial != nullptr)
	{
		if (bPowerState == true)
		{
			DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(0.0f, 0.5f, 1.0f));
		}
		else if (bPowerState == false)
		{
			DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(0.5f, 0.5f, 0.5f));
		}
	}
}

void UPowerExecutionComponent::SetPowerState(bool param, bool IsGenerator)
{
	if (bPowerState != param)
	{
		bPowerState = param;

		if (bPowerState == true)
		{
			TArray<UActorComponent*> PowerMovementComponents = GetOwner()->GetComponentsByClass(UPowerMovementComponent::StaticClass());
			for (int i = 0; i < PowerMovementComponents.Num(); i = i + 1)
			{
				UPowerMovementComponent* PowerMovementComponent = Cast<UPowerMovementComponent>(PowerMovementComponents[i]);
				if (PowerMovementComponent != nullptr)
				{
					PowerMovementComponent->StartAction();
				}
			}
		}
		else if (bPowerState == false)
		{
			TArray<UActorComponent*> PowerMovementComponents = GetOwner()->GetComponentsByClass(UPowerMovementComponent::StaticClass());
			for (int i = 0; i < PowerMovementComponents.Num(); i = i + 1)
			{
				UPowerMovementComponent* PowerMovementComponent = Cast<UPowerMovementComponent>(PowerMovementComponents[i]);
				if (PowerMovementComponent != nullptr)
				{
					PowerMovementComponent->EndAction();
				}
			}
		}

		UpdateMaterialColor();
	}
}


void UPowerExecutionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void UPowerExecutionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

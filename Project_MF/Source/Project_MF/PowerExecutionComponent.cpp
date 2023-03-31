// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerExecutionComponent.h"
#include "PowerMovementComponent.h"

UPowerExecutionComponent::UPowerExecutionComponent()
{
	//Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	//Trigger->SetupAttachment(this);

	static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Game/Resource/Materials/M_MFMaterial.M_MFMaterial"));
	if (M_MATERIAL.Succeeded() == true) { MaterialOrigin = M_MATERIAL.Object; }

}

void UPowerExecutionComponent::BeginPlay()
{
	//FVector TriggerVolume = FVector::OneVector;
	UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerRootComponent) == true)
	{
		if (MaterialOrigin != nullptr)
		{
			MaterialIndexNum = OwnerRootComponent->GetNumMaterials();
			OwnerRootComponent->SetMaterial(MaterialIndexNum, MaterialOrigin);
		}
		OwnerRootComponent->SetCollisionProfileName(TEXT("Collider"));
		OwnerRootComponent->SetGenerateOverlapEvents(true);
		OwnerRootComponent->OnComponentBeginOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapBegin);
		OwnerRootComponent->OnComponentEndOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapEnd);

		//Trigger->SetCollisionProfileName("OverlapAllDynamic");
		//Trigger->SetGenerateOverlapEvents(true);
		//Trigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapBegin);
		//Trigger->OnComponentEndOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapEnd);

		//TriggerVolume = OwnerRootComponent->GetRelativeScale3D();
	}
	//Trigger->SetBoxExtent(FVector(50.01f * TriggerVolume.X, 50.01f * TriggerVolume.Y, 50.01f * TriggerVolume.Z));

	UpdateMaterialColor();
}

void UPowerExecutionComponent::UpdateMaterialColor()
{
	UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerRootComponent) == true)
	{
		UMaterialInstanceDynamic* DynamicMaterial = OwnerRootComponent->CreateDynamicMaterialInstance(MaterialIndexNum);
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
}

void UPowerExecutionComponent::SetPowerState(bool param, bool IsGenerator)
{
	if (bPowerState != param)
	{
		bPowerState = param;

		//if (bPowerState == true)
		//{
		//	TArray<UActorComponent*> PowerMovementComponents = GetOwner()->GetComponentsByClass(UPowerMovementComponent::StaticClass());
		//	for (int i = 0; i < PowerMovementComponents.Num(); i = i + 1)
		//	{
		//		UPowerMovementComponent* PowerMovementComponent = Cast<UPowerMovementComponent>(PowerMovementComponents[i]);
		//		if (PowerMovementComponent != nullptr)
		//		{
		//			PowerMovementComponent->StartAction();
		//		}
		//	}
		//}
		//else if (bPowerState == false)
		//{
		//	TArray<UActorComponent*> PowerMovementComponents = GetOwner()->GetComponentsByClass(UPowerMovementComponent::StaticClass());
		//	for (int i = 0; i < PowerMovementComponents.Num(); i = i + 1)
		//	{
		//		UPowerMovementComponent* PowerMovementComponent = Cast<UPowerMovementComponent>(PowerMovementComponents[i]);
		//		if (PowerMovementComponent != nullptr)
		//		{
		//			PowerMovementComponent->EndAction();
		//		}
		//	}
		//}

		UpdateMaterialColor();
	}
}


void UPowerExecutionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void UPowerExecutionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

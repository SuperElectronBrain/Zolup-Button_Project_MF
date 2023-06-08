// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerExecutionComponent.h"
#include "PowerMovementComponent.h"

UPowerExecutionComponent::UPowerExecutionComponent()
{
	//Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	//Trigger->SetupAttachment(this);

	//static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	//if (M_MATERIAL.Succeeded() == true) { MaterialOrigin = M_MATERIAL.Object; }

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(this);
	Collider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	Collider->SetCollisionProfileName(TEXT("Collider"));
	Collider->SetGenerateOverlapEvents(true);
}

void UPowerExecutionComponent::BeginPlay()
{
	Super::BeginPlay();
	SetRelativeScale3D(FVector::OneVector);
	//FVector TriggerVolume = FVector::OneVector;
	USceneComponent* OwnerRootComponent = GetOwner()->GetRootComponent();
#pragma region UnUsed
	//UPrimitiveComponent* OwnerRootPrimitive = Cast<UPrimitiveComponent>(OwnerRootComponent);
	//if (::IsValid(OwnerRootPrimitive) == true)
	//{
		//if (MaterialOrigin != nullptr)
		//{
		//	MaterialIndexNum = OwnerRootPrimitive->GetNumMaterials();
		//	OwnerRootPrimitive->SetMaterial(0, MaterialOrigin);
		//}
		//OwnerRootComponent->SetCollisionProfileName(TEXT("Collider"));
		//OwnerRootComponent->SetGenerateOverlapEvents(true);
		//OwnerRootComponent->OnComponentBeginOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapBegin);
		//OwnerRootComponent->OnComponentEndOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapEnd);

		//Trigger->SetCollisionProfileName("OverlapAllDynamic");
		//Trigger->SetGenerateOverlapEvents(true);
		//Trigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapBegin);
		//Trigger->OnComponentEndOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapEnd);

		//TriggerVolume = OwnerRootComponent->GetRelativeScale3D();
	//}
#pragma endregion
	//FVector ParentScale = GetAttachParent()->GetRelativeScale3D();
	//FVector OwnerScale = OwnerRootComponent->GetRelativeScale3D();
	UStaticMeshComponent* ParentStaticMesh = Cast<UStaticMeshComponent>(GetAttachParent());
	//UStaticMeshComponent* OwnerRootStaticMesh = Cast<UStaticMeshComponent>(OwnerRootComponent);
	FVector ParentBounds = ParentStaticMesh != nullptr ? (ParentStaticMesh->GetStaticMesh() != nullptr ? ParentStaticMesh->GetStaticMesh()->GetBounds().BoxExtent : FVector::OneVector * 50) : FVector::OneVector * 50;
	//Collider->SetBoxExtent(FVector(OwnerRootBounds.X * OwnerScale.X, OwnerRootBounds.Y * OwnerScale.Y, OwnerRootBounds.Z * OwnerScale.Z));
	Collider->SetBoxExtent(FVector(ParentBounds.X, ParentBounds.Y, ParentBounds.Z));
	//Trigger->SetBoxExtent(FVector(50.01f * TriggerVolume.X, 50.01f * TriggerVolume.Y, 50.01f * TriggerVolume.Z));

	Collider->OnComponentBeginOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &UPowerExecutionComponent::OnOverlapEnd);

	//UpdateMaterialColor();
}

void UPowerExecutionComponent::UpdateMaterialColor()
{
	//UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//if (::IsValid(OwnerRootComponent) == true)
	//{
	//	UMaterialInstanceDynamic* DynamicMaterial = OwnerRootComponent->CreateDynamicMaterialInstance(0);
	//	if (DynamicMaterial != nullptr)
	//	{
	//		if (bPowerState == true)
	//		{
	//			DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(0.0f, 0.5f, 1.0f));
	//		}
	//		else if (bPowerState == false)
	//		{
	//			DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(0.5f, 0.5f, 0.5f));
	//		}
	//	}
	//}
}

void UPowerExecutionComponent::SetPowerState(bool param, bool IsGenerator)
{
	if (bPowerState != param)
	{
		bPowerState = param;
#pragma region UnUsed
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
#pragma endregion
		//UpdateMaterialColor();
	}
}

void UPowerExecutionComponent::BeginDestroy()
{
	Super::BeginDestroy();

	//if (::IsValid(Collider) == true)
	//{
	//	Collider->DestroyComponent();
	//}
}

void UPowerExecutionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void UPowerExecutionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

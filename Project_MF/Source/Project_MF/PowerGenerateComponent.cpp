// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerGenerateComponent.h"
#include "DrawDebugHelpers.h"

UPowerGenerateComponent::UPowerGenerateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	TriggerSize = 1;
	bPowerState = true;

#pragma region UnUsed
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Engine/BasicShapes/Cube.Cube"));
	//if (SM_BOX.Succeeded() == true) { MeshOrigin = SM_BOX.Object; }
#pragma endregion
	//static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	//if (M_MATERIAL.Succeeded() == true) { MaterialOrigin = M_MATERIAL.Object; }

#pragma region UnUsed
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->SetupAttachment(this);
	//if (SM_BOX.Succeeded() == true) 
	//{ 
	//	Mesh->SetStaticMesh(SM_BOX.Object);
	//	if (M_MATERIAL.Succeeded() == true)
	//	{
	//		Mesh->SetMaterial(0, M_MATERIAL.Object);
	//	}
	//}
#pragma endregion

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(this);
	Collider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	Collider->SetCollisionProfileName(TEXT("Collider"));
	Collider->SetGenerateOverlapEvents(true);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(this);
}

void UPowerGenerateComponent::BeginPlay()
{
	Super::BeginPlay();
	SetRelativeScale3D(FVector::OneVector);
	USceneComponent* OwnerRootComponent = GetOwner()->GetRootComponent();
	//UPrimitiveComponent* OwnerRootPrimitive = Cast<UPrimitiveComponent>(OwnerRootComponent);
	//if (::IsValid(OwnerRootPrimitive) == true)
	//{
		//if (MaterialOrigin != nullptr)
		//{
		//	MaterialIndexNum = OwnerRootPrimitive->GetNumMaterials();
		//	OwnerRootPrimitive->SetMaterial(0, MaterialOrigin);
		//}
		//OwnerRootPrimitive->SetCollisionProfileName(TEXT("Collider"));
		//OwnerRootPrimitive->SetGenerateOverlapEvents(true);
	//}
	
	float BoxSize = TriggerSize * 100.0f;
	FVector ParentScale = GetAttachParent()->GetRelativeScale3D();
	//FVector OwnerRootScale = OwnerRootComponent->GetRelativeScale3D();
	UStaticMeshComponent* ParentStaticMesh = Cast<UStaticMeshComponent>(GetAttachParent());
	FVector ParentBounds = ParentStaticMesh != nullptr ? (ParentStaticMesh->GetStaticMesh() != nullptr ? ParentStaticMesh->GetStaticMesh()->GetBounds().BoxExtent : FVector::OneVector * 50) : FVector::OneVector * 50;
	//FVector OwnerRootBounds = OwnerRootStaticMesh != nullptr ? (OwnerRootStaticMesh->GetStaticMesh() != nullptr ? OwnerRootStaticMesh->GetStaticMesh()->GetBounds().BoxExtent : FVector::OneVector * 50) : FVector::OneVector * 50;
	
	if (::IsValid(Collider) == true)
	{
		//Collider->SetBoxExtent(FVector((ParentScale.X * OwnerRootBounds.X), (ParentScale.Y * OwnerRootBounds.Y), (ParentScale.Z * OwnerRootBounds.Z)));
		//Collider->AttachToComponent(OwnerRootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Collider->SetBoxExtent(FVector(ParentBounds.X, ParentBounds.Y, ParentBounds.Z));
	}
	if (::IsValid(Trigger) == true)
	{
		//Trigger->SetBoxExtent(FVector((ParentScale.X * OwnerRootBounds.X) + (BoxSize / ParentScale.X), (ParentScale.Y * OwnerRootBounds.Y) + (BoxSize / ParentScale.Y), (ParentScale.Z * OwnerRootBounds.Z) + (BoxSize / ParentScale.Z)));
		//Trigger->AttachToComponent(OwnerRootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Trigger->SetBoxExtent(FVector(ParentBounds.X + (BoxSize / ParentScale.X), ParentBounds.Y + (BoxSize / ParentScale.Y), ParentBounds.Z + (BoxSize / ParentScale.Z)));
		Trigger->SetCollisionProfileName("NewTrigger");
		Trigger->SetGenerateOverlapEvents(true);
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerGenerateComponent::OnOverlapBegin);
		Trigger->OnComponentEndOverlap.AddDynamic(this, &UPowerGenerateComponent::OnOverlapEnd);
	}

	SetPowerState(!bPowerState, true);
	SetPowerState(!bPowerState, true);
	//UpdateMaterialColor();
}

void UPowerGenerateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
#pragma region UnUsed
//#if ENABLE_DRAW_DEBUG
//	float BoxSize = TriggerSize * 100.0f;
//	FVector OwnerScale = GetOwner()->GetRootComponent()->GetRelativeScale3D();
//	DrawDebugBox(GetWorld(), GetOwner()->GetRootComponent()->GetComponentLocation(), FVector((OwnerScale.X * 50.0f) + BoxSize, (OwnerScale.Y * 50.0f) + BoxSize, (OwnerScale.Z * 50.0f) + BoxSize), FQuat(GetOwner()->GetActorRotation()), FColor::Red, false, 0.1f);
//#endif
#pragma endregion
}

void UPowerGenerateComponent::UpdateMaterialColor()
{
	//UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//if (::IsValid(OwnerRootComponent) == true)
	//{
	//	UMaterialInstanceDynamic* DynamicMaterial = OwnerRootComponent->CreateDynamicMaterialInstance(0);
	//	if (DynamicMaterial != nullptr)
	//	{
	//		if (bPowerState == true)
	//		{
	//			DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(1.0f, 0.5f, 0.0f));
	//		}
	//
	//		else if (bPowerState == false)
	//		{
	//			DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(0.5f, 0.5f, 0.5f));
	//		}
	//	}
	//}
}

void UPowerGenerateComponent::SetPowerState(bool param, bool IsGenerator)
{
	if (bPowerState != param)
	{
		if (IsGenerator == true)
		{
			bPowerState = param;
		}

		float BoxSize = TriggerSize * 100.0f;
		//USceneComponent* OwnerRootComponent = GetOwner()->GetRootComponent();
		FVector ParentScale = GetAttachParent()->GetRelativeScale3D();
		//FVector OwnerScale = OwnerRootComponent->GetRelativeScale3D();
		UStaticMeshComponent* ParentStaticMesh = Cast<UStaticMeshComponent>(GetAttachParent());
		//UStaticMeshComponent* OwnerRootStaticMesh = Cast<UStaticMeshComponent>(OwnerRootComponent);
		FVector ParentBounds = ParentStaticMesh != nullptr ? (ParentStaticMesh->GetStaticMesh() != nullptr ? ParentStaticMesh->GetStaticMesh()->GetBounds().BoxExtent : FVector::OneVector * 50) : FVector::OneVector * 50;
		FVector TriggerVolume = FVector((ParentScale.X * ParentBounds.X) + BoxSize, (ParentScale.Y * ParentBounds.Y) + BoxSize, (ParentScale.Z * ParentBounds.Z) + BoxSize);
		
		TArray<FHitResult> HitResult;
		FCollisionQueryParams Params(NAME_None, false, GetOwner());
		bool bResult = GetWorld()->SweepMultiByChannel
		(
			HitResult,
			GetComponentLocation(),
			GetComponentLocation(),
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel4,
			FCollisionShape::MakeBox(TriggerVolume),
			Params
		);
#pragma region UnUsed
#if ENABLE_DRAW_DEBUG
		//FColor DrawColor = bResult == true ? FColor::Green : FColor::Red;
		//float DebugLifeTime = 0.1f;
		//DrawDebugBox(GetWorld(), GetComponentLocation(), TriggerVolume, FQuat(GetOwner()->GetActorRotation()), DrawColor, false, DebugLifeTime);
#endif
#pragma endregion

		if (bResult == true)
		{
			for (int i = 0; i < HitResult.Num(); i = i + 1)
			{;
				if (::IsValid(HitResult[i].GetComponent()) == true)
				{
					if (::IsValid(HitResult[i].GetComponent()->GetAttachParent()) == true)
					{
						UPowerGenerateComponent* PowerGenerateComponent = Cast<UPowerGenerateComponent>(HitResult[i].GetComponent()->GetAttachParent());
						if (::IsValid(PowerGenerateComponent) == false)
						{
							//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult[i].GetComponent()->GetAttachParent()->GetName());
							UPowerComponent* PowerComponent = Cast<UPowerComponent>(HitResult[i].GetComponent()->GetAttachParent());
							if (::IsValid(PowerComponent) == true)
							{
								if (PowerComponent != this)
								{
									
									PowerComponent->SetPowerState(bPowerState);
								}
							}
						}
					}
					/*UPowerGenerateComponent* PowerGenerateComponent = Cast<UPowerGenerateComponent>(HitResult[i].GetActor()->FindComponentByClass<UPowerGenerateComponent>());
					if (PowerGenerateComponent == nullptr)
					{
						UPowerComponent* PowerComponent = Cast<UPowerComponent>(HitResult[i].GetActor()->FindComponentByClass<UPowerComponent>());
						if (PowerComponent != nullptr)
						{
							if (PowerComponent != this)
							{
								PowerComponent->SetPowerState(bPowerState);
							}
						}
					}*/
				}
			}
		}
		//UpdateMaterialColor();
	}
}

void UPowerGenerateComponent::BeginDestroy()
{
	Super::BeginDestroy();

	//if (::IsValid(Collider) == true)
	//{
	//	Collider->DestroyComponent();
	//}
	//if (::IsValid(Trigger) == true)
	//{
	//	Trigger->DestroyComponent();
	//}
}

void UPowerGenerateComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UPowerComponent* PowerComponent = OtherActor->FindComponentByClass<UPowerComponent>();
	if (::IsValid(OtherComp->GetAttachParent()) == true)
	{
		UPowerComponent* PowerComponent = Cast<UPowerComponent>(OtherComp->GetAttachParent());
		if (::IsValid(PowerComponent) == true)
		{
			if (PowerComponent != this)
			{
				if (bPowerState == true)
				{
					PowerComponent->SetPowerState(true);
				}
			}
		}
	}
}

void UPowerGenerateComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UPowerComponent* PowerComponent = OtherActor->FindComponentByClass<UPowerComponent>();

	if (::IsValid(OtherComp->GetAttachParent()) == true)
	{
		UPowerComponent* PowerComponent = Cast<UPowerComponent>(OtherComp->GetAttachParent());
		if (PowerComponent != nullptr)
		{
			if (PowerComponent != this)
			{
				SetPowerState(false);
				PowerComponent->SetPowerState(false);
			}
		}
	}
}
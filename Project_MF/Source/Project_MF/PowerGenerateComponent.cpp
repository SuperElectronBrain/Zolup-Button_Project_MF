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
	static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (M_MATERIAL.Succeeded() == true) { MaterialOrigin = M_MATERIAL.Object; }

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

	UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerRootComponent) == true)
	{
		if (MaterialOrigin != nullptr)
		{
			MaterialIndexNum = OwnerRootComponent->GetNumMaterials();
			OwnerRootComponent->SetMaterial(0, MaterialOrigin);
		}
		//OwnerRootComponent->SetCollisionProfileName(TEXT("Collider"));
		//OwnerRootComponent->SetGenerateOverlapEvents(true);
	}
	
	float BoxSize = TriggerSize * 100.0f;
	FVector OwnerScale = GetOwner()->GetRootComponent()->GetRelativeScale3D();
	Trigger->SetBoxExtent(FVector(50.0f + (BoxSize / OwnerScale.X), 50.0f + (BoxSize / OwnerScale.Y), 50.0f + (BoxSize / OwnerScale.Z)));
	Trigger->SetCollisionProfileName("NewTrigger");
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerGenerateComponent::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &UPowerGenerateComponent::OnOverlapEnd);

	SetPowerState(!bPowerState, true);
	SetPowerState(!bPowerState, true);
	UpdateMaterialColor();
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
	UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerRootComponent) == true)
	{
		UMaterialInstanceDynamic* DynamicMaterial = OwnerRootComponent->CreateDynamicMaterialInstance(0);
		if (DynamicMaterial != nullptr)
		{
			if (bPowerState == true)
			{
				DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(1.0f, 0.5f, 0.0f));
			}

			else if (bPowerState == false)
			{
				DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(0.5f, 0.5f, 0.5f));
			}
		}
	}
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
		FVector OwnerScale = GetOwner()->GetRootComponent()->GetRelativeScale3D();
		FVector TriggerVolume = FVector((OwnerScale.X * 50.0f) + BoxSize, (OwnerScale.Y * 50.0f) + BoxSize, (OwnerScale.Z * 50.0f) + BoxSize);
		
		TArray<FHitResult> HitResult;
		FCollisionQueryParams Params(NAME_None, false, GetOwner());
		bool bResult = GetWorld()->SweepMultiByChannel
		(
			HitResult,
			GetOwner()->GetActorLocation(),
			GetOwner()->GetActorLocation(),
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel4,
			FCollisionShape::MakeBox(TriggerVolume),
			Params
		);
#pragma region UnUsed
//#if ENABLE_DRAW_DEBUG
//			FColor DrawColor = bResult == true ? FColor::Green : FColor::Red;
//			float DebugLifeTime = 5.0f;
//			float BoxSize = TriggerSize * 100.0f;
//			FVector OwnerScale = GetOwner()->GetRootComponent()->GetRelativeScale3D();
//			DrawDebugBox(GetWorld(), GetOwner()->GetRootComponent()->GetComponentLocation(), TriggerVolume, FQuat(GetOwner()->GetActorRotation()), DrawColor, false, DebugLifeTime);
//#endif
#pragma endregion

		if (bResult == true)
		{
			for (int i = 0; i < HitResult.Num(); i = i + 1)
			{
				if (HitResult[i].Actor.IsValid() == true)
				{
					UPowerGenerateComponent* PowerGenerateComponent = Cast<UPowerGenerateComponent>(HitResult[i].Actor->FindComponentByClass<UPowerGenerateComponent>());
					if (PowerGenerateComponent == nullptr)
					{
						UPowerComponent* PowerComponent = Cast<UPowerComponent>(HitResult[i].Actor->FindComponentByClass<UPowerComponent>());
						if (PowerComponent != nullptr)
						{
							if (PowerComponent != this)
							{
								PowerComponent->SetPowerState(bPowerState);
							}
						}
					}
				}
			}
		}
		UpdateMaterialColor();
	}
}

void UPowerGenerateComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UPowerComponent* PowerConnectionComponent = OtherActor->FindComponentByClass<UPowerComponent>();
	if (PowerConnectionComponent != nullptr)
	{
		if (PowerConnectionComponent != this)
		{
			if (bPowerState == true)
			{
				PowerConnectionComponent->SetPowerState(true);
			}
		}
	}
}

void UPowerGenerateComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UPowerComponent* PowerConnectionComponent = OtherActor->FindComponentByClass<UPowerComponent>();
	if (PowerConnectionComponent != nullptr)
	{
		if (PowerConnectionComponent != this)
		{
			SetPowerState(false);
			PowerConnectionComponent->SetPowerState(false);
		}
	}
}
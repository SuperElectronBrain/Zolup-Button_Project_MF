// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerGenerateComponent.h"
#include "DrawDebugHelpers.h"

UPowerGenerateComponent::UPowerGenerateComponent()
{
	TriggerSize = 3;
	bPowerState = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (SM_BOX.Succeeded() == true) { MeshOrigin = SM_BOX.Object; }
	static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Game/Resource/Other/Materials/M_MFMaterial.M_MFMaterial"));
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
	Collider->SetCollisionProfileName(TEXT("Carrier"));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(this);
	float BoxSize = TriggerSize * 50.0f;
	Trigger->SetBoxExtent(FVector(BoxSize, BoxSize, BoxSize));
	Trigger->SetCollisionProfileName(TEXT("Connector"));
}

void UPowerGenerateComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Mesh->SetStaticMesh(MeshOrigin);

	Collider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	float BoxSize = TriggerSize * 50.0f;
	Trigger->SetBoxExtent(FVector(BoxSize, BoxSize, BoxSize));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerGenerateComponent::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &UPowerGenerateComponent::OnOverlapEnd);
	
	SetPowerState(!bPowerState, true);
	SetPowerState(!bPowerState, true);
	UpdateMaterialColor();
}

void UPowerGenerateComponent::UpdateMaterialColor()
{
	UMaterialInstanceDynamic* DynamicMaterial = Mesh->CreateDynamicMaterialInstance(0);
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

void UPowerGenerateComponent::SetPowerState(bool param, bool IsGenerator)
{
	if (bPowerState != param)
	{
		if (IsGenerator == true)
		{
			bPowerState = param;
		}

		float BoxSize = TriggerSize * 50.0f;
		FVector TriggerVolume = FVector(BoxSize, BoxSize, BoxSize);
		
		TArray<FHitResult> HitResult;
		FCollisionQueryParams Params(NAME_None, false, GetOwner());
		bool bResult = GetWorld()->SweepMultiByChannel
		(
			HitResult,
			GetOwner()->GetActorLocation(),
			GetOwner()->GetActorLocation(),
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel2,
			FCollisionShape::MakeBox(TriggerVolume),
			Params
		);

//#if ENABLE_DRAW_DEBUG
//			FColor DrawColor = bResult == true ? FColor::Green : FColor::Red;
//			float DebugLifeTime = 5.0f;
//
//			DrawDebugBox(GetWorld(), GetOwner()->GetActorLocation(), TriggerVolume, FQuat(GetOwner()->GetActorRotation()), DrawColor, false, DebugLifeTime);
//#endif

		if (bResult == true)
		{
			for (int i = 0; i < HitResult.Num(); i = i + 1)
			{
				if (HitResult[i].Actor.IsValid() == true)
				{
					UPowerComponent* PowerConnectionComponent = Cast<UPowerComponent>(HitResult[i].Actor->FindComponentByClass<UPowerComponent>());
					if (PowerConnectionComponent != nullptr)
					{
						if (PowerConnectionComponent != this)
						{
							PowerConnectionComponent->SetPowerState(bPowerState);
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
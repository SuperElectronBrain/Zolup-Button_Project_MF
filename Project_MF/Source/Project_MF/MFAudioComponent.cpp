// Fill out your copyright notice in the Description page of Project Settings.


#include "MFAudioComponent.h"
#include "CustomGameInstance.h"

UMFAudioComponent::UMFAudioComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMFAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	UPrimitiveComponent* OwnerPrimitive = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerPrimitive) == true)
	{
		if (OwnerPrimitive->Mobility == EComponentMobility::Movable)
		{
			if (OwnerPrimitive->IsSimulatingPhysics() == true)
			{
				OwnerPrimitive->SetNotifyRigidBodyCollision(true);
				OwnerPrimitive->OnComponentHit.AddDynamic(this, &UMFAudioComponent::OnHit);
			}
		}
	}
}

void UMFAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<TWeakObjectPtr<AActor>> ExitActors;
	for (int32 i = 0; i < HitActors.Num(); i = i + 1)
	{
		if (HitActors[i].TickCount == 1)
		{
			OnCollisionEnter(HitActors[i].HitActor.Get());
		}

		HitActors[i].TickCount = HitActors[i].TickCount + 1;
		if (HitActors[i].HitCount != HitActors[i].TickCount)
		{
			OnCollisionExit(HitActors[i].HitActor.Get());
			ExitActors.Add(HitActors[i].HitActor);
		}
	}
	
	for (int32 i = 0; i < ExitActors.Num(); i = i + 1)
	{
		for (int32 j = 0; j < HitActors.Num(); j = j + 1)
		{
			if (HitActors[j].HitActor == ExitActors[i])
			{
				HitActors.RemoveAt(j);
				break;
			}
		}
	}
}

void UMFAudioComponent::OnCollisionEnter(AActor* Collision)
{
	if (GetOwner()->GetVelocity().Size() > 10.0f)
	{
		//float OriginalVolume = VolumeMultiplier;
		USoundBase* OriginalSound = Sound;
		float VolumeMultiply = 1.0f;
		UMFAudioComponent* TargetAudioComp = Collision->FindComponentByClass<UMFAudioComponent>();
		if (::IsValid(TargetAudioComp) == true)
		{
			for (int32 i = 0; i < VolumeMultiplySetting.Num(); i = i + 1)
			{
				if (VolumeMultiplySetting[i].MaterialType == TargetAudioComp->MaterialType)
				{
					VolumeMultiply = VolumeMultiplySetting[i].VolumeMultiply;
					if (::IsValid(VolumeMultiplySetting[i].VariationSound) == true)
					{
						Sound = VolumeMultiplySetting[i].VariationSound;
					}
				}
			}
		}

		VolumeMultiplier = (GetOwner()->GetVelocity().Size() / 100) * VolumeMultiply;
		Play();
		Sound = OriginalSound;
		//VolumeMultiplier = OriginalVolume;
	}
}

void UMFAudioComponent::OnCollisionExit(AActor* Collision)
{

}

void UMFAudioComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	SetWorldLocation(Hit.ImpactPoint);

	int32 Count = 0;
	for (int32 i = 0; i < HitActors.Num(); i = i + 1)
	{
		if (HitActors[i].HitActor == OtherActor)
		{
			HitActors[i].HitCount = HitActors[i].HitCount + 1;
	
			Count = Count + 1;
		}
	}
	
	if (Count < 1)
	{
		HitActors.Add(FCollisionData(OtherActor, 1, 0));
	
		//UE_LOG(LogTemp, Warning, TEXT("%s Hit Start"), *OtherActor->GetName());
	}
}
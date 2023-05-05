// Fill out your copyright notice in the Description page of Project Settings.


#include "MFAudioComponent.h"

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

	//TArray<int32> ExitActors;
	//for (int32 i = 0; i < HitActors.Num(); i = i + 1)
	//{
	//	HitActors[i].TickCount = HitActors[i].TickCount + 1;
	//	if (HitActors[i].HitCount != HitActors[i].TickCount)
	//	{
	//		//UE_LOG(LogTemp, Warning, TEXT("%d, %d"), HitActors[i].HitCount, HitActors[i].TickCount);
	//		//UE_LOG(LogTemp, Warning, TEXT("%s Hit End"), *HitActors[i].HitActor->GetName());
	//
	//		ExitActors.Add(i);
	//	}
	//}
	//
	//for (int32 i = 0; i < ExitActors.Num(); i = i + 1)
	//{
	//	HitActors.RemoveAt(ExitActors[i]);
	//}
}

void UMFAudioComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(GetOwner()->GetVelocity().Size() > 10.0f)
	{ 
		Play();
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());
	//
	//int32 Count = 0;
	//for (int32 i = 0; i < HitActors.Num(); i = i + 1)
	//{
	//	if (HitActors[i].HitActor == OtherActor)
	//	{
	//		HitActors[i].HitCount = HitActors[i].HitCount + 1;
	//
	//		Count = Count + 1;
	//	}
	//}
	//
	//if (Count < 1)
	//{
	//	HitActors.Add(FCollisionData(OtherActor, 1, 0));
	//
	//	UE_LOG(LogTemp, Warning, TEXT("%s Hit Start"), *OtherActor->GetName());
	//}
}
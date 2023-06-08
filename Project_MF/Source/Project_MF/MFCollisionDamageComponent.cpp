// Fill out your copyright notice in the Description page of Project Settings.


#include "MFCollisionDamageComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UMFCollisionDamageComponent::UMFCollisionDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMFCollisionDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UPrimitiveComponent* OwnerPrimitive = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerPrimitive) == false)
	{
		OwnerPrimitive = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	}

	if (::IsValid(OwnerPrimitive) == true)
	{
		OwnerPrimitive->SetNotifyRigidBodyCollision(true);
		OwnerPrimitive->OnComponentHit.AddDynamic(this, &UMFCollisionDamageComponent::OnHit);
	}
}


// Called every frame
void UMFCollisionDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

	// ...
}

void UMFCollisionDamageComponent::OnCollisionEnter(AActor* Collision)
{
	APawn* Pawn = Cast<APawn>(Collision);

	if (::IsValid(Pawn) == true)
	{

		Pawn->TakeDamage(1, FDamageEvent(), (AController*)nullptr, GetOwner());
	}
}

void UMFCollisionDamageComponent::OnCollisionExit(AActor* Collision)
{

}

void UMFCollisionDamageComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
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
	}
}

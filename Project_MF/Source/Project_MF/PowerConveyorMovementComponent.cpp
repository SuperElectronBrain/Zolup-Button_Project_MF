// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerConveyorMovementComponent.h"

UPowerConveyorMovementComponent::UPowerConveyorMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	if (IsRunningCommandlet() == false)
	{
		if (ArrowComponent)
		{
			ArrowComponent->ArrowColor = FColor(150, 200, 255);

			ArrowComponent->ArrowSize = 1.0f;
			ArrowComponent->bTreatAsASprite = true;
			ArrowComponent->SetupAttachment(this);
			ArrowComponent->bIsScreenSizeScaled = true;
		}
	}
#endif

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(this);
	Trigger->SetBoxExtent(FVector(50.001f, 50.001f, 50.001f));
}

void UPowerConveyorMovementComponent::BeginPlay()
{
	UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerRootComponent) == true)
	{
		Trigger->SetCollisionProfileName("OverlapAllDynamic");
		Trigger->SetGenerateOverlapEvents(true);

		Trigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerConveyorMovementComponent::OnOverlapBegin);
		Trigger->OnComponentEndOverlap.AddDynamic(this, &UPowerConveyorMovementComponent::OnOverlapEnd);
		
		//OwnerRootComponent->OnComponentHit.AddDynamic(this, &UPowerConveyorMovementComponent::OnHit);
		//OwnerRootComponent->SetNotifyRigidBodyCollision(true);
	}
}

void UPowerConveyorMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Action(DeltaTime);

	UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerRootComponent) == true)
	{
		TArray<AActor*> actors;
		OwnerRootComponent->GetOverlappingActors(actors);
		for (int i = 0; i < actors.Num(); i = i + 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *actors[i]->GetName());
		}
	}
}

void UPowerConveyorMovementComponent::Action(float DeltaTime)
{
	if (ObserveTarget != nullptr)
	{
		UPowerExecutionComponent* ObserveTargetExecutionComponent = ObserveTarget->FindComponentByClass<UPowerExecutionComponent>();
		if (::IsValid(ObserveTargetExecutionComponent) == true)
		{
			if (ObserveTargetExecutionComponent->GetPowerState() == true)
			{
				for (int i = 0; i < MovableTargets.Num(); i = i + 1)
				{
					MovableTargets[i]->AddActorWorldOffset(GetForwardVector() * (ActingSpeed * DeltaTime));
				}
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{

			}
		}
	}
}

void UPowerConveyorMovementComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
}

void UPowerConveyorMovementComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("î"));
	if (GetOwner() != OtherActor)
	{
		UPrimitiveComponent* CollisionTargetRootComponent = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
		if (::IsValid(CollisionTargetRootComponent) == true)
		{
			if (CollisionTargetRootComponent->IsSimulatingPhysics() == true)
			{
				int Count = 0;
				for (int i = 0; i < MovableTargets.Num(); i = i + 1)
				{
					if (MovableTargets[i] == OtherActor)
					{
						Count = Count + 1;
						break;
					}
				}

				if (Count < 1)
				{
					MovableTargets.Add(OtherActor);
				}
			}
		}
	}
}

void UPowerConveyorMovementComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GetOwner() != OtherActor)
	{
		for (int i = 0; i < MovableTargets.Num(); i = i + 1)
		{
			if (MovableTargets[i] == OtherActor)
			{
				MovableTargets.RemoveAt(i);
				break;
			}
		}
	}
}
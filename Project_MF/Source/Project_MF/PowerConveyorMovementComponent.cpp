// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerConveyorMovementComponent.h"
#include "MovementRegistComponent.h"

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
					UMovementRegistComponent* MovementRegistComponent = MovableTargets[i]->FindComponentByClass<UMovementRegistComponent>();
					if (MovementRegistComponent != nullptr)
					{
						if (MovementRegistComponent->MovementComponents[0] == this)
						{
							MovableTargets[i]->AddActorWorldOffset(GetForwardVector() * (ActingSpeed * DeltaTime));
						}
					}
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
				int Count_0 = 0;
				for (int i = 0; i < MovableTargets.Num(); i = i + 1)
				{
					if (MovableTargets[i] == OtherActor)
					{
						Count_0 = Count_0 + 1;
						break;
					}
				}
				if (Count_0 < 1)
				{
					MovableTargets.Add(OtherActor);

					UMovementRegistComponent* MovementRegistComponent = OtherActor->FindComponentByClass<UMovementRegistComponent>();
					if (MovementRegistComponent == nullptr)
					{
						MovementRegistComponent = NewObject<UMovementRegistComponent>(OtherActor, UMovementRegistComponent::StaticClass());
						MovementRegistComponent->RegisterComponent();
					}

					int Count_1 = 0;
					for (int j = 0; j < MovementRegistComponent->MovementComponents.Num(); j = j + 1)
					{
						if (MovementRegistComponent->MovementComponents[j] == this)
						{
							Count_1 = Count_1 + 1;
							break;
						}
					}
					if (Count_1 < 1)
					{
						MovementRegistComponent->MovementComponents.Add(this);
					}
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
				UMovementRegistComponent* MovementRegistComponent = MovableTargets[i]->FindComponentByClass<UMovementRegistComponent>();
				if (MovementRegistComponent != nullptr)
				{
					for (int j = 0; j < MovementRegistComponent->MovementComponents.Num(); j = j + 1)
					{
						if (MovementRegistComponent->MovementComponents[j] == this)
						{
							MovementRegistComponent->MovementComponents.RemoveAt(j);
							break;
						}
					}
				}

				if (MovementRegistComponent->MovementComponents.Num() < 1)
				{
					MovementRegistComponent->UnregisterComponent();
					MovementRegistComponent->DestroyComponent();
				}

				MovableTargets.RemoveAt(i);
				break;
			}
		}
	}
}
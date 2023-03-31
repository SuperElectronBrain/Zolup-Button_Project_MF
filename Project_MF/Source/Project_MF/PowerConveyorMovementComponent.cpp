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
	Trigger->SetBoxExtent(FVector(50.01f, 50.01f, 50.01f));
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
							FVector MovementVector = GetForwardVector() * (ActingSpeed * DeltaTime);
							AActor* MovableTarget = MovableTargets[i];
							MovableTarget->AddActorWorldOffset(MovementVector, true);
							if (MovableTarget->GetVelocity().Size() < 0.01f)
							{
								MovableTarget->AddActorWorldOffset(MovementVector / 2);
							}

							UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(MovableTarget->GetRootComponent());
							if (::IsValid(OwnerRootComponent) == true)
							{
								//UE_LOG(LogTemp, Warning, TEXT("(%f, %f, %f)"), GetForwardVector().X, GetForwardVector().Y, GetForwardVector().Z);
								//OwnerRootComponent->AddForce(GetForwardVector() * (ActingSpeed * DeltaTime * OwnerRootComponent->GetMass()));

								//FVector Center = FVector((MovableTarget->GetActorLocation() + GetOwner()->GetActorLocation()) / 2);
								//Center = Center + GetForwardVector();
								//OwnerRootComponent->AddForceAtLocation(GetForwardVector() * (5000 * ActingSpeed * DeltaTime * OwnerRootComponent->GetMass()), Center);
								//OwnerRootComponent->SetPhysicsLinearVelocity(GetForwardVector() * (ActingSpeed * DeltaTime), true);
								//if (MovableTarget->GetVelocity().Size() < 0.01f)
								//{
								//	MovableTarget->AddActorWorldOffset(MovementVector / 2);
								//}
							}
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
	//UE_LOG(LogTemp, Warning, TEXT("오이오이 마지카요 넷또 오소스기다제"));
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
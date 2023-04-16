// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerConveyorMovementComponent.h"
#include "MovementRegistComponent.h"
#include "DrawDebugHelpers.h"

UPowerConveyorMovementComponent::UPowerConveyorMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

//#if WITH_EDITORONLY_DATA
	//ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	//ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	//
	//if (IsRunningCommandlet() == false)
	//{
	//	if (ArrowComponent)
	//	{
	//		ArrowComponent->ArrowColor = FColor(150, 200, 255);
	//		ArrowComponent->SetupAttachment(this);
	//		ArrowComponent->ArrowSize = 1.0f;
	//		ArrowComponent->bTreatAsASprite = true;
	//		ArrowComponent->bIsScreenSizeScaled = false;
	//	}
	//}
//#endif
	
	//Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(this);
	Trigger->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
}

void UPowerConveyorMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetRelativeScale3D(FVector::OneVector);
#pragma region UnUsed
	//FVector ColliderSize = FVector::OneVector;
	//UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//if (::IsValid(OwnerRootComponent) == true)
	//{
	//	Collider->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//	Collider->SetRelativeLocation(FVector::ZeroVector);
	//	ColliderSize = OwnerRootComponent->GetRelativeScale3D();
	//}
	//
	//Collider->SetCollisionProfileName("BlockAllDynamic");
	//Collider->SetBoxExtent(FVector(50.1f * (ColliderSize.X / 2), 50.1f * ColliderSize.Y, 50.1f * ColliderSize.Z));

//#if ENABLE_DRAW_DEBUG
//			FColor DrawColor = false ? FColor::Green : FColor::Red;
//			float DebugLifeTime = 5.0f;
//			DrawDebugBox(GetWorld(), Collider->GetComponentLocation(), FVector(55.0f * (ColliderSize.X / 2), 55.0f * ColliderSize.Y, 55.0f * ColliderSize.Z), FQuat(GetOwner()->GetActorRotation()), DrawColor, false, DebugLifeTime);
//#endif
#pragma endregion

	FVector TriggerSize = FVector::OneVector;
	UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerRootComponent) == true)
	{
		Trigger->AttachToComponent(OwnerRootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Trigger->SetCollisionProfileName("OverlapAllDynamic");
		Trigger->SetGenerateOverlapEvents(true);
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerConveyorMovementComponent::OnOverlapBegin);
		Trigger->OnComponentEndOverlap.AddDynamic(this, &UPowerConveyorMovementComponent::OnOverlapEnd);

#pragma region UnUsed	
		//OwnerRootComponent->OnComponentHit.AddDynamic(this, &UPowerConveyorMovementComponent::OnHit);
		//OwnerRootComponent->SetNotifyRigidBodyCollision(true);
#pragma endregion

		TriggerSize = OwnerRootComponent->GetRelativeScale3D();
	}

	FVector OwnerRootScale = OwnerRootComponent->GetRelativeScale3D();
	UStaticMeshComponent* OwnerRootStaticMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector OwnerRootBounds = OwnerRootStaticMesh != nullptr ? (OwnerRootStaticMesh->GetStaticMesh() != nullptr ? OwnerRootStaticMesh->GetStaticMesh()->GetBounds().BoxExtent : FVector::OneVector * 50) : FVector::OneVector * 50;
	Trigger->SetBoxExtent(FVector(OwnerRootBounds.X * 1.0f, OwnerRootBounds.Y * 1.0f, OwnerRootBounds.Z * 1.2f));
	//Trigger->SetBoxExtent(FVector(50.0f * TriggerSize.X, 50.0f * TriggerSize.Y, 50.0f * TriggerSize.Z));

	//ArrowComponent->AttachToComponent(OwnerRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ArrowComponent = GetOwner()->FindComponentByClass<UArrowComponent>();

#pragma region UnUsed
	//FVector TriggerVolume = FVector(50.01f * TriggerSize.X, 50.01f * TriggerSize.Y, 50.01f * TriggerSize.Z);
	//TArray<FHitResult> HitResult;
	//FCollisionQueryParams Params(NAME_None, false, GetOwner());
	//bool bResult = GetWorld()->SweepMultiByChannel
	//(
	//	HitResult,
	//	GetOwner()->GetActorLocation(),
	//	GetOwner()->GetActorLocation(),
	//	FQuat::Identity,
	//	ECollisionChannel::ECC_WorldDynamic,
	//	FCollisionShape::MakeBox(TriggerVolume),
	//	Params
	//);
	//if (bResult == true)
	//{
	//	for (int i = 0; i < HitResult.Num(); i = i + 1)
	//	{
	//		if (HitResult[i].Actor.IsValid() == true)
	//		{
	//			if (GetOwner() != HitResult[i].Actor)
	//			{
	//				UPrimitiveComponent* CollisionTargetRootComponent = Cast<UPrimitiveComponent>(HitResult[i].Actor->GetRootComponent());
	//				if (::IsValid(CollisionTargetRootComponent) == true)
	//				{
	//					if (CollisionTargetRootComponent->IsSimulatingPhysics() == true)
	//					{
	//						int Count_0 = 0;
	//						for (int j = 0; j < MovableTargets.Num(); j = j + 1)
	//						{
	//							if (MovableTargets[j] == HitResult[j].Actor)
	//							{
	//								Count_0 = Count_0 + 1;
	//								break;
	//							}
	//						}
	//						if (Count_0 < 1)
	//						{
	//							MovableTargets.Add(HitResult[i].Actor->GetRootComponent()->GetOwner());
	//
	//							UMovementRegistComponent* MovementRegistComponent = HitResult[i].Actor->FindComponentByClass<UMovementRegistComponent>();
	//							if (MovementRegistComponent == nullptr)
	//							{
	//								MovementRegistComponent = NewObject<UMovementRegistComponent>(HitResult[i].Actor->GetRootComponent()->GetOwner(), UMovementRegistComponent::StaticClass());
	//								MovementRegistComponent->RegisterComponent();
	//								UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult[i].Actor->GetName());
	//							}
	//
	//							int Count_1 = 0;
	//							for (int j = 0; j < MovementRegistComponent->MovementComponents.Num(); j = j + 1)
	//							{
	//								if (MovementRegistComponent->MovementComponents[j] == this)
	//								{
	//									Count_1 = Count_1 + 1;
	//									break;
	//								}
	//							}
	//							if (Count_1 < 1)
	//							{
	//								MovementRegistComponent->MovementComponents.Add(this);
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
#pragma endregion
}

void UPowerConveyorMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Action(DeltaTime);
}

void UPowerConveyorMovementComponent::Action(float DeltaTime)
{
	if (::IsValid(ObserveTarget.Get()) == true)
	{
		UPowerExecutionComponent* ObserveTargetExecutionComponent = ObserveTarget->FindComponentByClass<UPowerExecutionComponent>();
		if (::IsValid(ObserveTargetExecutionComponent) == true)
		{
			if (ObserveTargetExecutionComponent->GetPowerState() == true)
			{
				for (int i = 0; i < MovableTargets.Num(); i = i + 1)
				{
					MovableTargets[i]->AddActorWorldOffset((::IsValid(ArrowComponent.Get()) == true ? Cast<USceneComponent>(ArrowComponent) : Cast<USceneComponent>(this))->GetForwardVector() * (ActingSpeed * DeltaTime));
				}

				//TArray<AActor*> OverlappingActors;
				//Trigger->GetOverlappingActors(OverlappingActors);
				//for (int i = 0; i < OverlappingActors.Num(); i = i + 1)
				//{
				//	if (OverlappingActors[i]->GetRootComponent()->Mobility == EComponentMobility::Movable)
				//	{
				//		//UE_LOG(LogTemp, Warning, TEXT("오이오이"));
				//
				//		//UPrimitiveComponent* OverlapActorsPrimitive = Cast<UPrimitiveComponent>(OverlappingActors[i]->GetRootComponent());
				//		//if (OverlapActorsPrimitive->IsSimulatingPhysics() == true)
				//		//{
				//			//OverlapActorsPrimitive->GetBodyInstance()->bLockRotation = true;
				//			//OverlapActorsPrimitive->SetPhysicsLinearVelocity(GetOwner()->GetActorForwardVector() * (ActingSpeed * DeltaTime), true);
				//			//OverlapActorsPrimitive->SetPhysicsLinearVelocity(ArrowComponent->GetForwardVector( * (ActingSpeed * DeltaTime), true);
				//			//OverlapActorsPrimitive->GetBodyInstance()->bLockRotation = false;
				//		//}
				//		//else
				//		//{
				//			//OverlappingActors[i]->AddActorWorldOffset(GetOwner()->GetActorForwardVector() * (ActingSpeed * DeltaTime));
				//			OverlappingActors[i]->AddActorWorldOffset(ArrowComponent->GetForwardVector() * (ActingSpeed * DeltaTime));
				//
				//		//}
				//	}
				//}
#pragma region UnUsed
				//Collider->AddWorldOffset(GetOwner()->GetActorForwardVector() * (ActingSpeed * DeltaTime));
				////UE_LOG(LogTemp, Warning, TEXT("(%f, %f, %f) %f"), Collider->GetRelativeLocation().X, Collider->GetRelativeLocation().Y, Collider->GetRelativeLocation().Z, Collider->GetRelativeLocation().Size());
				//if (Collider->GetRelativeLocation().Size() > 25.0f)
				//{
				//	Collider->SetRelativeLocation(FVector(-25.0f, 0.0f, 0.0f));
				//}

//#if ENABLE_DRAW_DEBUG
//				DrawDebugBox(GetWorld(), Collider->GetComponentLocation(), FVector(55.0f * GetOwner()->GetRootComponent()->GetRelativeScale3D().X / 2, 55.0f * GetOwner()->GetRootComponent()->GetRelativeScale3D().Y, 55.0f * GetOwner()->GetRootComponent()->GetRelativeScale3D().Z), FQuat(GetOwner()->GetActorRotation()), FColor::Red, false, 0.01f);
//#endif

				//for (int i = 0; i < MovableTargets.Num(); i = i + 1)
				//{
				//	UMovementRegistComponent* MovementRegistComponent = MovableTargets[i]->FindComponentByClass<UMovementRegistComponent>();
				//	if (MovementRegistComponent != nullptr)
				//	{
				//		if (MovementRegistComponent->MovementComponents[0] == this)
				//		{
				//			AActor* MovableTarget = MovableTargets[i];
				//			FVector MovementVector = GetOwner()->GetActorForwardVector() * (ActingSpeed * DeltaTime);
				//			FVector OriginPosition = MovableTarget->GetActorLocation();
				//			MovableTarget->AddActorWorldOffset(MovementVector);
				//			//
				//			//if ((OriginPosition - MovableTarget->GetActorLocation()).Size() < 0.1f)
				//			//{
				//			//	MovableTarget->AddActorWorldOffset(MovementVector / 2);
				//			//}
				//
				//			//UPrimitiveComponent* OwnerRootComponent = Cast<UPrimitiveComponent>(MovableTarget->GetRootComponent());
				//			//if (::IsValid(OwnerRootComponent) == true)
				//			//{
				//			//	//UE_LOG(LogTemp, Warning, TEXT("(%f, %f, %f)"), GetForwardVector().X, GetForwardVector().Y, GetForwardVector().Z);
				//			//	//OwnerRootComponent->AddForce(GetForwardVector() * (ActingSpeed * DeltaTime * OwnerRootComponent->GetMass()));
				//			//
				//			//	FVector Center = FVector((MovableTarget->GetActorLocation() + GetOwner()->GetActorLocation()) / 2);
				//			//	Center = Center + GetForwardVector();
				//			//	OwnerRootComponent->AddForceAtLocation(GetForwardVector() * (5000 * ActingSpeed * DeltaTime * OwnerRootComponent->GetMass()), Center);
				//			//	//OwnerRootComponent->SetPhysicsLinearVelocity(GetForwardVector() * (ActingSpeed * DeltaTime), true);
				//			//	//if (MovableTarget->GetVelocity().Size() < 0.01f)
				//			//	//{
				//			//	//	MovableTarget->AddActorWorldOffset(MovementVector / 2);
				//			//	//}
				//			//}
				//		}
				//	}
				//}
#pragma endregion
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{
			}
		}
	}
}

//void UPowerConveyorMovementComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//	
//}

void UPowerConveyorMovementComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() != OtherActor)
	{
		if (OtherActor->GetRootComponent()->Mobility == EComponentMobility::Movable)
		{
			MovableTargets.AddUnique(OtherActor);
		}
	}

#pragma region UnUsed
	//UE_LOG(LogTemp, Warning, TEXT("오이오이 마지카요 넷또 오소스기다제"));
	//if (GetOwner() != OtherActor)
	//{
	//	UPrimitiveComponent* CollisionTargetRootComponent = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
	//	if (::IsValid(CollisionTargetRootComponent) == true)
	//	{
	//		if (CollisionTargetRootComponent->IsSimulatingPhysics() == true)
	//		{
	//			int Count_0 = 0;
	//			for (int i = 0; i < MovableTargets.Num(); i = i + 1)
	//			{
	//				if (MovableTargets[i] == OtherActor)
	//				{
	//					Count_0 = Count_0 + 1;
	//					break;
	//				}
	//			}
	//			if (Count_0 < 1)
	//			{
	//				MovableTargets.Add(OtherActor);
	//
	//				UMovementRegistComponent* MovementRegistComponent = OtherActor->FindComponentByClass<UMovementRegistComponent>();
	//				if (MovementRegistComponent == nullptr)
	//				{
	//					MovementRegistComponent = NewObject<UMovementRegistComponent>(OtherActor, UMovementRegistComponent::StaticClass());
	//					MovementRegistComponent->RegisterComponent();
	//				}
	//
	//				int Count_1 = 0;
	//				for (int j = 0; j < MovementRegistComponent->MovementComponents.Num(); j = j + 1)
	//				{
	//					if (MovementRegistComponent->MovementComponents[j] == this)
	//					{
	//						Count_1 = Count_1 + 1;
	//						break;
	//					}
	//				}
	//				if (Count_1 < 1)
	//				{
	//					MovementRegistComponent->MovementComponents.Add(this);
	//				}
	//			}
	//		}
	//	}
	//}
#pragma endregion
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
#pragma region UnUsed
	//if (GetOwner() != OtherActor)
	//{
	//	for (int i = 0; i < MovableTargets.Num(); i = i + 1)
	//	{
	//		if (MovableTargets[i] == OtherActor)
	//		{
	//			UMovementRegistComponent* MovementRegistComponent = MovableTargets[i]->FindComponentByClass<UMovementRegistComponent>();
	//			if (MovementRegistComponent != nullptr)
	//			{
	//				for (int j = 0; j < MovementRegistComponent->MovementComponents.Num(); j = j + 1)
	//				{
	//					if (MovementRegistComponent->MovementComponents[j] == this)
	//					{
	//						MovementRegistComponent->MovementComponents.RemoveAt(j);
	//						break;
	//					}
	//				}
	//			}
	//
	//			if (MovementRegistComponent->MovementComponents.Num() < 1)
	//			{
	//				MovementRegistComponent->UnregisterComponent();
	//				MovementRegistComponent->DestroyComponent();
	//			}
	//
	//			MovableTargets.RemoveAt(i);
	//			break;
	//		}
	//	}
	//}
#pragma endregion
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerConveyorMovementComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "GameFramework/MovementComponent.h"
#include "DrawDebugHelpers.h"
#define LOCTEXT_NAMESPACE "MovementComponent"
DEFINE_LOG_CATEGORY_STATIC(LogMovement, Log, All);

UPowerConveyorMovementComponent::UPowerConveyorMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//PrimaryComponentTick.TickGroup = TG_PrePhysics;
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
	MoveComponentFlags = EMoveComponentFlags::MOVECOMP_NoFlags;


	//Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(this);
	Trigger->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
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
		//Trigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerConveyorMovementComponent::OnOverlapBegin);
		//Trigger->OnComponentEndOverlap.AddDynamic(this, &UPowerConveyorMovementComponent::OnOverlapEnd);

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
	TArray<USceneComponent*> ParentsComponents = GetAttachParent()->GetAttachChildren();
	for (int i = 0; i < ParentsComponents.Num(); i = i + 1)
	{
		UArrowComponent* Arrow = Cast<UArrowComponent>(ParentsComponents[i]);
		if (::IsValid(Arrow) == true)
		{
			ArrowComponent = Arrow;
			ArrowComponent->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform);
			break;
		}
	}

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
	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			TArray<AActor*> OverlappingActors;
			Trigger->GetOverlappingActors(OverlappingActors);
			for (int i = 0; i < OverlappingActors.Num(); i = i + 1)
			{
				AActor* OverlapTarget = OverlappingActors[i];
				if (OverlapTarget->GetRootComponent()->Mobility == EComponentMobility::Movable)
				{
					USceneComponent* DirectionComponent = ::IsValid(ArrowComponent.Get()) == true ? Cast<USceneComponent>(ArrowComponent) : Cast<USceneComponent>(this);
					FVector OriginPoint = DirectionComponent->GetComponentLocation();
					FVector MoveDirection = DirectionComponent->GetForwardVector();
					FVector GravitationDirection = ((OriginPoint - (MoveDirection * FVector::DotProduct(OriginPoint - OverlapTarget->GetActorLocation(), MoveDirection))) - OverlapTarget->GetActorLocation()).GetSafeNormal();
					if (true) { GravitationDirection = (DirectionComponent->GetRightVector() * FVector::DotProduct(DirectionComponent->GetRightVector(), GravitationDirection)).GetSafeNormal(); }

					UPrimitiveComponent* TargetRoot = Cast<UPrimitiveComponent>(OverlapTarget->GetRootComponent());
					if (::IsValid(TargetRoot) == true && PhysicsMovement == true)
					{
						if (TargetRoot->IsSimulatingPhysics() == true)
						{
							TargetRoot->SetPhysicsLinearVelocity((MoveDirection + GravitationDirection) * (ActingSpeed * DeltaTime), true);
						}
					}
					else if (::IsValid(TargetRoot) == false || PhysicsMovement == false)
					{
						FVector Velocity = (MoveDirection + GravitationDirection) * ActingSpeed;
						UpdateTargetMovement(OverlapTarget->GetRootComponent(), Velocity, DeltaTime);
						if (TargetRoot->IsSimulatingPhysics() == true)
						{
							if (::IsValid(TargetRoot) == true) { TargetRoot->SetPhysicsLinearVelocity(FVector::ZeroVector); }
						}

						//OverlapTarget->AddActorWorldOffset(FVector(0.0f, 0.0f, -UPhysicsSettings::Get()->DefaultGravityZ / 16) * DeltaTime, true);
						//OverlapTarget->AddActorWorldOffset(MoveDirection * (ActingSpeed * DeltaTime));
						//OverlapTarget->AddActorWorldOffset((GravitationDirection - OverlapTarget->GetActorLocation()) * DeltaTime, true);
					}

				}
			}

#pragma region UnUsed
			//for (int i = 0; i < MovableTargets.Num(); i = i + 1)
			//{
			//	AActor* MovableTarget = MovableTargets[i];
			//	MovableTarget->AddActorWorldOffset((::IsValid(ArrowComponent.Get()) == true ? Cast<USceneComponent>(ArrowComponent) : Cast<USceneComponent>(this))->GetForwardVector() * (ActingSpeed * DeltaTime));
			//	UPrimitiveComponent* TargetRoot = Cast<UPrimitiveComponent>(MovableTarget->GetRootComponent());
			//	if (::IsValid(TargetRoot) == true)
			//	{
			//		TargetRoot->SetPhysicsLinearVelocity(FVector::ZeroVector, true);
			//	}
			//}

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

#pragma region UnUsed
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
#pragma endregion

#pragma region Movement
void UPowerConveyorMovementComponent::UpdateTargetMovement(USceneComponent* UpdatedComponent, FVector& Velocity, const float DeltaTime)
{
	FVector Delta = Velocity * DeltaTime;
	if (Delta.IsNearlyZero(1e-6f) == false)
	{
		const FVector OldLocation = UpdatedComponent->GetComponentLocation();
		const FQuat Rotation = UpdatedComponent->GetComponentQuat();

		FHitResult Hit(1.0f);
		SafeMoveUpdatedComponent(UpdatedComponent, Delta, Rotation, true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			//HandleImpact(Hit, DeltaTime, Delta);
			// Try to slide the remaining distance along the surface.
			SlideAlongSurface(UpdatedComponent, Delta, 1.0f - Hit.Time, Hit.Normal, Hit, true);
		}

		// Update velocity
		// We don't want position changes to vastly reverse our direction (which can happen due to penetration fixups etc)
		if (true)
		{
			const FVector NewLocation = UpdatedComponent->GetComponentLocation();
			Velocity = ((NewLocation - OldLocation) / DeltaTime);
		}
	}

	// Finalize
	UpdatedComponent->ComponentVelocity = Velocity;
}

namespace MovementComponentCVars
{
	// Typically we want to depenetrate regardless of direction, so we can get all the way out of penetration quickly.
	// Our rules for "moving with depenetration normal" only get us so far out of the object. We'd prefer to pop out by the full MTD amount.
	// Depenetration moves (in ResolvePenetration) then ignore blocking overlaps to be able to move out by the MTD amount.
	int32 MoveIgnoreFirstBlockingOverlap = 0;
	static FAutoConsoleVariableRef CVarMoveIgnoreFirstBlockingOverlap(
		TEXT("p.MoveIgnoreFirstBlockingOverlap"),
		MoveIgnoreFirstBlockingOverlap,
		TEXT("Whether to ignore the first blocking overlap in SafeMoveUpdatedComponent (if moving out from object and starting in penetration).\n")
		TEXT("The 'p.InitialOverlapTolerance' setting determines the 'move out' rules, but by default we always try to depenetrate first (not ignore the hit).\n")
		TEXT("0: Disable (do not ignore), 1: Enable (ignore)"),
		ECVF_Default);
}

namespace MovementComponentCVars
{
	float PenetrationPullbackDistance = 0.125f;
	static FAutoConsoleVariableRef CVarPenetrationPullbackDistance(TEXT("p.PenetrationPullbackDistance"),
		PenetrationPullbackDistance,
		TEXT("Pull out from penetration of an object by this extra distance.\n")
		TEXT("Distance added to penetration fix-ups."),
		ECVF_Default);

	float PenetrationOverlapCheckInflation = 0.100f;
	static FAutoConsoleVariableRef CVarPenetrationOverlapCheckInflation(TEXT("p.PenetrationOverlapCheckInflation"),
		PenetrationOverlapCheckInflation,
		TEXT("Inflation added to object when checking if a location is free of blocking collision.\n")
		TEXT("Distance added to inflation in penetration overlap check."),
		ECVF_Default);
}

//void UPowerConveyorMovementComponent::HandleImpact(const FHitResult& Hit, float TimeSlice, const FVector& MoveDelta)
//{
//
//}

//FVector UPowerConveyorMovementComponent::ConstrainNormalToPlane(FVector Normal) const
//{
//	//if (false)
//	//{
//	//	Normal = FVector::VectorPlaneProject(Normal, FVector::UpVector).GetSafeNormal();
//	//}
//
//	return Normal;
//}

FVector UPowerConveyorMovementComponent::ComputeSlideVector(const FVector& Delta, const float Time, const FVector& Normal, const FHitResult& Hit) const
{
	//if (false)
	//{
	//	return FVector::VectorPlaneProject(Delta, Normal) * Time;
	//}
	//else
	//{
		//const FVector ProjectedNormal = ConstrainNormalToPlane(Normal);
	const FVector ProjectedNormal = Normal;
	return FVector::VectorPlaneProject(Delta, ProjectedNormal) * Time;
	//}
}

void UPowerConveyorMovementComponent::TwoWallAdjust(FVector& OutDelta, const FHitResult& Hit, const FVector& OldHitNormal) const
{
	FVector Delta = OutDelta;
	const FVector HitNormal = Hit.Normal;

	if ((OldHitNormal | HitNormal) <= 0.0f) //90 or less corner, so use cross product for direction
	{
		const FVector DesiredDir = Delta;
		FVector NewDir = (HitNormal ^ OldHitNormal);
		NewDir = NewDir.GetSafeNormal();
		Delta = (Delta | NewDir) * (1.0f - Hit.Time) * NewDir;
		if ((DesiredDir | Delta) < 0.0f)
		{
			Delta = -1.0f * Delta;
		}
	}
	else //adjust to new wall
	{
		const FVector DesiredDir = Delta;
		Delta = ComputeSlideVector(Delta, 1.0f - Hit.Time, HitNormal, Hit);
		if ((Delta | DesiredDir) <= 0.0f)
		{
			Delta = FVector::ZeroVector;
		}
		else if (FMath::Abs((HitNormal | OldHitNormal) - 1.0f) < KINDA_SMALL_NUMBER)
		{
			// we hit the same wall again even after adjusting to move along it the first time
			// nudge away from it (this can happen due to precision issues)
			Delta += HitNormal * 0.01f;
		}
	}

	OutDelta = Delta;
}

float UPowerConveyorMovementComponent::SlideAlongSurface(USceneComponent* UpdatedComponent, const FVector& Delta, float Time, const FVector& Normal, FHitResult& Hit, bool bHandleImpact)
{
	if (!Hit.bBlockingHit)
	{
		return 0.0f;
	}

	float PercentTimeApplied = 0.0f;
	const FVector OldHitNormal = Normal;

	FVector SlideDelta = ComputeSlideVector(Delta, Time, Normal, Hit);

	if ((SlideDelta | Delta) > 0.0f)
	{
		const FQuat Rotation = UpdatedComponent->GetComponentQuat();
		SafeMoveUpdatedComponent(UpdatedComponent, SlideDelta, Rotation, true, Hit);

		const float FirstHitPercent = Hit.Time;
		PercentTimeApplied = FirstHitPercent;
		if (Hit.IsValidBlockingHit())
		{
			// Notify first impact
			//if (bHandleImpact)
			//{
			//	HandleImpact(Hit, FirstHitPercent * Time, SlideDelta);
			//}

			// Compute new slide normal when hitting multiple surfaces.
			TwoWallAdjust(SlideDelta, Hit, OldHitNormal);

			// Only proceed if the new direction is of significant length and not in reverse of original attempted move.
			if (!SlideDelta.IsNearlyZero(1e-3f) && (SlideDelta | Delta) > 0.0f)
			{
				// Perform second move
				SafeMoveUpdatedComponent(UpdatedComponent, SlideDelta, Rotation, true, Hit);
				const float SecondHitPercent = Hit.Time * (1.0f - FirstHitPercent);
				PercentTimeApplied += SecondHitPercent;

				// Notify second impact
				//if (bHandleImpact && Hit.bBlockingHit)
				//{
				//	HandleImpact(Hit, SecondHitPercent * Time, SlideDelta);
				//}
			}
		}

		return FMath::Clamp(PercentTimeApplied, 0.0f, 1.0f);
	}

	return 0.0f;
}

//FVector UPowerConveyorMovementComponent::ConstrainDirectionToPlane(FVector Direction) const
//{
//	//if (false)
//	//{
//	//	Direction = FVector::VectorPlaneProject(Direction, FVector::UpVector);
//	//}
//
//	return Direction;
//}

//bool UPowerConveyorMovementComponent::MoveUpdatedComponentImpl(USceneComponent* UpdatedComponent, const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport)
//{
//	if (UpdatedComponent)
//	{
//		//const FVector NewDelta = ConstrainDirectionToPlane(Delta);
//		const FVector NewDelta = Delta;
//		return UpdatedComponent->MoveComponent(NewDelta, NewRotation, bSweep, OutHit, MoveComponentFlags, Teleport);
//	}
//	
//	return false;
//}

FORCEINLINE_DEBUGGABLE bool UPowerConveyorMovementComponent::MoveUpdatedComponent(USceneComponent* UpdatedComponent, const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport)
{
	//return MoveUpdatedComponentImpl(UpdatedComponent, Delta, NewRotation, bSweep, OutHit, Teleport);
	if (UpdatedComponent)
	{
		//const FVector NewDelta = ConstrainDirectionToPlane(Delta);
		const FVector NewDelta = Delta;
		return UpdatedComponent->MoveComponent(NewDelta, NewRotation, bSweep, OutHit, MoveComponentFlags, Teleport);
	}

	return false;
}

//FORCEINLINE_DEBUGGABLE bool UPowerConveyorMovementComponent::MoveUpdatedComponent(USceneComponent* UpdatedComponent, const FVector& Delta, const FRotator& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport)
//{
//	return MoveUpdatedComponentImpl(UpdatedComponent, Delta, NewRotation.Quaternion(), bSweep, OutHit, Teleport);
//}

FVector UPowerConveyorMovementComponent::GetPenetrationAdjustment(const FHitResult& Hit) const
{
	if (!Hit.bStartPenetrating)
	{
		return FVector::ZeroVector;
	}

	FVector Result;
	const float PullBackDistance = FMath::Abs(MovementComponentCVars::PenetrationPullbackDistance);
	const float PenetrationDepth = (Hit.PenetrationDepth > 0.0f ? Hit.PenetrationDepth : 0.125f);

	Result = Hit.Normal * (PenetrationDepth + PullBackDistance);

	//return ConstrainDirectionToPlane(Result);
	return Result;
}

void UPowerConveyorMovementComponent::InitCollisionParams(USceneComponent* UpdatedComponent, FCollisionQueryParams& OutParams, FCollisionResponseParams& OutResponseParam) const
{
	UPrimitiveComponent* UpdatedPrimitive = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (UpdatedPrimitive)
	{
		UpdatedPrimitive->InitSweepCollisionParams(OutParams, OutResponseParam);
	}
}

bool UPowerConveyorMovementComponent::OverlapTest(USceneComponent* UpdatedComponent, const FVector& Location, const FQuat& RotationQuat, const ECollisionChannel CollisionChannel, const FCollisionShape& CollisionShape, const AActor* IgnoreActor) const
{
	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(MovementOverlapTest), false, IgnoreActor);
	FCollisionResponseParams ResponseParam;
	InitCollisionParams(UpdatedComponent, QueryParams, ResponseParam);
	return GetWorld()->OverlapBlockingTestByChannel(Location, RotationQuat, CollisionChannel, CollisionShape, QueryParams, ResponseParam);
}

bool UPowerConveyorMovementComponent::ResolvePenetrationImpl(USceneComponent* UpdatedComponent, const FVector& ProposedAdjustment, const FHitResult& Hit, const FQuat& NewRotationQuat)
{
	// SceneComponent can't be in penetration, so this function really only applies to PrimitiveComponent.
	//const FVector Adjustment = ConstrainDirectionToPlane(ProposedAdjustment);
	const FVector Adjustment = ProposedAdjustment;
	UPrimitiveComponent* UpdatedPrimitive = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (!Adjustment.IsZero() && ::IsValid(UpdatedPrimitive) == true)
	{
		QUICK_SCOPE_CYCLE_COUNTER(STAT_MovementComponent_ResolvePenetration);
		// See if we can fit at the adjusted location without overlapping anything.
		AActor* ActorOwner = UpdatedComponent->GetOwner();
		if (::IsValid(ActorOwner) == false)
		{
			return false;
		}

		UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration: %s.%s at location %s inside %s.%s at location %s by %.3f (netmode: %d)"),
			*ActorOwner->GetName(),
			*UpdatedComponent->GetName(),
			*UpdatedComponent->GetComponentLocation().ToString(),
			*GetNameSafe(Hit.GetActor()),
			*GetNameSafe(Hit.GetComponent()),
			Hit.Component.IsValid() ? *Hit.GetComponent()->GetComponentLocation().ToString() : TEXT("<unknown>"),
			Hit.PenetrationDepth,
			(uint32)GetNetMode());

		// We really want to make sure that precision differences or differences between the overlap test and sweep tests don't put us into another overlap,
		// so make the overlap test a bit more restrictive.
		const float OverlapInflation = MovementComponentCVars::PenetrationOverlapCheckInflation;
		bool bEncroached = OverlapTest(UpdatedComponent, Hit.TraceStart + Adjustment, NewRotationQuat, UpdatedPrimitive->GetCollisionObjectType(), UpdatedPrimitive->GetCollisionShape(OverlapInflation), ActorOwner);
		if (bEncroached == false)
		{
			// Move without sweeping.
			MoveUpdatedComponent(UpdatedComponent, Adjustment, NewRotationQuat, false, nullptr, ETeleportType::TeleportPhysics);
			UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   teleport by %s"), *Adjustment.ToString());
			return true;
		}
		else
		{
			// Disable MOVECOMP_NeverIgnoreBlockingOverlaps if it is enabled, otherwise we wouldn't be able to sweep out of the object to fix the penetration.
			TGuardValue<EMoveComponentFlags> ScopedFlagRestore(MoveComponentFlags, EMoveComponentFlags(MoveComponentFlags & (~MOVECOMP_NeverIgnoreBlockingOverlaps)));

			// Try sweeping as far as possible...
			FHitResult SweepOutHit(1.0f);
			bool bMoved = MoveUpdatedComponent(UpdatedComponent, Adjustment, NewRotationQuat, true, &SweepOutHit, ETeleportType::TeleportPhysics);
			UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   sweep by %s (success = %d)"), *Adjustment.ToString(), bMoved);

			// Still stuck?
			if (bMoved == false && SweepOutHit.bStartPenetrating)
			{
				// Combine two MTD results to get a new direction that gets out of multiple surfaces.
				const FVector SecondMTD = GetPenetrationAdjustment(SweepOutHit);
				const FVector CombinedMTD = Adjustment + SecondMTD;
				if (SecondMTD != Adjustment && CombinedMTD.IsZero() == false)
				{
					bMoved = MoveUpdatedComponent(UpdatedComponent, CombinedMTD, NewRotationQuat, true, nullptr, ETeleportType::TeleportPhysics);
					UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   sweep by %s (MTD combo success = %d)"), *CombinedMTD.ToString(), bMoved);
				}
			}

			// Still stuck?
			if (bMoved == false)
			{
				// Try moving the proposed adjustment plus the attempted move direction. This can sometimes get out of penetrations with multiple objects
				//const FVector MoveDelta = ConstrainDirectionToPlane(Hit.TraceEnd - Hit.TraceStart);
				const FVector MoveDelta = Hit.TraceEnd - Hit.TraceStart;
				if (MoveDelta.IsZero() == false)
				{
					bMoved = MoveUpdatedComponent(UpdatedComponent, Adjustment + MoveDelta, NewRotationQuat, true, nullptr, ETeleportType::TeleportPhysics);
					UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   sweep by %s (adjusted attempt success = %d)"), *(Adjustment + MoveDelta).ToString(), bMoved);

					// Finally, try the original move without MTD adjustments, but allowing depenetration along the MTD normal.
					// This was blocked because MOVECOMP_NeverIgnoreBlockingOverlaps was true for the original move to try a better depenetration normal, but we might be running in to other geometry in the attempt.
					// This won't necessarily get us all the way out of penetration, but can in some cases and does make progress in exiting the penetration.
					if (!bMoved && FVector::DotProduct(MoveDelta, Adjustment) > 0.0f)
					{
						bMoved = MoveUpdatedComponent(UpdatedComponent, MoveDelta, NewRotationQuat, true, nullptr, ETeleportType::TeleportPhysics);
						UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   sweep by %s (Original move, attempt success = %d)"), *(MoveDelta).ToString(), bMoved);
					}
				}
			}

			return bMoved;
		}
	}

	return false;
}

FORCEINLINE_DEBUGGABLE bool UPowerConveyorMovementComponent::ResolvePenetration(USceneComponent* UpdatedComponent, const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotation)
{
	return ResolvePenetrationImpl(UpdatedComponent, Adjustment, Hit, NewRotation);
}

bool UPowerConveyorMovementComponent::SafeMoveUpdatedComponent(USceneComponent* UpdatedComponent, const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult& OutHit, ETeleportType Teleport)
{
	if (UpdatedComponent == NULL)
	{
		OutHit.Reset(1.0f);
		return false;
	}

	bool bMoveResult = false;

	// Scope for move flags
	{
		// Conditionally ignore blocking overlaps (based on CVar)
		const EMoveComponentFlags IncludeBlockingOverlapsWithoutEvents = (MOVECOMP_NeverIgnoreBlockingOverlaps | MOVECOMP_DisableBlockingOverlapDispatch);
		TGuardValue<EMoveComponentFlags> ScopedFlagRestore(MoveComponentFlags, MovementComponentCVars::MoveIgnoreFirstBlockingOverlap ? MoveComponentFlags : (MoveComponentFlags | IncludeBlockingOverlapsWithoutEvents));
		bMoveResult = MoveUpdatedComponent(UpdatedComponent, Delta, NewRotation, bSweep, &OutHit, Teleport);
	}

	// Handle initial penetrations
	if (OutHit.bStartPenetrating && IsValid(UpdatedComponent) == true)
	{
		const FVector RequestedAdjustment = GetPenetrationAdjustment(OutHit);
		if (ResolvePenetration(UpdatedComponent, RequestedAdjustment, OutHit, NewRotation))
		{
			// Retry original move
			bMoveResult = MoveUpdatedComponent(UpdatedComponent, Delta, NewRotation, bSweep, &OutHit, Teleport);
		}
	}

	return bMoveResult;
}
#pragma endregion
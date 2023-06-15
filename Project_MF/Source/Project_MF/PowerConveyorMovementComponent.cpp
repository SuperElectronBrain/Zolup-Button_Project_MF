// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerConveyorMovementComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "DrawDebugHelpers.h"
//#define LOCTEXT_NAMESPACE "MovementComponent"
//DEFINE_LOG_CATEGORY_STATIC(LogMovement, Log, All);

UPowerConveyorMovementComponent::UPowerConveyorMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MoveComponentFlags = EMoveComponentFlags::MOVECOMP_NoFlags;

	//Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	//Trigger->SetupAttachment(this);
	//Trigger->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
}

void UPowerConveyorMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetRelativeScale3D(FVector::OneVector);

	TArray<USceneComponent*> Components = GetAttachChildren();
	for (int i = 0; i < Components.Num(); i = i + 1)
	{
		UBoxComponent* Box = Cast<UBoxComponent>(Components[i]);
		if (::IsValid(Box) == true)
		{
			Trigger = Box;
			Trigger->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
			break;
		}
	}
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

	if (::IsValid(Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())) == true)
	{
		if (::IsValid(Trigger.Get()) == true)
		{
			Trigger->SetCollisionProfileName("OverlapAllDynamic");
			Trigger->SetGenerateOverlapEvents(true);
		}
	}

	UStaticMeshComponent* ParentStaticMeshComponent = Cast<UStaticMeshComponent>(GetAttachParent());
	//FVector ParentBounds = ParentStaticMeshComponent != nullptr ? (ParentStaticMeshComponent->GetStaticMesh() != nullptr ? ParentStaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent : FVector::OneVector * 50) : FVector::OneVector * 50;
	//Trigger->SetBoxExtent(FVector(ParentBounds.X * 1.0f, ParentBounds.Y * 1.0f, ParentBounds.Z * 1.5f));


	if (::IsValid(ParentStaticMeshComponent) == false)
	{
		if (GetOwner()->GetRootComponent() != GetAttachParent())
		{
			ParentStaticMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
		}
	}

	if (::IsValid(ParentStaticMeshComponent) == true)
	{
		UStaticMesh* ParentStaticMesh = ParentStaticMeshComponent->GetStaticMesh();
		if (::IsValid(ParentStaticMesh) == true)
		{
			UMaterialInterface* ParentMaterial = ParentStaticMeshComponent->GetMaterial(0);
			if (::IsValid(ParentMaterial) == true)
			{
				DynamicMaterial = UMaterialInstanceDynamic::Create(ParentMaterial, ParentStaticMeshComponent);
				if (::IsValid(DynamicMaterial) == true)
				{
					ParentStaticMeshComponent->SetMaterial(0, DynamicMaterial);
				}
			}
		}
	}

	if (::IsValid(DynamicMaterial) == true)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("speed"), 0);
	}
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
			if (::IsValid(DynamicMaterial) == true)
			{
				DynamicMaterial->SetScalarParameterValue(TEXT("speed"), -ActingSpeed * 0.001f);
			}

			if (::IsValid(Trigger.Get()) == true)
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
						if (true) { GravitationDirection = (DirectionComponent->GetRightVector() * FVector::DotProduct(DirectionComponent->GetRightVector(), GravitationDirection)); }//.GetSafeNormal(); }

						UPrimitiveComponent* TargetRoot = Cast<UPrimitiveComponent>(OverlapTarget->GetRootComponent());
						if (::IsValid(TargetRoot) == true && PhysicsMovement == true)
						{
							if (TargetRoot->IsSimulatingPhysics() == true)
							{
								TargetRoot->SetPhysicsLinearVelocity((MoveDirection + GravitationDirection) * (ActingSpeed * DeltaTime), true);
							}
						}
						else
						{
							bool isMoveable = true;
							UMagneticComponent* MagneticComponent = OverlapTarget->FindComponentByClass<UMagneticComponent>();
							if (::IsValid(MagneticComponent) == true)
							{
								if (MagneticComponent->GetCurrentMagnetMovementType()!=EMagnetMoveType::NONE)
								{
									UE_LOG(LogTemp, Warning, TEXT("움직이는중~~~"))
									isMoveable = false;
								}
							}

							if (isMoveable == true)
							{
								FVector Velocity = (MoveDirection + GravitationDirection) * ActingSpeed;
								UpdateTargetMovement(OverlapTarget->GetRootComponent(), Velocity, DeltaTime);
								//if (TargetRoot->GetComponentRotation() != GetAttachParent()->GetComponentRotation())
								//{
									//TargetRoot->SetWorldRotation(FMath::RInterpTo(TargetRoot->GetComponentRotation(), GetAttachParent()->GetComponentRotation(), DeltaTime, 100.0f));
								//}

								if (::IsValid(TargetRoot) == true)
								{
									TargetRoot->SetWorldRotation(FRotator::ZeroRotator);
									if (TargetRoot->IsSimulatingPhysics() == true)
									{
										if (::IsValid(TargetRoot) == true) { TargetRoot->SetPhysicsLinearVelocity(FVector::DownVector); }
									}
								}

								//OverlapTarget->AddActorWorldOffset(FVector(0.0f, 0.0f, -UPhysicsSettings::Get()->DefaultGravityZ / 16) * DeltaTime, true);
								//OverlapTarget->AddActorWorldOffset(MoveDirection * (ActingSpeed * DeltaTime));
								//OverlapTarget->AddActorWorldOffset((GravitationDirection - OverlapTarget->GetActorLocation()) * DeltaTime, true);
							}
						}
					}
				}
			}
		}
		else if (ObserveTargetExecutionComponent->GetPowerState() == false)
		{
			if (::IsValid(DynamicMaterial) == true)
			{
				DynamicMaterial->SetScalarParameterValue(TEXT("speed"), 0);
			}
		}
	}
}

void UPowerConveyorMovementComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetOwner() != OtherActor)
	{
		if (OtherActor->GetRootComponent()->Mobility == EComponentMobility::Movable)
		{
			MovableTargets.AddUnique(OtherActor);
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


FVector UPowerConveyorMovementComponent::ComputeSlideVector(const FVector& Delta, const float Time, const FVector& Normal, const FHitResult& Hit) const
{
	const FVector ProjectedNormal = Normal;
	return FVector::VectorPlaneProject(Delta, ProjectedNormal) * Time;
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
			// Compute new slide normal when hitting multiple surfaces.
			TwoWallAdjust(SlideDelta, Hit, OldHitNormal);

			// Only proceed if the new direction is of significant length and not in reverse of original attempted move.
			if (!SlideDelta.IsNearlyZero(1e-3f) && (SlideDelta | Delta) > 0.0f)
			{
				// Perform second move
				SafeMoveUpdatedComponent(UpdatedComponent, SlideDelta, Rotation, true, Hit);
				const float SecondHitPercent = Hit.Time * (1.0f - FirstHitPercent);
				PercentTimeApplied += SecondHitPercent;
			}
		}

		return FMath::Clamp(PercentTimeApplied, 0.0f, 1.0f);
	}

	return 0.0f;
}

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

FVector UPowerConveyorMovementComponent::GetPenetrationAdjustment(const FHitResult& Hit) const
{
	if (!Hit.bStartPenetrating)
	{
		return FVector::ZeroVector;
	}

	FVector Result;
	const float PullBackDistance = FMath::Abs(0.125f);
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

		// We really want to make sure that precision differences or differences between the overlap test and sweep tests don't put us into another overlap,
		// so make the overlap test a bit more restrictive.
		const float OverlapInflation = 0.100f;
		bool bEncroached = OverlapTest(UpdatedComponent, Hit.TraceStart + Adjustment, NewRotationQuat, UpdatedPrimitive->GetCollisionObjectType(), UpdatedPrimitive->GetCollisionShape(OverlapInflation), ActorOwner);
		if (bEncroached == false)
		{
			// Move without sweeping.
			MoveUpdatedComponent(UpdatedComponent, Adjustment, NewRotationQuat, false, nullptr, ETeleportType::TeleportPhysics);
			//UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   teleport by %s"), *Adjustment.ToString());
			return true;
		}
		else
		{
			// Disable MOVECOMP_NeverIgnoreBlockingOverlaps if it is enabled, otherwise we wouldn't be able to sweep out of the object to fix the penetration.
			TGuardValue<EMoveComponentFlags> ScopedFlagRestore(MoveComponentFlags, EMoveComponentFlags(MoveComponentFlags & (~MOVECOMP_NeverIgnoreBlockingOverlaps)));

			// Try sweeping as far as possible...
			FHitResult SweepOutHit(1.0f);
			bool bMoved = MoveUpdatedComponent(UpdatedComponent, Adjustment, NewRotationQuat, true, &SweepOutHit, ETeleportType::TeleportPhysics);
			//UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   sweep by %s (success = %d)"), *Adjustment.ToString(), bMoved);

			// Still stuck?
			if (bMoved == false && SweepOutHit.bStartPenetrating)
			{
				// Combine two MTD results to get a new direction that gets out of multiple surfaces.
				const FVector SecondMTD = GetPenetrationAdjustment(SweepOutHit);
				const FVector CombinedMTD = Adjustment + SecondMTD;
				if (SecondMTD != Adjustment && CombinedMTD.IsZero() == false)
				{
					bMoved = MoveUpdatedComponent(UpdatedComponent, CombinedMTD, NewRotationQuat, true, nullptr, ETeleportType::TeleportPhysics);
					///UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   sweep by %s (MTD combo success = %d)"), *CombinedMTD.ToString(), bMoved);
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
					//UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   sweep by %s (adjusted attempt success = %d)"), *(Adjustment + MoveDelta).ToString(), bMoved);

					// Finally, try the original move without MTD adjustments, but allowing depenetration along the MTD normal.
					// This was blocked because MOVECOMP_NeverIgnoreBlockingOverlaps was true for the original move to try a better depenetration normal, but we might be running in to other geometry in the attempt.
					// This won't necessarily get us all the way out of penetration, but can in some cases and does make progress in exiting the penetration.
					if (!bMoved && FVector::DotProduct(MoveDelta, Adjustment) > 0.0f)
					{
						bMoved = MoveUpdatedComponent(UpdatedComponent, MoveDelta, NewRotationQuat, true, nullptr, ETeleportType::TeleportPhysics);
						//UE_LOG(LogMovement, Verbose, TEXT("ResolvePenetration:   sweep by %s (Original move, attempt success = %d)"), *(MoveDelta).ToString(), bMoved);
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
		TGuardValue<EMoveComponentFlags> ScopedFlagRestore(MoveComponentFlags, 0 ? MoveComponentFlags : (MoveComponentFlags | IncludeBlockingOverlapsWithoutEvents));
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
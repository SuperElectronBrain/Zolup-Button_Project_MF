// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "PowerConveyorMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerConveyorMovementComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
	
private:
//#if WITH_EDITORONLY_DATA
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) UArrowComponent* ArrowComponent;
	UPROPERTY() TWeakObjectPtr<UArrowComponent> ArrowComponent;

	//#endif
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	UPROPERTY() UBoxComponent* Trigger;
	//UPROPERTY() UBoxComponent* Collider;
	UPROPERTY() TArray<AActor*> MovableTargets;
	EMoveComponentFlags MoveComponentFlags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool PhysicsMovement;

	//UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma region Movement
	//void HandleImpact(const FHitResult& Hit, float TimeSlice, const FVector& MoveDelta);
	//FVector ConstrainNormalToPlane(FVector Normal) const;
	FVector ComputeSlideVector(const FVector& Delta, const float Time, const FVector& Normal, const FHitResult& Hit) const;
	void TwoWallAdjust(FVector& OutDelta, const FHitResult& Hit, const FVector& OldHitNormal) const;
	float SlideAlongSurface(USceneComponent* UpdatedComponent, const FVector& Delta, float Time, const FVector& Normal, FHitResult& Hit, bool bHandleImpact);
	//FVector ConstrainDirectionToPlane(FVector Direction) const;
	FORCEINLINE_DEBUGGABLE bool MoveUpdatedComponent(USceneComponent* UpdatedComponent, const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport);
	//FORCEINLINE_DEBUGGABLE bool MoveUpdatedComponent(USceneComponent* UpdatedComponent, const FVector& Delta, const FRotator& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport);
	FVector GetPenetrationAdjustment(const FHitResult& Hit) const;
	void InitCollisionParams(USceneComponent* UpdatedComponent, FCollisionQueryParams& OutParams, FCollisionResponseParams& OutResponseParam) const;
	bool OverlapTest(USceneComponent* UpdatedComponent, const FVector& Location, const FQuat& RotationQuat, const ECollisionChannel CollisionChannel, const FCollisionShape& CollisionShape, const AActor* IgnoreActor) const;
	bool ResolvePenetrationImpl(USceneComponent* UpdatedComponent, const FVector& ProposedAdjustment, const FHitResult& Hit, const FQuat& NewRotationQuat);
	FORCEINLINE_DEBUGGABLE bool ResolvePenetration(USceneComponent* UpdatedComponent, const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotation);
	//bool MoveUpdatedComponentImpl(USceneComponent* UpdatedComponent, const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport = ETeleportType::None);
	bool SafeMoveUpdatedComponent(USceneComponent* UpdatedComponent, const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult& OutHit, ETeleportType Teleport = ETeleportType::None);
#pragma endregion
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() virtual void Action(float DeltaTime);


	UFUNCTION() void UpdateTargetMovement(USceneComponent* UpdatedComponent, FVector& Velocity, const float DeltaTime);

public:
	UPowerConveyorMovementComponent();

};

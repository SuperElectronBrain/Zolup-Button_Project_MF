// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "RotatingMagMovementComponent.h"

AActor* URotatingMagMovementComponent::ApplyMovement(EMagnetMoveType type, UMagneticComponent* SafeMagOperator, float DeltaTime)
{
	USceneComponent* updated = UpdatedComponent;
	UMagneticComponent* owner = GetOwnerMagnetic();
	
	float dir = (type==EMagnetMoveType::PUSHED_OUT?-1.f:1.f);
	FVector goal = (SafeMagOperator->GetComponentLocation() - owner->GetComponentLocation()) - updated->GetComponentRotation().Vector();

	FVector t1 = (SafeMagOperator->GetComponentLocation() - owner->GetComponentLocation()).GetSafeNormal();
	const FRotator rotation = updated->GetComponentRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector t2 = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	float cos = FVector::DotProduct(t1, t2);

	FRotator rot(0.f, cos*RotSpeedScale, 0.f);

	FHitResult hit;
	updated->AddWorldRotation(rot.Quaternion(), true, &hit);

	if (hit.bBlockingHit)
	{
		return hit.GetActor();
	}

	return nullptr;
}

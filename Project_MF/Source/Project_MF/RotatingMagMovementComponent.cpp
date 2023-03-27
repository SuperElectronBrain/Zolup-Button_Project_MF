// Fill out your copyright notice in the Description page of Project Settings.

#include "RotatingMagMovementComponent.h"

AActor* URotatingMagMovementComponent::ApplyMovement(EMagnetMoveType type, UMagneticComponent* SafeMagOperator, float DeltaTime)
{
	USceneComponent* updated = UpdatedComponent;
	UMagneticComponent* owner = GetOwnerMagnetic();

	FVector t1 = (SafeMagOperator->GetComponentLocation() - owner->GetComponentLocation()).GetSafeNormal();
	const FRotator rotation = updated->GetComponentRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector t2 = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	float cos = FVector::DotProduct(t1, t2);

	FRotator rot(0.f, -cos * RotSpeed, 0.f);

	FHitResult hit;

	SafeMoveUpdatedComponent(FVector::ZeroVector, rot + rotation, true, hit);
	if (hit.bBlockingHit)
	{
		return hit.GetActor();
	}

	return nullptr;
}

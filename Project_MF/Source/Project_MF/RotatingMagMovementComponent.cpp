// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "RotatingMagMovementComponent.h"

AActor* URotatingMagMovementComponent::ApplyMovement(EMagnetMoveType type, UMagneticComponent* SafeMagOperator, float DeltaTime)
{
	USceneComponent* updated = UpdatedComponent;
	UMagneticComponent* owner = GetOwnerMagnetic();
	
	FVector dir = (SafeMagOperator->GetComponentLocation() - owner->GetComponentLocation()) * (type==EMagnetMoveType::PUSHED_OUT?-1.f:1.f);
	FRotator rot(0.f, FMath::Atan2(dir.Y, dir.X)*RotSpeedScale, 0.f);

	updated->AddWorldRotation(rot.Quaternion());

	//FHitResult hit;
	//SafeMoveUpdatedComponent(FVector::ZeroVector, rot, true, hit);

	//if (hit.IsValidBlockingHit() && hit.GetActor()!=nullptr && ::IsValid(hit.GetActor()))
	//{
	//	return hit.GetActor();
	//}

	return nullptr;
}

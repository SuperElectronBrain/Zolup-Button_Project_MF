// Fill out your copyright notice in the Description page of Project Settings.

#include "RotatingMagMovementComponent.h"
#include "DrawDebugHelpers.h"

AActor* URotatingMagMovementComponent::ApplyMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* SafeMagOperator, float DeltaTime)
{
	USceneComponent* updated = UpdatedComponent;

	//계산에 필요한 것들을 구한다.
	const FRotator rotation = updated->GetComponentRotation();
	const FVector magDir = (owner->GetComponentLocation()-updated->GetComponentLocation()).GetSafeNormal();
	const FVector goalDir = (SafeMagOperator->GetComponentLocation() - updated->GetComponentLocation()).GetSafeNormal();
	const FVector t1(magDir.X, magDir.Y, 0.f);
	 FVector t2(goalDir.X, goalDir.Y, 0.f);

	//움직임 상태에 따른 적용
	t2 *= type == EMagnetMoveType::PUSHED_OUT ? -1.f : 1.f;

	float cos = FMath::Acos(FVector::DotProduct(t1.GetSafeNormal(), t2.GetSafeNormal()));
	FVector cross = FVector::CrossProduct(t1, t2);

	//UE_LOG(LogTemp, Warning, TEXT("cos: %f"), FMath::RadiansToDegrees(FMath::Acos(cos)))

	//DrawDebugLine(GetWorld(), updated->GetComponentLocation(), updated->GetComponentLocation() + goalDir * 1000.f, FColor::Red, false, 0.1f, 0U, 3.f);
	//DrawDebugLine(GetWorld(), updated->GetComponentLocation(), updated->GetComponentLocation() + magDir * 1000.f, FColor::Blue, false, 0.1f, 0U, 3.f);

	//최종 계산 및 적용.
	float rotDir = cross.Z >= 0 ? 1.f : -1.f;
	FRotator rot = FRotator::MakeFromEuler(FVector(0.f, 0.f, FMath::Abs(cos) * rotDir * RotSpeed));
	FHitResult hit;
	SafeMoveUpdatedComponent(FVector::ZeroVector, rot + rotation, true, hit);
	if (hit.bBlockingHit)
	{
		return hit.GetActor();
	}

	return nullptr;
}

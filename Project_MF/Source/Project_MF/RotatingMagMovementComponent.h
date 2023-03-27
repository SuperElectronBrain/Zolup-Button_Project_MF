// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "MagneticMovementComponent.h"
#include "RotatingMagMovementComponent.generated.h"

UCLASS(ClassGroup = (Megnetic), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API URotatingMagMovementComponent final : public UMagneticMovementComponent
{
	GENERATED_BODY()

private:
	/*Override methods*/
	virtual AActor* ApplyMovement(EMagnetMoveType type, UMagneticComponent* SafeMagOperator, float DeltaTime) override;

	/*fields And Components*/
	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true, ClampMin = 0.f))
	float RotSpeed = 5.f;
	
};

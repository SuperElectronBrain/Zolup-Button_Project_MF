// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagneticMovementComponent.h"
#include "DefaultMagneticMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Megnetic), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UDefaultMagneticMovementComponent final : public UMagneticMovementComponent
{
	GENERATED_BODY()

public:
	UDefaultMagneticMovementComponent();

private:
	/*Override methods*/
	virtual AActor* ApplyMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* SafeMagOperator, float DeltaTime) override;

	/*fields and Components*/
	FHitResult hit;
	float _power;
	FVector PrevDir;
	float _operatorRadiusDiv;
	float _operatorRadiusHalfDiv;
	float _prevOperatorRadius;
	bool _originUsedGravity;

public:
	UPROPERTY(EditAnywhere, Category = Magnetic)
	EMagnetMoveAxisType MoveType = EMagnetMoveAxisType::MOVE_XYZ;
};

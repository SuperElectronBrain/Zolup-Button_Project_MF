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
	virtual void StartMovement(EMagnetMoveType moveType, UMagneticComponent* owner, UMagneticComponent* magOperator) override;

	/*Private methods*/
	UFUNCTION()
	void ShakeProcess();

	/*fields and Components*/
	FHitResult hit;
	float _power;
	FVector PrevDir;
	float _operatorRadiusDiv;
	float _operatorRadiusHalfDiv;
	float _prevOperatorRadius;
	float _distance, _currTime, _goalTimeDiv, _distanceDiv, _shakePow;
	FVector _startPos, _moveDir, _shakeDir;
	bool _originUsedGravity, _registerHit;

public:
	UPROPERTY(EditAnywhere, Category = Magnetic)
	EMagnetMoveAxisType MoveType = EMagnetMoveAxisType::MOVE_XYZ;
};

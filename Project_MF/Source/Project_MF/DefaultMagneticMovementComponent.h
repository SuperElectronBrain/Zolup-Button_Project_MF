// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagneticMovementComponent.h"
#include "DefaultMagneticMovementComponent.generated.h"

class UMagneticComponent;

/*이 컴포넌트가 붙여있는 엑터에 부착되어있는 UMagneticComponent가 사용할 자석의 움직임이 정의된 컴포넌트 입니다.
 *기본적인 자석의 밀림/당겨짐의 움직임이 정의되어있습니다.
 */
UCLASS(ClassGroup = (MegneticMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UDefaultMagneticMovementComponent final : public UMagneticMovementComponent
{
	GENERATED_BODY()

public:
	UDefaultMagneticMovementComponent();

private:
	///////////////////////
	///*Override methods*//
	//////////////////////
	virtual void ApplyMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* SafeMagOperator, float DeltaTime, FHitResult& HitResult) override;
	virtual void StartMovement(EMagnetMoveType moveType, UMagneticComponent* owner, UMagneticComponent* magOperator) override;
	virtual void EndMovement(EMagnetMoveType endType, UMagneticComponent* owner) override;

	///////////////////////
	///*Private methods*///
	//////////////////////

	/////////////////////////////
	///*fields and Components*///
	////////////////////////////
	FHitResult hit;
	float _power;
	FVector PrevDir;
	float _operatorRadiusDiv;
	float _operatorRadiusHalfDiv;
	float _prevOperatorRadius;
	float _distance, _currTime, _goalTimeDiv, _distanceDiv, _shakePow;
	FVector _startPos, _moveDir, _shakeDir;
	bool _originUsedGravity, _registerHit;

	FVector start, middle, end;

public:
	UPROPERTY(EditAnywhere, Category = Magnetic)
	EMagnetMoveAxisType MoveType = EMagnetMoveAxisType::MOVE_XYZ;
};

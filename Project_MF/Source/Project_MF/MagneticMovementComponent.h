#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "MagneticMovementComponent.generated.h"

class UMagneticComponent;

UENUM()
enum class EMagnetMoveType : uint8
{
	NONE,
	PUSHED_OUT,
	DRAWN_IN
};

UENUM()
enum class EMagnetMoveAxisType : uint8
{
	NONE,
	MOVE_ONLY_XY,
	MOVE_ONLY_Z,
	MOVE_XYZ
};

UCLASS(abstract)
class PROJECT_MF_API UMagneticMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	//////////////////////
	/////*Construtor*/////
	/////////////////////
	UMagneticMovementComponent();

	////////////////////////
	/////*Public method*////
	///////////////////////
	virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent) override;
	void ApplyUpdatedComponentMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* magOperator, float DeltaTime, FHitResult& HitResult);
	virtual void StartMovement(EMagnetMoveType startType, UMagneticComponent* owner, UMagneticComponent* magOperator) {}
	virtual void EndMovement(EMagnetMoveType endType, UMagneticComponent* owner) {}

protected:
	UFUNCTION()
	virtual void ApplyMovement(EMagnetMoveType type, UMagneticComponent* safeOwner, UMagneticComponent* safeMagOperator, float DeltaTime, FHitResult& HitResult) PURE_VIRTUAL(UMagneticMovementComponent::ApplyMovement);
	UMagneticComponent* GetOwnerMagnetic() const;
	bool UpdatedPrimitiveIsValid() const { return UpdatedPrimitive && ::IsValid(UpdatedPrimitive) && UpdatedPrimitive->IsSimulatingPhysics(); }

private:
	//////////////////////////////
	/////*Fields And Components*//
	/////////////////////////////
	UMagneticComponent* _MagOwner;
};
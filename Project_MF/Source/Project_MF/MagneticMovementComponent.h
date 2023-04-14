#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "MagneticComponent.h"
#include "MagneticMovementComponent.generated.h"

UENUM()
enum class EMagnetMoveType
{
	NONE,
	PUSHED_OUT,
	DRAWN_IN
};

UENUM()
enum class EMagnetMoveAxisType
{
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
	AActor* ApplyUpdatedComponentMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* magOperator, float DeltaTime);
	virtual void StartMovement(EMagnetMoveType startType, UMagneticComponent* owner, UMagneticComponent* magOperator) {}
	virtual void EndMovement(EMagnetMoveType endType, UMagneticComponent* owner) {}

protected:
	UFUNCTION()
	virtual AActor* ApplyMovement(EMagnetMoveType type, UMagneticComponent* safeOwner, UMagneticComponent* safeMagOperator, float DeltaTime) PURE_VIRTUAL(UMagneticMovementComponent::ApplyMovement, return false;);
	UMagneticComponent* GetOwnerMagnetic() const;
	bool UpdatedPrimitiveIsValid() const { return UpdatedPrimitive && ::IsValid(UpdatedPrimitive) && UpdatedPrimitive->IsSimulatingPhysics(); }

private:
	//////////////////////////////
	/////*Fields And Components*//
	/////////////////////////////
	UMagneticComponent* _MagOwner;
};
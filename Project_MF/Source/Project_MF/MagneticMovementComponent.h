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

UCLASS(abstract)
class PROJECT_MF_API UMagneticMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	/*Construtor*/
	UMagneticMovementComponent();

	/*Public method*/
	virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent) override;
	AActor* ApplyUpdatedComponentMovement(EMagnetMoveType type, UMagneticComponent* magOperator, float DeltaTime);

protected:
	UFUNCTION()
	virtual AActor* ApplyMovement(EMagnetMoveType type, UMagneticComponent* safeMagOperator, float DeltaTime) PURE_VIRTUAL(UMagneticMovementComponent::ApplyMovement, return false;);
	UMagneticComponent* GetOwnerMagnetic() const;

private:
	/*Fields And Components*/
	UMagneticComponent* _MagOwner;
};
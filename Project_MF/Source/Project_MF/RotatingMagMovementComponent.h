// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "MagneticMovementComponent.h"
#include "RotatingMagMovementComponent.generated.h"

/*이 컴포넌트가 붙여있는 엑터에 부착되어있는 UMagneticComponent가 사용할 자석의 움직임이 정의된 컴포넌트 입니다.
 *끌어당겨질 때는 해당 움직임을 사용하는 자석이 끌어당기는 자석을 바라보게 되며, 밀려질 때는 해당 움직임을 사용하는 자석의
 * 반대방향을 보게 됩니다.
 */
UCLASS(ClassGroup = (MegneticMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API URotatingMagMovementComponent final : public UMagneticMovementComponent
{
	GENERATED_BODY()

private:
	/*Override methods*/
	virtual AActor* ApplyMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* SafeMagOperator, float DeltaTime) override;

	/*fields And Components*/
	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true, ClampMin = 0.f))
	float RotSpeed = 3.f;
	
};

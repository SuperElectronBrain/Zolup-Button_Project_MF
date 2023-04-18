#include "DefaultMagneticMovementComponent.h"
#include "DrawDebugHelpers.h"

UDefaultMagneticMovementComponent::UDefaultMagneticMovementComponent()
{
	_prevOperatorRadius = _operatorRadiusDiv = _operatorRadiusHalfDiv = _power = _shakePow = 0.f;
	_originUsedGravity = _registerHit = false;
}

void UDefaultMagneticMovementComponent::StartMovement(EMagnetMoveType moveType, UMagneticComponent* owner, UMagneticComponent* magOperator)
{
	FVector ownerPos = owner->GetMagneticFieldLocation();
	FVector operatorPos = magOperator->GetMagneticFieldLocation();
	FVector distance = (operatorPos - ownerPos);
	_distance = distance.Size();
	_currTime = 0.f;
	_goalTimeDiv = 1.f / .7f;
	_distanceDiv = 1.f / _distance;
	_startPos = ownerPos;
	_shakeDir = FVector::RightVector;
	_moveDir = distance.GetSafeNormal();
}

AActor* UDefaultMagneticMovementComponent::ApplyMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* SafeMagOperator, float DeltaTime)
{
	USceneComponent* updated = UpdatedComponent;

	//계산에 필요한 요소들을 모두 구한다...
	FVector ownerPos		= owner->GetMagneticFieldLocation();
	FVector operatorPos		= SafeMagOperator->GetMagneticFieldLocation();
	FVector dir				= (operatorPos - ownerPos);
	float distance			= dir.Size();
	float ownerRadius		= owner->GetMagneticFieldRadius();
	float operatorRadius	= SafeMagOperator->GetMagneticFieldRadius();
	float totalRadius		= ownerRadius + operatorRadius;

	//TODO: 나눗셈 제거는 다음에.... 
	_prevOperatorRadius		= operatorRadius;
	_operatorRadiusDiv		= 1.f / operatorRadius;
	_operatorRadiusHalfDiv	= 1.f / (operatorRadius * .65f);

	float penetrate		 = (totalRadius-distance);
	float penetrateRatio = penetrate * _operatorRadiusDiv;

	//현재 움직임 타입에 따라서 방향을 바꾼 방향벡터를 얻는다.
	dir = dir.GetSafeNormal() * (type == EMagnetMoveType::PUSHED_OUT ? -1.f : 1.f);

	//최종 이동량 결정
	FVector final = dir;
	float power = 0.f;

	//밀려날 경우
	if (type==EMagnetMoveType::PUSHED_OUT)
	{
		power = (.2f + 20.f * (penetrate * _operatorRadiusHalfDiv));
		if (penetrateRatio >= .65f) power += 10.f;

		Velocity = dir * (power * DeltaTime * 150.f);
		if (Velocity.Size() > operatorRadius * .5f)
		{
			Velocity = Velocity.GetSafeNormal() * operatorRadius * .5f;
		}
	}
	//끌어당겨질 경우
	else if (type==EMagnetMoveType::DRAWN_IN)
	{
		//power = (.2f + 20.f * (penetrate * _operatorRadiusHalfDiv));
		//if (penetrateRatio >= .8f) power += 50.f;
		float distanceRatio = (ownerPos - _startPos).Size() * _distanceDiv;

		if (distanceRatio >= .4f) power = _distance * 10.f * DeltaTime;
		else power = (_distance * .5f + _distance * (distanceRatio+.3f*2.f) ) * DeltaTime;

		Velocity = dir * power;
	}

	//이동제한 방향에 따라서 이동량 제거
	if (MoveType == EMagnetMoveAxisType::MOVE_ONLY_XY) Velocity.Z = 0.f;
	else if (MoveType == EMagnetMoveAxisType::MOVE_ONLY_Z) Velocity.X = Velocity.Y = 0.f;

	PrevDir = dir;

	//UE Simulate Physics가 true일 경우.
	if (UpdatedPrimitiveIsValid())
	{
		UPrimitiveComponent* physics = UpdatedPrimitive;
		physics->SetEnableGravity(false);
		physics->SetPhysicsLinearVelocity(FVector::ZeroVector);
	}

	//최종 이동량 적용 및 부드러운 움직임 적용.
	SafeMoveUpdatedComponent(Velocity, UpdatedComponent->GetComponentRotation(), true, hit, ETeleportType::TeleportPhysics);

	if (hit.bBlockingHit)
	{
		FHitResult hit2 = hit;
		UpdatedComponent->SetWorldRotation(FQuat::Identity);
		SlideAlongSurface(Velocity, 1.f - hit2.Time, hit2.Normal, hit2);
	}

	if (hit.IsValidBlockingHit() && FVector::DotProduct(dir, hit.Normal)<0 && type == EMagnetMoveType::DRAWN_IN && hit.GetActor()!=nullptr && ::IsValid(hit.GetActor()))
	{
		return hit.GetActor();
	}

	return nullptr;
}

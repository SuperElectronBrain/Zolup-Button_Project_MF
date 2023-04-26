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

	UPrimitiveComponent* ownerPhysics = owner->GetAttachmentPrimitive();
	if (ownerPhysics)
	{
		ownerPhysics->SetPhysicsLinearVelocity(FVector::ZeroVector);
		ownerPhysics->SetPhysicsAngularVelocity(FVector::ZeroVector);
	}
}

void UDefaultMagneticMovementComponent::EndMovement(EMagnetMoveType endType, UMagneticComponent* owner)
{
	UPrimitiveComponent* ownerPhysics = owner->GetAttachmentPrimitive();
	if (ownerPhysics)
	{
		ownerPhysics->SetPhysicsLinearVelocity(FVector::ZeroVector);
		ownerPhysics->SetPhysicsAngularVelocity(FVector::ZeroVector);
	}
}

AActor* UDefaultMagneticMovementComponent::ApplyMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* SafeMagOperator, float DeltaTime)
{
	UPrimitiveComponent* ownerPhysics = owner->GetAttachmentPrimitive();
	UPrimitiveComponent* operatorPhysics = SafeMagOperator->GetAttachmentPrimitive();

	//물리가 적용되는 녀석일 경우.
	if (ownerPhysics && operatorPhysics && ownerPhysics->IsSimulatingPhysics() && type == EMagnetMoveType::DRAWN_IN)
	{
		FVector ownerCenter = ownerPhysics->GetCenterOfMass();
		FVector operatorCenter = operatorPhysics->GetCenterOfMass();
		FVector move = operatorCenter - ownerCenter;
		FVector dir = move.GetSafeNormal();
		float distance = move.Size();
		float ownerRadius = owner->GetMagneticFieldRadius();
		float operatorRadius = SafeMagOperator->GetMagneticFieldRadius();
		float totalRadius = ownerRadius + operatorRadius;
		float penetrateRatio = FMath::Clamp((totalRadius-distance)/operatorRadius, 0.f, 1.f);
		float pow = 0.f;

		if (type == EMagnetMoveType::PUSHED_OUT)
		{
			ownerPhysics->SetEnableGravity(true);
			pow = totalRadius * penetrateRatio;
			ownerPhysics->SetPhysicsLinearVelocity(-dir * pow);
		}
		else if(type==EMagnetMoveType::DRAWN_IN)
		{
			ownerPhysics->SetEnableGravity(false);
			//pow = 80000.f * penetrateRatio * ownerPhysics->GetMass();

			//UE_LOG(LogTemp, Warning, TEXT("distance: %f"), distance)
			if (penetrateRatio>=.7f)
			{
				pow = 100000.f * ownerPhysics->GetMass();
				ownerPhysics->AddForceAtLocation(dir * pow, ownerCenter);
			}
			else
			{
				ownerPhysics->SetPhysicsLinearVelocity((300.f + 300.f * penetrateRatio) * dir);
			}
			
			//UE_LOG(LogTemp, Warning, TEXT("LinearVelocity: %f / AngularVelocity: %f"), ownerPhysics->GetPhysicsLinearVelocity().Size(), ownerPhysics->GetPhysicsAngularVelocity().Size())
			//ownerPhysics->AddForceAtLocation(dir * pow, ownerCenter);
			//ownerPhysics->SetPhysicsAngularVelocity(FVector::ZeroVector);
		}

		return nullptr;
	}

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
		float distanceRatio = (ownerPos - _startPos).Size() * _distanceDiv;
		power = (_distance * .5f + _distance * (distanceRatio+.3f*2.f) ) * DeltaTime;

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
		SlideAlongSurface(Velocity, 1.f - hit2.Time, hit2.Normal, hit2);
	}

	if (hit.IsValidBlockingHit() && FVector::DotProduct(dir, hit.Normal)<0 && type == EMagnetMoveType::DRAWN_IN && hit.GetActor()!=nullptr && ::IsValid(hit.GetActor()))
	{
		return hit.GetActor();
	}

	return nullptr;
}

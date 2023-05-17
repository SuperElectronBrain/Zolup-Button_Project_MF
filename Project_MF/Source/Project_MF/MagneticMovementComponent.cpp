#include "MagneticMovementComponent.h"
#include "MagneticComponent.h"

UMagneticMovementComponent::UMagneticMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	_MagOwner = nullptr;
}

UMagneticComponent* UMagneticMovementComponent::GetOwnerMagnetic() const
{
	if (_MagOwner && ::IsValid(_MagOwner))
	{
		return _MagOwner;
	}

	return GetOwner()->FindComponentByClass<UMagneticComponent>();
}

void UMagneticMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
	//유효하지 않은 UpdatedComponent라면 스킵.
	if (NewUpdatedComponent==nullptr || !::IsValid(NewUpdatedComponent))
	{
		return;
	}

	UpdatedComponent = NewUpdatedComponent->GetOwner()->GetRootComponent();

	if(_MagOwner==nullptr || !::IsValid(_MagOwner)) 
		_MagOwner = NewUpdatedComponent->GetOwner()->FindComponentByClass<UMagneticComponent>();

	Super::SetUpdatedComponent(NewUpdatedComponent);
}

void UMagneticMovementComponent::ApplyUpdatedComponentMovement(EMagnetMoveType type, UMagneticComponent* owner, UMagneticComponent* magOperator, float DeltaTime, FHitResult& HitResult)
{
	if (type == EMagnetMoveType::NONE || magOperator == nullptr && !::IsValid(magOperator) || owner == nullptr && !::IsValid(owner))
		return;

	//이동 상태에 따라서 알맞은 로직 처리
	ApplyMovement(type,owner, magOperator,  DeltaTime, HitResult);
}
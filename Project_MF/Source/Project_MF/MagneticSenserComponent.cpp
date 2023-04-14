#include "MagneticSenserComponent.h"
#include "MagneticComponent.h"
#include "MagneticSenserEffectComponent.h"

TMap<UMagneticComponent*, TArray<UMagneticSenserComponent*>> UMagneticSenserComponent::_applyList;

UMagneticSenserComponent::UMagneticSenserComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	_senseRange = nullptr;
	_effect = nullptr;
}

void UMagneticSenserComponent::OnChildAttached(USceneComponent* ChildComponent)
{
	Super::OnChildAttached(ChildComponent);

	if (GetEffectIsValid()==false)
	{
		UMagneticSenserEffectComponent* effect = Cast<UMagneticSenserEffectComponent>(ChildComponent);
		if (effect && ::IsValid(effect))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s가 효과로 붙여짐!!"), *ChildComponent->GetName())
			_effect = effect;
			return;
		}
	}

	if (GetRangeIsValid()==false)
	{
		UPrimitiveComponent* range = Cast<UPrimitiveComponent>(ChildComponent);
		if (range && IsValid(range))
		{
			_senseRange = range;
		}
	}
}

void UMagneticSenserComponent::OnChildDetached(USceneComponent* ChildComponent)
{
	Super::OnChildDetached(ChildComponent);

	if (_effect==ChildComponent)
	{
		_effect = nullptr;
		return;
	}

	if (_senseRange==ChildComponent)
	{
		_senseRange = nullptr;
		return;
	}
}

void UMagneticSenserComponent::GetMagnetAppliedSenserList(UMagneticComponent* magnet, TArray<UMagneticSenserComponent*>& outList)
{
	if (magnet == nullptr || !::IsValid(magnet)) return;
	if (_applyList.Contains(magnet) == false) return;
	
	TArray<UMagneticSenserComponent*>& lists = _applyList[magnet];

	outList.Reset();
	outList.Reserve(lists.Num());

	for (UMagneticSenserComponent* e : lists)
	{
		outList.Add(e);
	}
}

void UMagneticSenserComponent::GetMagnetAppliedSenserListByClass(UMagneticComponent* magnet, TArray<UMagneticSenserComponent*>& outList, UClass* filterClass)
{
	if (magnet == nullptr || !::IsValid(magnet)) return;
	if (_applyList.Contains(magnet) == false) return;

	TArray<UMagneticSenserComponent*>& lists = _applyList[magnet];

	outList.Reset();
	outList.Reserve(lists.Num());

	for (UMagneticSenserComponent* e : lists)
	{
		if (e->_effect && e->_effect->GetClass()==filterClass)
		{
			outList.Add(e);
		}
	}
}

bool UMagneticSenserComponent::GetEffectIsValid() const
{
	return (_effect && ::IsValid(_effect));
}

bool UMagneticSenserComponent::GetRangeIsValid() const
{
	return (_senseRange && ::IsValid(_senseRange));
}

void UMagneticSenserComponent::BeginPlay()
{
	Super::BeginPlay();

	//범위 충돌 초기화.
	if (GetRangeIsValid())
	{
		_senseRange->SetCollisionObjectType(MAGNETIC_COLLISION_OBJECTTYPE);
		_senseRange->SetCollisionProfileName(MAGNETIC_COLLISION_PROFILE);
		_senseRange->SetGenerateOverlapEvents(true);
		if (_senseRange->IsSimulatingPhysics()) _senseRange->SetSimulatePhysics(false);
	}

	//효과를 적용할 수 있는 상태라면 첫 적용을 시도한다.
	if (GetRangeIsValid() && GetEffectIsValid())
	{
		_senseRange->OnComponentBeginOverlap.AddDynamic(this, &UMagneticSenserComponent::BeginOverlap);
		_senseRange->OnComponentEndOverlap.AddDynamic(this, &UMagneticSenserComponent::EndOverlap);

		//사전에 미리 겹쳐있는 오브젝트들이 있다면 가져와서 효과를 적용시킨다.
		TArray<UPrimitiveComponent*> overlapList;
		_senseRange->GetOverlappingComponents(overlapList);

		if (overlapList.Num() > 0) {
			for (auto p : overlapList)
			{
				//해당 자석과 부착된 엑터가 같거나, USphereComponent가 아닐 경우 스킵.
				if (p->GetOwner() == GetOwner() || p->GetClass() != USphereComponent::StaticClass()) continue;
				UMagneticComponent* magnet = Cast<UMagneticComponent>(p->GetAttachParent());

				//만약 MagneticComponent가 유효하지 않거나, 유효한데 강화도가 더 높다면 스킵.
				if (magnet == nullptr || !::IsValid(magnet))
					continue;

				//효과가 존재할 경우
				ApplyEffect(magnet);
			}
		}

	} //END
}

void UMagneticSenserComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//오버랩 콜백 삭제
	if (GetRangeIsValid())
	{
		_senseRange->OnComponentBeginOverlap.RemoveDynamic(this, &UMagneticSenserComponent::BeginOverlap);
		_senseRange->OnComponentEndOverlap.RemoveDynamic(this, &UMagneticSenserComponent::EndOverlap);
	}

	//현재 영향을 주고 있는 자석들에서 참조를 모두 지운다.
	TArray<UMagneticComponent*> keys;
	_applyList.GetKeys(keys);

	int count = keys.Num();
	for (int i = 0; i < count; i++)
	{
		ReleaseEffect(keys[i]);
	}
}

void UMagneticSenserComponent::ApplyEffect(UMagneticComponent* const magnet)
{
	if (magnet == nullptr || !::IsValid(magnet)) return;

	if (!_applyList.Contains(magnet)) _applyList.Add(magnet, TArray<UMagneticSenserComponent*>());
	if (!_applyList[magnet].Contains(this)) _applyList[magnet].Add(this);

	if (GetEffectIsValid())
	{
		_effect->ApplyEffect(magnet, this);
	}
}
void UMagneticSenserComponent::ReleaseEffect(UMagneticComponent* const magnet)
{
	if (magnet == nullptr || !::IsValid(magnet)) return;

	if (!_applyList.Contains(magnet)) return;
	if (_applyList[magnet].Contains(this))
	{
		_applyList[magnet].Remove(this);
		if (_applyList[magnet].Num() == 0) _applyList.Remove(magnet);
	}

	if (GetEffectIsValid())
	{
		_effect->ReleaseEffect(magnet, this);
	}
}

bool UMagneticSenserComponent::CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const
{
	if (ChildComponent == nullptr || !::IsValid(ChildComponent)) return false;

	//UE_LOG(LogTemp, Warning, TEXT("붙일 컴포넌트는: %s"), *ChildComponent->GetName())
	if (GetRangeIsValid()==false)
	{
		UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(ChildComponent);
		if (primitive)
		{
			return true;
		}
	}

	if (GetEffectIsValid()==false)
	{
		UMagneticSenserEffectComponent* effect = Cast<UMagneticSenserEffectComponent>(ChildComponent);
		if (effect)
		{
			return true;
		}
	}

	return _effect==ChildComponent || _senseRange==ChildComponent;
}

void  UMagneticSenserComponent::DestroyComponent(bool bPromoteChilderen)
{
	if (GetRangeIsValid())
	{
		_senseRange->DestroyComponent(bPromoteChilderen);
	}

	if (GetEffectIsValid())
	{
		_effect->DestroyComponent(bPromoteChilderen);
	}

	Super::DestroyComponent(bPromoteChilderen);
}

void  UMagneticSenserComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ApplyEffect(Cast<UMagneticComponent>(OtherComp->GetAttachParent()));
}

void  UMagneticSenserComponent::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ReleaseEffect(Cast<UMagneticComponent>(OtherComp->GetAttachParent()));
}

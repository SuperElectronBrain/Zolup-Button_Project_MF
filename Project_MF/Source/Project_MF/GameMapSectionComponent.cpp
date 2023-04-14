#include "GameMapSectionComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UGameMapSectionComponent::UGameMapSectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UGameMapSectionComponent::CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const
{
	return false;
}

void UGameMapSectionComponent::RemoveResetPoint(AActor* actor)
{
	//존재여부를 확인하고, 존재하면 지운다.
	int32 count = _infoList.Num();
	for (int32 i=0; i<count ; i++)
	{
		FActorBeginInfo info = _infoList[i];

		if (info.Actor==nullptr || info.Actor==actor || info.Actor && !::IsValid(info.Actor) )
		{
			_infoList.RemoveAt(i);
			return;
		}
	}
}

void UGameMapSectionComponent::AddResetPoint(AActor* actor)
{
	//중복체크를 한다.
	int32 count = _infoList.Num();
	for (int32 i=0; i<count ; i++)
	{
		FActorBeginInfo& info = _infoList[i];

		if (info.Actor && ::IsValid(info.Actor)){
			if (info.Actor == actor)
			{
				info.Transform = actor->GetTransform();
				return;
			}
		}
		else
		{
			_infoList.RemoveAt(i);
			i--;
			count = _infoList.Num();
			continue;
		}

	}

	FActorBeginInfo newInfo;
	newInfo.Actor = actor;
	newInfo.Transform = actor->GetTransform();
	_infoList.Add(newInfo);
}

void UGameMapSectionComponent::SetSection(ESectionSettingType type)
{
	switch (type){

			//////////////////////////////////////////////////
			case(ESectionSettingType::SECTION_RESET_BEGIN_PLAY):
			{
				if (bIsCompleteSection) return;
				int32 count = _infoList.Num();
				for (int32 i = 0; i < count; i++)
				{
					const FActorBeginInfo& info = _infoList[i];

					if (info.Actor == nullptr || info.Actor && !::IsValid(info.Actor))
					{
						_infoList.RemoveAt(i);
						count = _infoList.Num();
						i--;
						continue;
					}

					info.Actor->SetActorLocation(info.Transform.GetLocation());
					info.Actor->SetActorRotation(info.Transform.GetRotation());
					info.Actor->SetActorScale3D(info.Transform.GetScale3D());
				}
				break;
			}

			//////////////////////////////////////////////////
			case(ESectionSettingType::SECTION_COMPLETE):
			{
				bIsCompleteSection = true;
				break;
			}

	}
}

void UGameMapSectionComponent::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);
}

void UGameMapSectionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	for (auto a : _infoList)
	{
		a.Actor->SetActorLocation(a.Actor->GetActorLocation() + FVector::RightVector);
	}
}


// Called when the game starts
void UGameMapSectionComponent::BeginPlay()
{
	Super::BeginPlay();

	//이 컴포넌트가 붙어있는 엑터의 하위 엑터들의 트랜스폼 정보를 모조리 가져온다.
	TArray<AActor*> childs;
	GetOwner()->GetAttachedActors(childs, true);

	_infoList.Reset();
	_infoList.Reserve(childs.Num());
	for (AActor* a : childs)
	{
		if (a==nullptr || a && !::IsValid(a)) continue;

		FActorBeginInfo info;
		info.Actor = a;
		info.Transform = a->GetTransform();
		_infoList.Add(info);
	}
}

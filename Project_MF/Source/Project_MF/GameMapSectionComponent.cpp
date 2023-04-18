#include "GameMapSectionComponent.h"
#include "Components/BoxComponent.h"
#include "MagneticComponent.h"
#include "Components/MeshComponent.h"
#include "GameCheckPointContainerComponent.h"

// Sets default values for this component's properties
UGameMapSectionComponent::UGameMapSectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGameMapSectionComponent::OnAttachmentChanged()
{
	ShapeColor = FColor::Blue;
}

void MoveCheckPoint(AActor* actor)
{

}

void UGameMapSectionComponent::SetSection(ESectionSettingType type)
{
	switch (type){

			//////////////////////////////////////////////////
			case(ESectionSettingType::SECTION_RESET_BEGIN_PLAY):
			{
				if (bIsCompleteSection) return;

				//엑터 정보 리셋
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

				//자성 정보 리셋
				count = _magInfoList.Num();
				for (int32 i=0; i<count; i++)
				{
					const FMagneticBeginInfo& info = _magInfoList[i];

					if (info.Magnetic==nullptr || info.Magnetic && !::IsValid(info.Magnetic))
					{
						_magInfoList.RemoveAt(i);
						count = _magInfoList.Num();
						i--;
						continue;
					}

					info.Magnetic->SetCurrentMagnetic(info.Type);
					info.Magnetic->SetMagneticFieldRadiusScale(info.MagneticFieldRadiusScale);
					info.Magnetic->SetMaxHaveMagneticSeconds(info.MaxHaveMagneticSeconds);
				}

				//이 섹션에 들어와 있는 체크포인트 컨테이너들의 위치를 저장된 체크포인트로 이동시킨다.
				TArray<AActor*> overlaps;
				GetOverlappingActors(overlaps);
				for (AActor* a : overlaps)
				{
					UGameCheckPointContainerComponent* container = Cast<UGameCheckPointContainerComponent>(a->GetComponentByClass(UGameCheckPointContainerComponent::StaticClass()));
					if (container && ::IsValid(container) && 
						container->CheckPoint && ::IsValid(container->CheckPoint))
					{
						container->GetOwner()->SetActorLocation(container->CheckPoint->GetActorLocation());
					}
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

bool UGameMapSectionComponent::AddActorInfo(AActor* actor)
{
	if (actor == nullptr || actor && !::IsValid(actor)) return false;
	FActorBeginInfo info;
	info.Actor = actor;
	info.Transform = actor->GetTransform();
	_infoList.Add(info);

	return true;
}

bool UGameMapSectionComponent::AddMagnetInfo(USceneComponent* components)
{
	UMeshComponent* mesh = Cast<UMeshComponent>(components);

	if (mesh && ::IsValid(mesh))
	{
		TArray<USceneComponent*> childs;
		mesh->GetChildrenComponents(true, childs);

		for (auto s : childs) {

			UMagneticComponent* magnet = Cast<UMagneticComponent>(s);

			if (magnet && ::IsValid(magnet))
			{
				FMagneticBeginInfo info;
				info.Magnetic = magnet;
				info.Type = magnet->GetCurrentMagnetic();
				info.MagneticFieldRadiusScale = magnet->GetMagneticFieldRadiusScale();
				info.MaxHaveMagneticSeconds = magnet->GetMaxHaveMangeticSeconds();

				_magInfoList.Add(info);
				return true;
			}

		}
	}

	return false;
}

// Called when the game starts
void UGameMapSectionComponent::BeginPlay()
{
	Super::BeginPlay();

	//이 컴포넌트가 붙어있는 엑터의 하위 엑터들의 트랜스폼 정보를 모조리 가져온다.
	TArray<AActor*> childs;
	GetOwner()->GetAttachedActors(childs, true);

	//UE_LOG(LogTemp, Warning, TEXT("시작 크기: %d"), childs.Num())
	_infoList.Reset();
	_infoList.Reserve(childs.Num());
	for (AActor* a : childs)
	{
		if (a==nullptr || a && !::IsValid(a)) continue;

		AddActorInfo(a);

		//해당 엑터의 컴포넌트들을 순회해서, 자성 컴포넌트만을 찾는다.
		TArray<USceneComponent*> components;
		a->GetRootComponent()->GetChildrenComponents(true, components);

		//Start------------------
		for (auto s : components) {

			if (AddMagnetInfo(s)==false)
			{
				UMagneticComponent* magnet = Cast<UMagneticComponent>(s);

				if (magnet && ::IsValid(magnet))
				{
					FMagneticBeginInfo minfo;
					minfo.Magnetic = magnet;
					minfo.Type = magnet->GetCurrentMagnetic();
					minfo.MagneticFieldRadiusScale = magnet->GetMagneticFieldRadiusScale();
					minfo.MaxHaveMagneticSeconds = magnet->GetMaxHaveMangeticSeconds();

					_magInfoList.Add(minfo);
				}
			}

		}
		//End--------------------
	}
}

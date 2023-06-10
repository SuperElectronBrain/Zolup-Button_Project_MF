#include "GameMapSectionComponent.h"
#include "MagneticComponent.h"
#include "Components/MeshComponent.h"
#include "GameCheckPointContainerComponent.h"

// Sets default values for this component's properties
UGameMapSectionComponent::UGameMapSectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	/*CDO - GameSectionData*/
	static ConstructorHelpers::FObjectFinder<UDataTable> SECTION_DATA_TABLE(
		TEXT("/Game/Blueprints/GameSetting/GameMapSectionDataTable.GameMapSectionDataTable")
	);

	if (SECTION_DATA_TABLE.Succeeded()) _SectionDataTable = SECTION_DATA_TABLE.Object;
}

void UGameMapSectionComponent::SetCurrSectionDMGCount(int32 newValue)
{
	CurrSectionDMGCount = newValue;
	if (CurrSectionDMGCount < 0) CurrSectionDMGCount = 0;
	else if (CurrSectionDMGCount > _MaxSectionDMGCount)
	{
		CurrSectionDMGCount = _MaxSectionDMGCount;
	}
}

void UGameMapSectionComponent::OnAttachmentChanged()
{
	ShapeColor = FColor::Blue;
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

					if (info.Actor.IsValid()==false)
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

					if (info.Magnetic.IsValid()==false)
					{
						_magInfoList.RemoveAt(i);
						count = _magInfoList.Num();
						i--;
						continue;
					}

					info.Magnetic->SetCurrentMagnetic(EMagneticType::NONE);
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

#if WITH_EDITOR
void UGameMapSectionComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FString& changed = PropertyChangedEvent.GetPropertyName().ToString();

	if (changed == "SectionDataName")
	{
		if (_SectionDataTable && _SectionDataTable->GetRowMap().Num() > 0)
		{
			FSectionData* Data = _SectionDataTable->FindRow<FSectionData>(*SectionDataName, TEXT(""));
			if (Data)
			{
				_MaxSectionDMGCount = Data->MaxDMGCount;
				_bIgnorePlayerGiven = Data->bIgnorePlayerGiven;
				_bResetCountByExitPlayer = Data->bResetCountByExitPlayer;
			}
		}

		return;
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

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

	/*섹션 데이터 테이블에서 지정된 이름의 값들을 가져온다.*/
	if (_SectionDataTable && _SectionDataTable->GetRowMap().Num() > 0)
	{
		FSectionData* Data = _SectionDataTable->FindRow<FSectionData>(*SectionDataName, TEXT(""));
		if (Data)
		{
			_MaxSectionDMGCount = Data->MaxDMGCount;
			_bIgnorePlayerGiven = Data->bIgnorePlayerGiven;
		}
	}


	/*이 컴포넌트가 붙어있는 엑터의 하위 엑터들의 트랜스폼 정보를 모조리 가져온다.*/
	TArray<AActor*> childs;
	GetOwner()->GetAttachedActors(childs, true);

	_infoList.Reset();
	_infoList.Reserve(childs.Num());
	for (AActor* a : childs)
	{
		if (a==nullptr || a && !::IsValid(a)) continue;

		AddActorInfo(a);

		//해당 엑터의 컴포넌트들을 순회해서, 자성 컴포넌트만을 찾는다.
		TArray<USceneComponent*> components;
		a->GetRootComponent()->GetChildrenComponents(true, components);

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
	}


}

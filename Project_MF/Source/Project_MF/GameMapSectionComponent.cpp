#include "GameMapSectionComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UGameMapSectionComponent::UGameMapSectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Range = CreateDefaultSubobject<UBoxComponent>(TEXT("RANGE"));
	Range->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	Range->SetupAttachment(this);
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

void UGameMapSectionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	static float time = 0.f;

	if ((time+=DeltaTime)>=5.f)
	{
		time = 0.f;
		SetSection(ESectionSettingType::SECTION_RESET_BEGIN_PLAY);

	}
}


// Called when the game starts
void UGameMapSectionComponent::BeginPlay()
{
	Super::BeginPlay();

	//이 컴포넌트가 붙어있는 엑터의 하위 엑터들의 트랜스폼 정보를 모조리 가져온다.
	TArray<AActor*> childs;
	GetOwner()->GetAttachedActors(childs, true);

	UE_LOG(LogTemp, Warning, TEXT("시작 크기: %d"), childs.Num())
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

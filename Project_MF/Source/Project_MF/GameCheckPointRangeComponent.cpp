#include "GameCheckPointRangeComponent.h"
#include "GameMapSectionComponent.h"
#include "GameCheckPointContainerComponent.h"
#include "CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UIBlackScreenWidget.h"

UGameCheckPointRangeComponent::UGameCheckPointRangeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	HitApplyTiming = EHitCheckPointRangeApplyTiming::APPLY_IMMEDIATELY;
	HitApplyType = EHitCheckPointRangeApplyType::SAVE_CHECKPOINT;
	HitApplyAfterType = EHitCheckPointRangeApplyAfterType::NONE;
	ShapeColor = FColor::Emerald;
}

void UGameCheckPointRangeComponent::FadeChange(bool isDark, int id)
{
	if (isDark == false) return;
	if (!(id == 834 && HitApplyType == EHitCheckPointRangeApplyType::OPEN_LEVEL) && id!=CHECKPOINT_FADE_ID)
	{
		return;
	}

	ApplyRogic(_moveTarget.Get());
	_moveTarget.Reset();
}

void UGameCheckPointRangeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (_Instance.IsValid())
	{
		_Instance->GetUIManager()->OnUIFadeChange.RemoveDynamic(this, &UGameCheckPointRangeComponent::FadeChange);
	}
}

bool UGameCheckPointRangeComponent::CanAttachAsChild(const USceneComponent* ChildComponent, FName SocketName) const
{
	return false;
}

void UGameCheckPointRangeComponent::BeginPlay()
{
	Super::BeginPlay();

	//부모 섹션에 대한 참조.
	Section = Cast<UGameMapSectionComponent>(GetAttachParent());

	//충돌에 대한 델리게이트 구독.
	OnComponentBeginOverlap.AddDynamic(this, &UGameCheckPointRangeComponent::BeginOverlap);

	//GameInstance 참조 확보 및 페이드 아웃 이벤트 구독.
	_Instance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());
	if (_Instance.IsValid())
	{
		 _Instance->GetUIManager()->OnUIFadeChange.AddDynamic(this, &UGameCheckPointRangeComponent::FadeChange);
	}

	//게임 시작전부터 겹쳐있을 경우에 대한 처리
	TArray<AActor*> overlaps;
	GetOverlappingActors(overlaps);

	for (AActor* a : overlaps)
	{
		ApplyRogic(a);
	}
}

void UGameCheckPointRangeComponent::ApplyRogic(AActor* actor)
{
	//유효하지 않은 엑터라면, 아니라면 탈출.
	if (actor == nullptr || actor && !::IsValid(actor)) return;
	UGameCheckPointContainerComponent* container = Cast<UGameCheckPointContainerComponent>(actor->GetComponentByClass(UGameCheckPointContainerComponent::StaticClass()));

	if (container == nullptr || container && !::IsValid(container)) return;

	//적용할 로직을 결정한다.
	switch (HitApplyType) {

		case(EHitCheckPointRangeApplyType::MOVE_TO_CHECKPOINT):
			if (CheckPoint && ::IsValid(CheckPoint))
			{
				container->GetOwner()->SetActorLocation(CheckPoint->GetActorLocation());
			}
			break;

		case(EHitCheckPointRangeApplyType::MOVE_TO_LAST_CHECKPOINT):
			if (container->CheckPoint && ::IsValid(container->CheckPoint))
			{
				container->GetOwner()->SetActorLocation(container->CheckPoint->GetActorLocation());
			}
			break;

		case(EHitCheckPointRangeApplyType::SAVE_CHECKPOINT):
			if (CheckPoint && ::IsValid(CheckPoint))
			{
				container->CheckPoint = CheckPoint;
			}
			break;

		case(EHitCheckPointRangeApplyType::OPEN_LEVEL):
			{
				UGameplayStatics::OpenLevel(GetWorld(),OpenLevelName);
			}
			break;
	}

	//로직 적용 후의 로직을 적용한다.
	switch (HitApplyAfterType){
		case(EHitCheckPointRangeApplyAfterType::DESTROY_THIS):
			DestroyComponent(true);
			break;

	}
}

void UGameCheckPointRangeComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	switch (HitApplyTiming) {

		case(EHitCheckPointRangeApplyTiming::APPLY_IMMEDIATELY):
			ApplyRogic(OtherActor);
			break;

		case(EHitCheckPointRangeApplyTiming::APPLY_AFTER_UI_FADEOUT):
			TWeakObjectPtr<UUIBlackScreenWidget> blackScreen;
			if (_Instance.IsValid())
			{
				_Instance->GetUIManager()->GetUIBlackScreenWidget(blackScreen);
				if (_Instance->GetUIManager()->IsPlayingFadeByID(CHECKPOINT_FADE_ID)) return;

				_moveTarget.Reset();
				_moveTarget = OtherActor;

				//뷰포트에 추가되지 않았다면 추가.
				if (blackScreen->IsInViewport()==false)
					blackScreen->AddToViewport();

				bool removeViewport = (HitApplyType == EHitCheckPointRangeApplyType::OPEN_LEVEL);

				//페이드 아웃 실행
				if (blackScreen.IsValid())
				{
					_Instance->GetUIManager()->PlayFadeInOut(
						EFadeType::WHITE_TO_DARK_TO_WHITE,
						blackScreen.Get(),
						2.f,
						2.f,
						1.f,
						0.f,
						0.f,
						1.f,
						CHECKPOINT_FADE_ID,
						FLinearColor::Black,
						FLinearColor::Black,
						false,
						removeViewport
					);
				}
			}
			break;

	}
}
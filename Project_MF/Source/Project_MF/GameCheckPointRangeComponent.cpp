#include "GameCheckPointRangeComponent.h"
#include "GameMapSectionComponent.h"
#include "GameCheckPointContainerComponent.h"
#include "CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UIBlackScreenWidget.h"
#include "GamePlayerCharacter.h"

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
	if (isDark == false || id != CHECKPOINT_FADE_ID) return;

	if (_moveTarget.IsValid() == false) return;

	ApplyRogic(_moveTarget.Get(), HitApplyType);
	for (auto type : HitApplyTypes) ApplyRogic(_moveTarget.Get(), type);

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
		UGameCheckPointContainerComponent* container = Cast<UGameCheckPointContainerComponent>(a->GetComponentByClass(UGameCheckPointContainerComponent::StaticClass()));
		ApplyRogic(container, HitApplyType);

		for (auto type : HitApplyTypes) ApplyRogic(container, type);
	}
}

void UGameCheckPointRangeComponent::ApplyRogic(UGameCheckPointContainerComponent* container, EHitCheckPointRangeApplyType applyType)
{
	//유효하지 않은 엑터라면, 아니라면 탈출.
	if (::IsValid(container)==false) return;

	//적용할 로직을 결정한다.
	switch (applyType) {

		/**지정한 위치로 엑터를 옮깁니다.*/
		case(EHitCheckPointRangeApplyType::MOVE_TO_CHECKPOINT):
			if (CheckPoint && ::IsValid(CheckPoint))
			{
				container->GetOwner()->SetActorLocation(CheckPoint->GetActorLocation());
			}
			break;

		/**이 엑터를 마지막 세이브 장소로 이동시킵니다.*/
		case(EHitCheckPointRangeApplyType::MOVE_TO_LAST_CHECKPOINT):
			if (container->CheckPoint && ::IsValid(container->CheckPoint))
			{
				container->GetOwner()->SetActorLocation(container->CheckPoint->GetActorLocation());
			}
			break;

		/**이 체크포인트 범위가 가르키는 세이브 포인트를 엑터에 저장시킵니다.*/
		case(EHitCheckPointRangeApplyType::SAVE_CHECKPOINT):
		{
			if (CheckPoint && ::IsValid(CheckPoint))
			{
				container->CheckPoint = CheckPoint;
			}
			break;
		}

		/**새로운 레벨을 엽니다.*/
		case(EHitCheckPointRangeApplyType::OPEN_LEVEL):
		{
			UGameplayStatics::OpenLevel(GetWorld(),OpenLevelName);
			break;
		}

		/**특정 사운드를 실행합니다.*/
		case(EHitCheckPointRangeApplyType::PLAY_SOUND2D):
		{
			if (SoundSource)
			{
				UGameplayStatics::PlaySound2D(
					GetWorld(),
					SoundSource,
					1.f
				);
			}
			break;
		}

		/**플레이어가 데미지 이벤트 모드에 들어가도록 합니다.*/
		case(EHitCheckPointRangeApplyType::SET_PLAYER_DMG_MODE):
		{
			AGamePlayerCharacter* player = Cast<AGamePlayerCharacter>(container->GetOwner());
			if (::IsValid(player))
			{
				player->SetDMGMode();
				if (CheckPoint && ::IsValid(CheckPoint))
				{
					UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(CheckPoint->GetRootComponent());
					if (primitive) {
						primitive->SetSimulatePhysics(true);
						primitive->SetVisibility(true);

						FVector playerPos = player->GetActorLocation();
						FVector checkPos = CheckPoint->GetActorLocation();
						
						const FRotator rotation = player->GetController()->GetControlRotation();
						const FRotator yawRotation(0, rotation.Yaw, 0);
						const FVector dir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

						FVector result = FVector(playerPos.X, playerPos.Y, checkPos.Z) + (dir * 15.f);

						CheckPoint->SetActorLocation(result);
					}

				}
			}

		}
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
	UGameCheckPointContainerComponent* container = Cast<UGameCheckPointContainerComponent>(OtherActor->GetComponentByClass(UGameCheckPointContainerComponent::StaticClass()));
	if (::IsValid(container)==false) return;

	switch (HitApplyTiming) {

		case(EHitCheckPointRangeApplyTiming::APPLY_IMMEDIATELY):
		{
			ApplyRogic(container, HitApplyType);
			for (auto type : HitApplyTypes) ApplyRogic(container, type);
			break;
		}

		case(EHitCheckPointRangeApplyTiming::APPLY_AFTER_UI_FADEOUT):
		{
			TWeakObjectPtr<UUIBlackScreenWidget> blackScreen;
			if (_Instance.IsValid())
			{
				_Instance->GetUIManager()->GetUIBlackScreenWidget(blackScreen);
				if (_Instance->GetUIManager()->IsPlayingFadeByID(CHECKPOINT_FADE_ID)) return;

				_moveTarget.Reset();
				_moveTarget = container;

				//뷰포트에 추가되지 않았다면 추가.
				if (blackScreen->IsInViewport() == false)
					blackScreen->AddToViewport();

				bool removeViewport = (HitApplyType == EHitCheckPointRangeApplyType::OPEN_LEVEL);
				int usedID = CHECKPOINT_FADE_ID;

				_Instance->GetUIManager()->StopFadeInOutByHandler(blackScreen.Get());

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
						usedID,
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
}
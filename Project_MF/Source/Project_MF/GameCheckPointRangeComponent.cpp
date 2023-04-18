#include "GameCheckPointRangeComponent.h"
#include "GameMapSectionComponent.h"
#include "GameCheckPointContainerComponent.h"

UGameCheckPointRangeComponent::UGameCheckPointRangeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	HitApplyTiming = EHitCheckPointRangeApplyTiming::APPLY_IMMEDIATELY;
	HitApplyType = EHitCheckPointRangeApplyType::SAVE_CHECKPOINT;
	HitApplyAfterType = EHitCheckPointRangeApplyAfterType::NONE;
	ShapeColor = FColor::Emerald;
}

void UGameCheckPointRangeComponent::FadeWait(AActor* actor)
{
	APlayerCameraManager* c = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	if (c) c->StartCameraFade(1.f, 0.f, 1.f, FLinearColor::Black, false, true);
	ApplyRogic(actor);
}


void UGameCheckPointRangeComponent::BeginPlay()
{
	Super::BeginPlay();

	Section = Cast<UGameMapSectionComponent>(GetAttachParent());

	OnComponentBeginOverlap.AddDynamic(this, &UGameCheckPointRangeComponent::BeginOverlap);

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
	UGameCheckPointContainerComponent* container = Cast<UGameCheckPointContainerComponent>(actor->GetComponentByClass(UGameCheckPointContainerComponent::StaticClass()));

	if (actor == nullptr || actor && !::IsValid(actor) || container==nullptr || container && !::IsValid(container)) return;

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
	}

	//로직 적용 후의 로직을 적용한다.
	switch (HitApplyAfterType){
		case(EHitCheckPointRangeApplyAfterType::DESTROY_THIS):
			DestroyComponent(true);
			UE_LOG(LogTemp, Warning, TEXT("삭제될 운명!!"))
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

			APlayerCameraManager* c = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
			if (c) c->StartCameraFade(0.f, 1.f, 1.f, FLinearColor::Black, false, true);
			
			FTimerHandle handle;
			FTimerDelegate callback = FTimerDelegate::CreateUObject(
				this,
				&UGameCheckPointRangeComponent::FadeWait,
				OtherActor
			);

			GetWorld()->GetTimerManager().SetTimer(
				handle,
				callback,
				2.f,
				false
			);
			break;

	}
}
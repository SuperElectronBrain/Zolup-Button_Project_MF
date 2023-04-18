#include "PlayerAirVent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GamePlayerCharacter.h"

APlayerAirVent::APlayerAirVent()
{
	PrimaryActorTick.bCanEverTick = false;
	_bIsEntrance = false;

	/*Arrow*/
	RootComponent = Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));

	/*Box*/
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetupAttachment(Arrow);
	Box->SetBoxExtent(FVector(20.43026f, 100.f, 100.f));
	Box->SetRelativeLocation(FVector(-150.f, 0.f, 0.f));
	Box->ShapeColor = FColor::Orange;
}

void APlayerAirVent::BeginPlay()
{
	//이벤트 등록
	Box->OnComponentBeginOverlap.AddDynamic(this, &APlayerAirVent::BeginOverlap);

	//이미 충돌이 나 있었을 때의 처리
	TArray<AActor*> overlaps;
	Box->GetOverlappingActors(overlaps);

	for (AActor* a : overlaps)
	{
		AGamePlayerCharacter* player = Cast<AGamePlayerCharacter>(a);
		if (player && ::IsValid(player))
		{
			EnterVent(player);
			return;
		}
	}

}

void APlayerAirVent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGamePlayerCharacter* player = Cast<AGamePlayerCharacter>(OtherActor);
	if (player && ::IsValid(player))
	{
		EnterVent(player);
		return;
	}
}

void APlayerAirVent::EnterVent(AGamePlayerCharacter* player)
{
	if (player == nullptr || player && !::IsValid(player)) return;

	FVector playerDir = player->GetActorLocation() - Box->GetComponentLocation();
	FVector arrowDir = Arrow->GetComponentLocation() - Box->GetComponentLocation();
	float Dot = FVector::DotProduct(playerDir, arrowDir);

	//출입구의 역할을 한다면
	if (_bIsEntrance)
	{
		player->SetPlayerMode(player->PlayerMode == EPlayerMode::STANDING ? EPlayerMode::CREEPY : EPlayerMode::STANDING);

		//지정된 방향과 반대 방향에서 오고 있다면 환풍구를 탈출한다.
		if (Dot>=0)
		{
			player->SetActorLocation(Box->GetComponentLocation()-arrowDir.GetSafeNormal()*100.f);
		}
		//환풍구방향과 다른 방향에으로 들어왔다면, 환풍구에 들어간다.
		else
		{
			FRotator arrowRot = Arrow->GetComponentRotation();

			player->SetActorLocation(Arrow->GetComponentLocation());
			player->SetPlayerRotator(arrowRot);
		}

		return;
	}

	if (Dot >= 0) return;
	FRotator arrowRot = Arrow->GetComponentRotation();
	player->SetPlayerRotator(arrowRot);
}

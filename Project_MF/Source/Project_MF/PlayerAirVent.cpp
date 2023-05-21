#include "PlayerAirVent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GamePlayerCharacter.h"
#include "DrawDebugHelpers.h"

APlayerAirVent::APlayerAirVent()
{
	PrimaryActorTick.bCanEverTick = false;
	_bShowEnterRange = false;

	/*CDO*/
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(
		TEXT("/Engine/BasicShapes/Cone.Cone")
	);

	/*Box*/
	RootComponent = Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->ShapeColor = FColor::Orange;
	Box->SetBoxExtent(FVector(20.f, 100.f, 100.f));

	/*Arrow*/
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	Arrow->SetupAttachment(Box);
	Arrow->ArrowLength = 46.f;
	Arrow->ArrowSize = 3.8f;
	Arrow->SetRelativeLocation(FVector(150.f, 0.f, 0.f));

	/*Standing L*/
	LStandingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_STANDING"));
	LStandingMesh->SetupAttachment(Box);
	LStandingMesh->SetRelativeScale3D(FVector(.5f, .5f, .5f));
	LStandingMesh->SetRelativeLocationAndRotation(FVector(-25.f, -56.f, -22.f), FRotator(-85.f, -88.26f, -5.f));
	LStandingMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LStandingMesh->bHiddenInGame = true;

	RStandingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_STANDING"));
	RStandingMesh->SetupAttachment(Box);
	RStandingMesh->SetRelativeScale3D(FVector(.5f, .5f, .5f));
	RStandingMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RStandingMesh->SetRelativeLocationAndRotation(FVector(60.f, 58.f, -20.f), FRotator(90.f, 0.f, 101.f));
	RStandingMesh->bHiddenInGame = true;

	if (MESH.Succeeded())
	{
		LStandingMesh->SetStaticMesh(MESH.Object);
		RStandingMesh->SetStaticMesh(MESH.Object);
	}

}

void APlayerAirVent::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (LStandingMesh)
	{
		DrawDebugLine(
			GetWorld(),
			LStandingMesh->GetComponentLocation(),
			LStandingMesh->GetComponentLocation() + LStandingMesh->GetUpVector() * 60.f,
			FColor::Red
		);
	}

}

void APlayerAirVent::BeginPlay()
{
	Super::BeginPlay();

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
		_Player = player;
		EnterVent(player);
		return;
	}
}

void APlayerAirVent::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGamePlayerCharacter* player = Cast<AGamePlayerCharacter>(OtherActor);
	if (player && ::IsValid(player))
	{
		_Player.Reset();
		return;
	}
}

FVector APlayerAirVent::GetFinalEnterLocation() const 
{ 
	if (Arrow) return Arrow->GetComponentLocation() - GetActorUpVector() * 50.f; 
	return FVector::ZeroVector; 
}

#if WITH_EDITOR
void APlayerAirVent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FString changed = PropertyChangedEvent.GetPropertyName().ToString();

	if (changed=="_bShowEnterRange")
	{
		Box->bHiddenInGame = _bShowEnterRange;
	}
}
#endif

void APlayerAirVent::GetStandingHandInfo(EStandingHandType type, FVector& outLocation, FRotator& outRotator) const
{
	UStaticMeshComponent* target = (type == EStandingHandType::DOWN_LEFT ? LStandingMesh : RStandingMesh);
	if (target == nullptr || !::IsValid(target)) return;

	FHitResult result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	if (_Player.IsValid()) params.AddIgnoredActor(_Player.Get());

	bool ret = GetWorld()->LineTraceSingleByChannel(
		result,
		target->GetComponentLocation(),
		target->GetComponentLocation() + target->GetUpVector() * 300.f,
		ECollisionChannel::ECC_Visibility,
		params
	);

	if (ret)
	{
		outLocation = result.Location;

		if (type==EStandingHandType::DOWN_RIGHT)
		{
			FVector rightCross = -FVector::CrossProduct(result.Normal, FVector::DownVector);
			FVector upCross = -FVector::CrossProduct(result.Normal, rightCross);
			FVector resultCross = -rightCross-upCross;

			outRotator = result.Normal.Rotation();
		}
		else 
		{
			FVector rightCross = -FVector::CrossProduct(result.Normal, FVector::DownVector);
			FVector upCross = -FVector::CrossProduct(result.Normal, rightCross);
			FVector resultCross = upCross + rightCross;

			outRotator = resultCross.Rotation();
		}
	}

}

FVector APlayerAirVent::GetStandingHandLocation(EStandingHandType type) const
{
	switch (type){
		case(EStandingHandType::DOWN_LEFT):
			return LStandingMesh->GetComponentLocation();

		case(EStandingHandType::DOWN_RIGHT):
			return RStandingMesh->GetComponentLocation();
	}

	return FVector::ZeroVector;
}

FVector APlayerAirVent::GetAirVentFloorLocation() const
{
	FHitResult result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	if (_Player.IsValid()) params.AddIgnoredActor(_Player.Get());

	bool ret = GetWorld()->LineTraceSingleByChannel(
		result,
		Arrow->GetComponentLocation(),
		Arrow->GetComponentLocation() - Arrow->GetUpVector() * 400.f,
		ECollisionChannel::ECC_Visibility,
		params
	);

	if (ret)
	{
		return result.Location;
	}

	return FVector::ZeroVector;
}

FRotator APlayerAirVent::GetStandingHandRotation(EStandingHandType type) const
{
	switch (type) {
	case(EStandingHandType::DOWN_LEFT):
		return LStandingMesh->GetUpVector().Rotation();

	case(EStandingHandType::DOWN_RIGHT):
		return LStandingMesh->GetUpVector().Rotation();
	}

	return FRotator::ZeroRotator;
}

void APlayerAirVent::EnterVent(AGamePlayerCharacter* player)
{
	if (player == nullptr || player && !::IsValid(player)) return;

	FVector playerDir = player->GetActorLocation() - Box->GetComponentLocation();
	FVector arrowDir = Arrow->GetComponentLocation() - Box->GetComponentLocation();
	float Dot = FVector::DotProduct(playerDir, arrowDir);

	//환풍구 방향과 반대 방향에서 들어왔으면, 환풍구에 들어간다.
	if (Dot < 0)
	{
		player->SetCreepyMode(this, true);
	}
	else player->SetCreepyMode(this);

	//출입구의 역할을 한다면
	//if (_bIsEntrance)
	//{

	//	//지정된 방향과 반대 방향에서 오고 있다면 환풍구를 탈출한다.
	//	if (dot>=0)
	//	{
	//		player->setactorlocation(box->getcomponentlocation()-arrowdir.getsafenormal()*100.f);
	//	}
	//	//환풍구방향과 다른 방향에으로 들어왔다면, 환풍구에 들어간다.
	//	else
	//	{
	//		frotator arrowrot = arrow->getcomponentrotation();

	//		//player->setactorlocation(arrow->getcomponentlocation());
	//		//player->setplayerrotator(arrowrot);
	//	}

	//	return;
	//}
	//FRotator arrowRot = Arrow->GetComponentRotation();
	//player->SetPlayerRotator(arrowRot);
}

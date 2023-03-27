// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	//SphereComponent
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("awd"));
	Sphere->SetSphereRadius(300.f);
	Sphere->SetGenerateOverlapEvents(true);

	//Static_Mesh
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("visual"));
	mesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MESH(TEXT("/Game/Resource/PlayerCharacter/Meshs/Character_arm.Character_arm"));
	if (MESH.Succeeded())
	{
		mesh->SetSkeletalMesh(MESH.Object);
		mesh->SetRelativeLocation(FVector::ZeroVector);
		mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//GetOwner()->SetActorEnableCollision(true);
	if (GetOwner() && ::IsValid(GetOwner()))
	{
		GetOwner()->SetActorEnableCollision(true);
	}

	//bluePrint
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerCharacterBlueprint"));
	if (ANIM.Succeeded())
	{
		mesh->SetAnimInstanceClass(ANIM.Class);
	}

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATestActor::OnHit2);
}

void ATestActor::OnHit2(UPrimitiveComponent* OverlappedComponent, 
						AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, 
						bool bFromSweep, 
						const FHitResult& SweepResult )
{
	//UE_LOG(LogTemp, Warning, TEXT("충돌함!!!: %s"), OverlappedComponent->GetSub);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//직접 충돌로직 만들어본다!
	//FHitResult result;
	//FCollisionQueryParams params(NAME_None, false, this);
	//FVector start = GetActorLocation();

	//if (GetWorld()->SweepSingleByChannel(
	//	result, start, start, FQuat::Identity, 
	//	ECollisionChannel::ECC_Visibility, 
	//	FCollisionShape::MakeSphere(500.f),params ))
	//{
	//	AActor* hit = result.GetActor();
	//	if (hit==nullptr || !::IsValid(hit)) return;
	//	UE_LOG(LogTemp, Warning, TEXT("%s가 %s와 충돌함!!"), *GetActorLabel(), *hit->GetActorLabel())

	//}

}


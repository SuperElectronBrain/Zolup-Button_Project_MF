// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActorObject.h"
#include "Components/SphereComponent.h"
#include "MagneticComponent.h"
#include "MagneticFieldEffectComponent.h"

// Sets default values
ATestActorObject::ATestActorObject()
{
	PrimaryActorTick.bCanEverTick = true;

	/*Sphere*/
	RootComponent = Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	/**Effect*/
	FieldEffect = CreateDefaultSubobject<UMagneticFieldEffectComponent>(TEXT("EFFECT"));
	FieldEffect->SetupAttachment(RootComponent);
}

void ATestActorObject::BeginPlay()
{
	Super::BeginPlay();
}

void ATestActorObject::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("leftTime: %f"), leftTime)
	if (leftTime<=0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("적용됨."))
		const EMagneticType currType = FieldEffect->GetFieldMagneticType();

		switch (type) {
			case(0): 
				FieldEffect->SetMagneticFieldInfo(EMagneticType::S, 200.f);
				break;

			case(1):
				FieldEffect->SetMagneticFieldInfo(EMagneticType::NONE, 300.f);
				break;
		}

		leftTime = 10.f;
		type++;
		if (type > 1) type = 0;
	}

	leftTime -= DeltaTime;
}



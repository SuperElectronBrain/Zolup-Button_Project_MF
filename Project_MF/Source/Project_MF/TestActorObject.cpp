// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActorObject.h"
#include "MagneticSenserComponent.h"
#include "MagSenserEffect_EnchantComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATestActorObject::ATestActorObject()
{
	PrimaryActorTick.bCanEverTick = false;

	/*Sphere*/
	RootComponent = Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	/*Senser*/
	Senser = CreateDefaultSubobject<UMagneticSenserComponent>(TEXT("SENSER"));
	Senser->SetupAttachment(Sphere);
	
	/*Box*/
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetupAttachment(Senser);

	/*Box*/
	Box2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX2"));
	Box2->SetupAttachment(Senser);

	/*Effect*/
	Effect = CreateDefaultSubobject<UMagSenserEffect_EnchantComponent>(TEXT("EFFECT"));
	Effect->SetupAttachment(Senser);
}



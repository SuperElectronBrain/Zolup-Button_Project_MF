// Fill out your copyright notice in the Description page of Project Settings.


#include "CanvasActor.h"

// Sets default values
ACanvasActor::ACanvasActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	RootComponent = SceneComponent;
}

// Called when the game starts or when spawned
void ACanvasActor::BeginPlay()
{
	Super::BeginPlay();

	if (::IsValid(CanvasClass)== true)
	{
		CanvasInstance = CreateWidget<UUserWidget>(GetWorld(), CanvasClass);
		CanvasInstance->AddToViewport();
	}
}

// Called every frame
void ACanvasActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


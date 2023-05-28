// Fill out your copyright notice in the Description page of Project Settings.


#include "EditLevelMFActorManagementActor.h"

// Sets default values
AEditLevelMFActorManagementActor::AEditLevelMFActorManagementActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEditLevelMFActorManagementActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEditLevelMFActorManagementActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEditLevelMFActorManagementActor::SpawnMFActor()
{
	//MFActorsArray.Add(GetWorld()->SpawnActor<AMFActor>(AMFActor::StaticClass(), FVector(ActorCount * 100.0f, 0.0f, 0.0f), FRotator::ZeroRotator));
	ActorCount = ActorCount + 1;
}


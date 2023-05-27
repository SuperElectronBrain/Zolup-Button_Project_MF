// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "MFActor.h"
#include "EditLevelMFActorManagementActor.generated.h"

UCLASS()
class PROJECT_MF_API AEditLevelMFActorManagementActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY() int32 ActorCount;
	//UPROPERTY() TArray<AMFActor*> MFActorsArray;

public:	
	// Sets default values for this actor's properties
	AEditLevelMFActorManagementActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void SpawnMFActor();
};

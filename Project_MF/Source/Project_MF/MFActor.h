// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MFActor.generated.h"

UCLASS()
class PROJECT_MF_API AMFActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY() UStaticMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties
	AMFActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION() UStaticMeshComponent* GetMesh();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

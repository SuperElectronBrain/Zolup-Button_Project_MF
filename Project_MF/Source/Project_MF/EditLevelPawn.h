// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EditLevelMFActorManagementActor.h"
#include "EditLevelPawn.generated.h"

UCLASS()
class PROJECT_MF_API AEditLevelPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY() AEditLevelMFActorManagementActor* EditLevelMFActorManagementActor;

protected:
	UPROPERTY() USceneComponent* DefaultComponent;
	UPROPERTY() UFloatingPawnMovement* Movement;

private:
	UFUNCTION() void SpawnMFActor();

public:
	// Sets default values for this pawn's properties
	AEditLevelPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION() void VerticalMovement(float param);
	UFUNCTION() void HorizontalMovement(float param);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() void SetEditLevelMFActorManagementActor(AEditLevelMFActorManagementActor* param);
};

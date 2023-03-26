// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameLevelCharacter.generated.h"

UCLASS()
class PROJECT_MF_API AGameLevelCharacter : public ACharacter
{
	GENERATED_BODY()

private:

protected:
	UPROPERTY() UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AGameLevelCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

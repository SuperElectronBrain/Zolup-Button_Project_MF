// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PowerExecutionComponent.h"
#include "PowerMovementComponent.generated.h"


UCLASS()
class PROJECT_MF_API UPowerMovementComponent : public USceneComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true)) AActor* ObserveTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) float ActingRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) float ActingSpeed;
	UPROPERTY() float CurrentMovement;
	UPROPERTY() bool bActingState;
public:	
	// Sets default values for this component's properties
	UPowerMovementComponent();

public:	
	UFUNCTION() void StartAction();
	UFUNCTION() void EndAction();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "PowerLightControlComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerLightControlComponent : public UPowerMovementComponent
{
	GENERATED_BODY()

private:
	/** It works in reverse. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool ReversAction;
	/** When disabled, it does nothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool NonReversibleAction;
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPowerLightControlComponent();

	UFUNCTION() virtual void Action(float DeltaTime);
};

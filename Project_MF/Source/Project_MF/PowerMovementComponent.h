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

public:
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerMovementComponent, Meta = (AllowPrivateAccess = true)) TWeakObjectPtr<AActor> ObserveTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerMovementComponent, Meta = (AllowPrivateAccess = true)) float ActingRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerMovementComponent, Meta = (AllowPrivateAccess = true)) float ActingSpeed;
	UPROPERTY() float CurrentMovement;
	UPROPERTY() bool bActingState;
	UPROPERTY() TWeakObjectPtr<UPowerComponent> ObserveTargetExecutionComponent;

private:	

protected:
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UPowerMovementComponent();
	UFUNCTION() void StartAction();
	UFUNCTION() void EndAction();
};

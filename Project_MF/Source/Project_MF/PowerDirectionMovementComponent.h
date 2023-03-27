// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "PowerDirectionMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerDirectionMovementComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
	
private:
#if WITH_EDITORONLY_DATA
	UPROPERTY() UArrowComponent* ArrowComponent;
#endif
	UPROPERTY() FVector OriginPosition;

public:
	UPowerDirectionMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};

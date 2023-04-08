// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "PowerRotationMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerRotationMovementComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
	
private:
#if WITH_EDITORONLY_DATA
	UPROPERTY() UArrowComponent* ArrowComponent;
#endif
	UPROPERTY() FVector OriginNormalVector;
protected:
	virtual void BeginPlay() override;

public:
	UPowerRotationMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION() virtual void Action(float DeltaTime);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "PowerObjectSpawnerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerObjectSpawnerComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY() TWeakObjectPtr<UArrowComponent> ArrowComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TSubclassOf<AActor> OriginActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool OneTime;
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPowerObjectSpawnerComponent();

	UFUNCTION() virtual void Action(float DeltaTime);
};

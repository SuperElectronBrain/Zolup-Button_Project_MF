// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerMovementComponent.h"
#include "MovementRegistComponent.generated.h"


UCLASS()
class PROJECT_MF_API UMovementRegistComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY() TArray<UPowerMovementComponent*> MovementComponents;

public:	
	// Sets default values for this component's properties
	UMovementRegistComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PowerMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MF_API UPowerMovementComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) float ActingRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) float ActingSpeed;
	UPROPERTY() FVector OriginPosition;
	UPROPERTY() float CurrentMovement;
	UPROPERTY() bool bActingState;

public:	
	// Sets default values for this component's properties
	UPowerMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void StartAction();
	UFUNCTION() void EndAction();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PowerGenerateComponent.h"
#include "Engine/EngineTypes.h"
#include "PowerSensorComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerReceiver), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerSensorComponent : public UBoxComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) AActor* ReceivingTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) float MinimumWeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool PlayerOnly;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool ReversSignal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool NonReversibleSignal;
	UPROPERTY() TWeakObjectPtr<UPowerGenerateComponent> ReceivingTargetGenerateComponent;
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPowerSensorComponent();
};

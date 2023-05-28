// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PowerGenerateComponent.h"
#include "GameMapSectionComponent.h"
#include "PowerMapDamageSensorComponent.generated.h"


UCLASS(ClassGroup = (PowerReceiver), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerMapDamageSensorComponent : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TWeakObjectPtr<AActor> ObserveTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TWeakObjectPtr<AActor> ReceivingTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) int32 TriggerCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool ReversSignal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool NonReversibleSignal;
	UPROPERTY() TWeakObjectPtr<UGameMapSectionComponent> ObserveTargetGameMapSectionComponent;
	UPROPERTY() TWeakObjectPtr<UPowerComponent> ReceivingTargetGenerateComponent;
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Sets default values for this component's properties
	UPowerMapDamageSensorComponent();
};
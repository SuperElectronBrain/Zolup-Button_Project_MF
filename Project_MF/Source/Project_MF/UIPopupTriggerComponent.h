// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "UIPopupTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerReceiver), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UUIPopupTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool OneTime;
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UUIPopupTriggerComponent();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "MFAudioComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UMFAudioComponent : public UAudioComponent
{
	GENERATED_BODY()

private:
protected:
public:

private:
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UMFAudioComponent();
};

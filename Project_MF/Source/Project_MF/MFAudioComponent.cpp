// Fill out your copyright notice in the Description page of Project Settings.


#include "MFAudioComponent.h"

UMFAudioComponent::UMFAudioComponent()
{
}

void UMFAudioComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMFAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

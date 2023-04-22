// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "UIPopupTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerReceiver), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UUIPopupTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Meta = (AllowPrivateAccess = true)) TSubclassOf<class UUserWidget> CanvasClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool OneTime;

public:
	UPROPERTY() UUserWidget* CanvasInstance;

private:
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UUIPopupTriggerComponent();
};

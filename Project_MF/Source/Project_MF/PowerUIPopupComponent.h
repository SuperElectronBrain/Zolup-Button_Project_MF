// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "PowerUIPopupComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerUIPopupComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Meta = (AllowPrivateAccess = true)) TSubclassOf<class UUserWidget> UMGClass;
	/** It works in reverse. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool ReversAction;
	/** When disabled, it does nothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool NonReversibleAction;

public:
	UPROPERTY() UUserWidget* UMGInstance;

private:
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPowerUIPopupComponent();

	UFUNCTION() virtual void Action(float DeltaTime);
};

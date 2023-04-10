// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "PowerDirectionMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerDirectionMovementComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
	
private:
#if WITH_EDITORONLY_DATA
	UPROPERTY() UArrowComponent* ArrowComponent;
#endif
	UPROPERTY() FVector OriginPosition;
	/**
	* When activated, it moves infinitely.
	* WARNING - When disabled, it may not be able to return to original state.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool UnlimitedMovement;
	/** When disabled, it does nothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool NonReversibleMovement;

public:
	UPowerDirectionMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Called every frame

	UFUNCTION() virtual void Action(float DeltaTime);

};

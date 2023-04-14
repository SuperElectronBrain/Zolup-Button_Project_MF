// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "PowerRotationMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerRotationMovementComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
	
private:
//#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) UArrowComponent* ArrowComponent;
//#endif
	/**
	* When activated, it moves infinitely.
	* WARNING - When disabled, it may not be able to return to original state.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool UnlimitedMovement;
	/** When disabled, it does nothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool NonReversibleMovement;
	//UPROPERTY() FVector OriginNormalVector;
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPowerRotationMovementComponent();

	UFUNCTION() virtual void Action(float DeltaTime);
};

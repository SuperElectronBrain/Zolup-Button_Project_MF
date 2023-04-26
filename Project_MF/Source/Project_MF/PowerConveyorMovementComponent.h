// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "PowerConveyorMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerConveyorMovementComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
	
private:
//#if WITH_EDITORONLY_DATA
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) UArrowComponent* ArrowComponent;
	UPROPERTY() TWeakObjectPtr<UArrowComponent> ArrowComponent;

	//#endif
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	UPROPERTY() UBoxComponent* Trigger;
	//UPROPERTY() UBoxComponent* Collider;
	UPROPERTY() TArray<AActor*> MovableTargets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool PhysicsMovement;

	//UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;

	UFUNCTION() virtual void Action(float DeltaTime);

public:
	UPowerConveyorMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

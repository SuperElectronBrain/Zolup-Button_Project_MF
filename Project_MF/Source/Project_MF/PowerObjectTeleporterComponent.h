// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "PowerObjectTeleporterComponent.generated.h"

UENUM()
enum EPowerActingOption
{
	None UMETA(DisplayName = "It works anytime"),
	PlayerIgnore UMETA(DisplayName = "Except for the Player"),
	PlayerOnly UMETA(DisplayName = "Only works for Players"),
};

/**
 * 
 */
UCLASS(ClassGroup = (PowerMovement), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerObjectTeleporterComponent : public UPowerMovementComponent
{
	GENERATED_BODY()
private:
	UPROPERTY() TWeakObjectPtr<UArrowComponent> ArrowComponent;
	UPROPERTY() TWeakObjectPtr<UBoxComponent> BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) EPowerActingOption ActingOption;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) int32 ActingTimes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) bool UnlimitedActing;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPowerObjectTeleporterComponent();

	UFUNCTION() virtual void Action(float DeltaTime);
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

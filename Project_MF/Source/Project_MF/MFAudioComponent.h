// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "MFAudioComponent.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FCollisionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() TWeakObjectPtr<AActor> HitActor;
	UPROPERTY() int32 HitCount;
	UPROPERTY() int32 TickCount;

	FCollisionData(AActor *Actor = nullptr, int32 Value1 = 0, int32 Value2 = 0) : HitActor(Actor), HitCount(Value1), TickCount(Value2) {}
};

USTRUCT(Atomic, BlueprintType)
struct FVolumeMultiplySetting
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString MaterialType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<USoundBase> VariationSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float VolumeMultiply;
};
/**
 * 
 */
UCLASS(ClassGroup = (MFComponent), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UMFAudioComponent : public UAudioComponent
{
	GENERATED_BODY()

private:
	UPROPERTY() TArray<FCollisionData> HitActors;
protected:
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) FString MaterialType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TArray<FVolumeMultiplySetting> VolumeMultiplySetting;

private:
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	virtual void OnCollisionEnter(AActor* Collision);
	virtual void OnCollisionExit(AActor* Collision);


public:
	UMFAudioComponent();
};

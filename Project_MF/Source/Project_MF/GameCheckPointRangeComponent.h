// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameCheckPointRangeComponent.generated.h"

UENUM()
enum class EHitCheckPointRangeApplyTiming
{
	APPLY_IMMEDIATELY,
	APPLY_AFTER_UI_FADEOUT,
};

UENUM()
enum class EHitCheckPointRangeApplyType
{
	MOVE_TO_CHECKPOINT,
	MOVE_TO_LAST_CHECKPOINT,
	SAVE_CHECKPOINT
};

UENUM()
enum class EHitCheckPointRangeApplyAfterType
{
	NONE,
	DESTROY_THIS
};

class UGameMapSectionComponent;

/**
 * 
 */
UCLASS(ClassGroup = (GameMapSection), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UGameCheckPointRangeComponent final : public UBoxComponent
{
	GENERATED_BODY()

public:
	////////////////////
	/// Constructor ////
	////////////////////
	UGameCheckPointRangeComponent();
	
private:
	////////////////////////
	/// Override methods ///
	////////////////////////
	virtual void BeginPlay() override;
	virtual bool CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const override { return false; }

	/////////////////////////
	//// Private methods ////
	/////////////////////////
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ApplyRogic(AActor* actor);

	//////////////////////////////
	/// Components and fields ////
	//////////////////////////////
	UPROPERTY()
	UGameMapSectionComponent* Section;

	UPROPERTY(EditAnywhere, BlueprintReadwrite,  Category = CheckPointRange, Meta = (AllowPrivateAccess = true))
	AActor* CheckPoint;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = CheckPointRange, Meta = (AllowPrivateAccess = true))
	TArray<AActor*> ApplyTarget;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = CheckPointRange, Meta = (AllowPrivateAccess = true))
	EHitCheckPointRangeApplyTiming HitApplyTiming;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = CheckPointRange, Meta = (AllowPrivateAccess = true))
	EHitCheckPointRangeApplyType HitApplyType;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = CheckPointRange, Meta = (AllowPrivateAccess = true))
	EHitCheckPointRangeApplyAfterType HitApplyAfterType;
};


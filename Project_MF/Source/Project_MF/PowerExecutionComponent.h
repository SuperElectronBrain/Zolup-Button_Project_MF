// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerComponent.h"
#include "PowerExecutionComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Power), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerExecutionComponent : public UPowerComponent
{
	GENERATED_BODY()
	
private:
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) UStaticMeshComponent* Mesh;
	//UPROPERTY() UBoxComponent* Trigger;
	UPROPERTY() UBoxComponent* Collider;
	UPROPERTY() int32 MaterialIndexNum;
	void UpdateMaterialColor();

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	virtual void SetPowerState(bool param, bool IsGenerator = false) override;

public:
	UPowerExecutionComponent();

	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

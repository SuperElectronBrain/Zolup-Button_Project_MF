// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerComponent.h"
#include "PowerGenerateComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Power), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UPowerGenerateComponent : public UPowerComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY() /*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))*/ UStaticMeshComponent* Mesh;
	UPROPERTY() /*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))*/ UBoxComponent* Collider;
	UPROPERTY() UBoxComponent* Trigger;
	void UpdateMaterialColor();

protected:
	virtual void BeginPlay() override;

	virtual void SetPowerState(bool param, bool IsGenerator = false) override;

public:
	UPowerGenerateComponent();

	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

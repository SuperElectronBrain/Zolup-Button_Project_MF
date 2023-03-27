// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PowerComponent.h"
#include "Components/BoxComponent.h"
#include "PowerConnectionComponent.generated.h"


UCLASS( ClassGroup=(Power), meta=(BlueprintSpawnableComponent) )
class PROJECT_MF_API UPowerConnectionComponent : public UPowerComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TArray<UStaticMeshComponent*> Meshs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TArray<UBoxComponent*> Colliders;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TArray<UBoxComponent*> Triggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) int32 ObjectLength;

public:	
	// Sets default values for this component's properties
	UPowerConnectionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
#if WITH_EDITOR
	virtual void PostInitProperties() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION() void UpdateMaterialColor();

	UFUNCTION(BlueprintCallable) void SetObjectLength(int32 param);
	UFUNCTION(BlueprintCallable) virtual void SetTriggerSize(int32 param) override;

	UFUNCTION() virtual void SetPowerState(bool param, bool IsGenerator = false) override;

	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

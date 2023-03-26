// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "PowerComponent.generated.h"

UCLASS()// ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MF_API UPowerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) UStaticMesh* MeshOrigin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) UMaterial* MaterialOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) int32 TriggerSize;
	UPROPERTY(VisibleAnywhere) bool bPowerState;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetTriggerSize(int32 param);
	virtual void SetPowerState(bool param, bool IsGenerator = false);
};

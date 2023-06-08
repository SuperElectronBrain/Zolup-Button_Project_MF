// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MFAudioComponent.h"
#include "MFCollisionDamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MF_API UMFCollisionDamageComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY() TArray<FCollisionData> HitActors;

public:	
	// Sets default values for this component's properties
	UMFCollisionDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	virtual void OnCollisionEnter(AActor* Collision);
	virtual void OnCollisionExit(AActor* Collision);
};

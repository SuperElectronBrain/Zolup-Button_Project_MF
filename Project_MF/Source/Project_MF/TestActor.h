// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "MagneticComponent.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class PROJECT_MF_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit2(	UPrimitiveComponent* OverlappedComponent, 
					AActor* OtherActor, 
					UPrimitiveComponent* OtherComp, 
					int32 OtherBodyIndex, 
					bool bFromSweep, 
					const FHitResult& SweepResult
				);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category=Physics, Meta=(AllowPrivateAccess=true))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, Category = Visual, Meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* mesh;

};

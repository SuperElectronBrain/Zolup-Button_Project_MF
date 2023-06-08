// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActorObject.generated.h"

class UMagneticSenserComponent;
class UMagSenserEffect_EnchantComponent;
class UBoxComponent;
class USphereComponent;
class UMagneticFieldEffectComponent;

UCLASS()
class PROJECT_MF_API ATestActorObject : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	ATestActorObject();

private:
	float leftTime = 10.f;
	int type = 0;

	virtual void BeginPlay() override;
	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;


	UPROPERTY(VisibleAnywhere, Category = Test, Meta = (AllowPrivateAccess = true))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, Category = Test, Meta = (AllowPrivateAccess = true))
	UMagneticFieldEffectComponent* FieldEffect;
};

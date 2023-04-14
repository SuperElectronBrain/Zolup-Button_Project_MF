// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActorObject.generated.h"

class UMagneticSenserComponent;
class UMagSenserEffect_EnchantComponent;
class UBoxComponent;
class USphereComponent;

UCLASS()
class PROJECT_MF_API ATestActorObject : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	ATestActorObject();

private:
	UPROPERTY(VisibleAnywhere, Category = Test, Meta = (AllowPrivateAccess = true))
	UMagneticSenserComponent* Senser;

	UPROPERTY(VisibleAnywhere, Category = Test, Meta = (AllowPrivateAccess = true))
	UMagSenserEffect_EnchantComponent* Effect;

	UPROPERTY(VisibleAnywhere, Category = Test, Meta = (AllowPrivateAccess = true))
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = Test, Meta = (AllowPrivateAccess = true))
	UBoxComponent* Box2;

	UPROPERTY(VisibleAnywhere, Category = Test, Meta = (AllowPrivateAccess = true))
	USphereComponent* Sphere;
};

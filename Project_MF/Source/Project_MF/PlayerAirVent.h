// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerAirVent.generated.h"

class UArrowComponent;
class UBoxComponent;
class AGamePlayerCharacter;

UCLASS()
class PROJECT_MF_API APlayerAirVent final : public AActor
{
	GENERATED_BODY()
	
public:	
	////////////////////////
	//// Constructor ///////
	////////////////////////
	APlayerAirVent();

private:
	////////////////////////
	/// Override methods ///
	///////////////////////
	virtual void BeginPlay() override;

	////////////////////////
	/// Private methods ////
	////////////////////////
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void EnterVent(AGamePlayerCharacter* player);

	//////////////////
	/// Components ///
	/////////////////
	UPROPERTY(VisibleAnywhere, Category=AirVent, Meta=(AllowPrivateAccess=true))
	UArrowComponent* Arrow;

	UPROPERTY()
	UBoxComponent* Box;

public:
	UPROPERTY(EditAnywhere, Category = AirVent)
	bool _bIsEntrance;

};

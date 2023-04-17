// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameCheckPointContainerComponent.generated.h"

UCLASS(ClassGroup = (GameMapSection), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UGameCheckPointContainerComponent final : public UActorComponent
{
	GENERATED_BODY()

public:	
	////////////////////
	/// Constructor ////
	////////////////////
	UGameCheckPointContainerComponent();

public:
	/////////////////////////////
	/// Fields And Components ///
	/////////////////////////////
	UPROPERTY(VisibleAnywhere, Category = CheckPoint)
	AActor* CheckPoint;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameMapCheckPointComponent.h"
#include "GameMapCheckPoint.generated.h"

//class UGameMapCheckPointComponent;

UCLASS()
class PROJECT_MF_API AGameMapCheckPoint final : public AActor
{
	GENERATED_BODY()
	
public:
	//////////////////////
	//// Constructor ////
	/////////////////////
	AGameMapCheckPoint();

private:
#if WITH_EDITORONLY_DATA
	///////////////////////////////
	/// Components And Fields /////
	//////////////////////////////
	UPROPERTY(VisibleAnywhere, Category=CheckPoint, Meta=(AllowPrivateAccess=true))
	UGameMapCheckPointComponent* Point;
#endif

};

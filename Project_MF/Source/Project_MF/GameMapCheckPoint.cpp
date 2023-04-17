// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMapCheckPoint.h"
#include "GameMapCheckPointComponent.h"

// Sets default values
AGameMapCheckPoint::AGameMapCheckPoint()
{
	PrimaryActorTick.bCanEverTick = false;
	
#if WITH_EDITOR
	RootComponent = Point = CreateDefaultSubobject<UGameMapCheckPointComponent>(TEXT("Point"));
#endif
}
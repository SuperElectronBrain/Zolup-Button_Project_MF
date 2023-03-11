// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelPawn.h"

// Sets default values
AMainLevelPawn::AMainLevelPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainLevelPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainLevelPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainLevelPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelCharacter.h"

// Sets default values
AGameLevelCharacter::AGameLevelCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	//Camera->SetupAttachment(GetCapsuleComponent());

}

// Called when the game starts or when spawned
void AGameLevelCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameLevelCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameLevelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


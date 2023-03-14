// Fill out your copyright notice in the Description page of Project Settings.


#include "EditLevelPawn.h"

// Sets default values
AEditLevelPawn::AEditLevelPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultComponent"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	RootComponent = DefaultComponent;
}

// Called when the game starts or when spawned
void AEditLevelPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEditLevelPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEditLevelPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Key_G"), EInputEvent::IE_Pressed, this, &AEditLevelPawn::SpawnMFActor);

	PlayerInputComponent->BindAxis(TEXT("VerticalMovement"), this, &AEditLevelPawn::VerticalMovement);
	PlayerInputComponent->BindAxis(TEXT("HorizontalMovement"), this, &AEditLevelPawn::HorizontalMovement);
}

void AEditLevelPawn::VerticalMovement(float param)
{
	AddMovementInput(GetActorForwardVector(), param);
}

void AEditLevelPawn::HorizontalMovement(float param)
{
	AddMovementInput(GetActorRightVector(), param);
}

void AEditLevelPawn::SpawnMFActor()
{
	if (EditLevelMFActorManagementActor != nullptr)
	{
		EditLevelMFActorManagementActor->SpawnMFActor();
	}
}

void AEditLevelPawn::SetEditLevelMFActorManagementActor(AEditLevelMFActorManagementActor* param)
{
	if (EditLevelMFActorManagementActor != param)
	{
		EditLevelMFActorManagementActor = param;
	}
}
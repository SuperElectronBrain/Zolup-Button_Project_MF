// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelGameMode.h"
#include "MainLevelPawn.h"
#include "MainLevelPawnController.h"

AMainLevelGameMode::AMainLevelGameMode()
{
	DefaultPawnClass = AMainLevelPawn::StaticClass();
	PlayerControllerClass = AMainLevelPawnController::StaticClass();
}
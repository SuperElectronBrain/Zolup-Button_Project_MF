// Fill out your copyright notice in the Description page of Project Settings.


#include "EditLevelGameMode.h"
#include "EditLevelPawn.h"
#include "EditLevelPawnController.h"

AEditLevelGameMode::AEditLevelGameMode()
{
	DefaultPawnClass = AEditLevelPawn::StaticClass();
	PlayerControllerClass = AEditLevelPawnController::StaticClass();
}

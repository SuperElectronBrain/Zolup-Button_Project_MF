// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerGameMode.h"
#include "GamePlayerCharacter.h"
//#include "PlayerCharacter.h"

ATestPlayerGameMode::ATestPlayerGameMode()
{
	DefaultPawnClass = AGamePlayerCharacter::StaticClass();
}

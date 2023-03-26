// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "EditLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API AEditLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
private:
	
protected:
	virtual void BeginPlay() override;

public:
	AEditLevelScriptActor();
};

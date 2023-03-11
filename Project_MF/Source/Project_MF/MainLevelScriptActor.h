// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, Category = UI) class UUserWidget* MainLevelUICanvasInstance;
protected:
	UPROPERTY(VisibleAnywhere, Category = UI) TSubclassOf<class UUserWidget> MainLevelUICanvasClass;
public:
	AMainLevelScriptActor();
protected:
	virtual void BeginPlay() override;
};

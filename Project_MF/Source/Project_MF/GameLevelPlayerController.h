// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameLevelPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API AGameLevelPlayerController final : public APlayerController
{
	GENERATED_BODY()
	
public:
	/////////////////////////////////
	////						 ///
	////	  Constructor	    ///
	///							///
	//////////////////////////////
	AGameLevelPlayerController();


	/////////////////////////////////
	////						 ///
	////	 Private methods     ///
	///							///
	//////////////////////////////
private:
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void ShowGameSettings();


	/////////////////////////////////
	////						 ///
	////  Fields and Components ///
	///							///
	//////////////////////////////
	TWeakObjectPtr<class UUIGameSettingsWidget> GameSettingsWidget;
	TWeakObjectPtr<class AGamePlayerCharacter> GamePlayerCharacter;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainLevelUICanvasWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UMainLevelUICanvasWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable) void GameStart();
	UFUNCTION(BlueprintCallable) void GameQuit();
	UFUNCTION(BlueprintCallable) void EnterEditMode();

	UPROPERTY() class UButton* GameStartButton;
	UPROPERTY() class UButton* GameQuitButton;
	UPROPERTY() class UButton* GameEditButton;

private:
	UFUNCTION() void OnStartButtonClicked();
	UFUNCTION() void OnQuitButtonClicked();
	UFUNCTION() void OnEditButtonClicked();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIStopTimerWidget.generated.h"

class UImage;
class IGameUIHandler;

UCLASS()
class PROJECT_MF_API UUIStopTimerWidget : public UUserWidget, public IGameUIHandler
{
	GENERATED_BODY()

	//////////////////////
	/// Public methods ///
	//////////////////////
public:
	void SetCurrTime(float newValue);
	void SetGoalTime(float newValue);

private:
	////////////////////////
	/// Override methods ///
	////////////////////////
	virtual void NativeOnInitialized() override;
	virtual float GetAlpha() const override;
	virtual void SetAlpha(float newAlpha) override;
	virtual FLinearColor GetColor() const override;
	virtual void SetColor(FLinearColor newColor) override;

	/////////////////////////////
	/// Fields And Components  //
	/////////////////////////////
	UPROPERTY(EditAnywhere, Category = StopTimerWidget, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* _ContentMaterial;

	UPROPERTY(EditAnywhere, Category = StopTimerWidget, Meta = (AllowPrivateAccess = true, ClampMin = 0.f))
	float GoalTime;

	UPROPERTY()
	UMaterialInstanceDynamic* _MaterialDynamic;

	UPROPERTY()
	UImage* ContentImage;
};

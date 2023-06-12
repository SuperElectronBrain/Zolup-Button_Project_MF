// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIHandler.h"
#include "UIGameSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UUIGameSettingsWidget : public UUserWidget, public IGameUIHandler
{
	GENERATED_BODY()
	

public:
	/**IGameUIHandler의 인터페이스 구현부입니다.*/
	virtual float GetAlpha() const override;
	virtual void SetAlpha(float newAlpha) override;

	virtual FLinearColor GetColor() const override;
	virtual void SetColor(FLinearColor newColor) override;
};

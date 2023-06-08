// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "GameUIHandler.h"
#include "HandlerImage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UHandlerImage : public UImage, public IGameUIHandler
{
	GENERATED_BODY()
	
public:
	virtual float GetAlpha() const override;
	virtual void SetAlpha(float newAlpha) override;

	virtual FLinearColor GetColor() const override;
	virtual void SetColor(FLinearColor newColor) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameUIHandler.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameUIHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_MF_API IGameUIHandler
{
	GENERATED_BODY()

public:
	virtual float GetAlpha() const = 0;
	virtual void SetAlpha(float newAlpha) = 0;

	virtual FLinearColor GetColor() const = 0;
	virtual void SetColor(FLinearColor newColor) = 0;

};

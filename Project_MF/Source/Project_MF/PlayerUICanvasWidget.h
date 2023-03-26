// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIMagneticInfoWidget.h"
#include "MagneticComponent.h"
#include "PlayerUICanvasWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UPlayerUICanvasWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	/*Construct*/
	virtual void NativeConstruct() override;

	void SetAnimColor(FColor color);
	UPlayerUIMagneticInfoWidget* GetMagneticInfoWidget() const { return _MagneticInfo; }

private:
	/*fields and Components*/
	UPROPERTY()
	UPlayerUIMagneticInfoWidget* _MagneticInfo;

	UPROPERTY()
	UImage* _AimImage;
	
};

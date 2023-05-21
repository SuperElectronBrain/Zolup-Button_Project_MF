// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUICanvasWidget.generated.h"

class UImage;
class UPlayerUIMagneticInfoWidget;
class UPlayerUIAimWidget;
/**
 * 
 */
UCLASS()
class PROJECT_MF_API UPlayerUICanvasWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	/*Construct*/
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void GetMagneticInfoWidget(TWeakObjectPtr<UPlayerUIMagneticInfoWidget>& outPtr) const;
	void GetAimWidget(TWeakObjectPtr<UPlayerUIAimWidget>& outPtr) const;

private:
	/*fields and Components*/
	UPROPERTY()
	UPlayerUIMagneticInfoWidget* _MagneticInfo;

	UPROPERTY()
	UPlayerUIAimWidget* _Aim;
	
};

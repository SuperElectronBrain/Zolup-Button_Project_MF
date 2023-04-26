// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUICanvasWidget.h"
#include "MagneticComponent.h"
#include "CustomGameInstance.h"

void UPlayerUICanvasWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	_MagneticInfo = Cast<UPlayerUIMagneticInfoWidget>(GetWidgetFromName(TEXT("MagneticInfo")));
	_AimImage = Cast<UImage>(GetWidgetFromName(TEXT("Aim")));
}

void UPlayerUICanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UPlayerUICanvasWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPlayerUICanvasWidget::SetAnimColor(FColor color)
{
	if (_AimImage == nullptr || _MagneticInfo==nullptr) return;

	_AimImage->SetColorAndOpacity(color);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUICanvasWidget.h"
#include "MagneticComponent.h"

void UPlayerUICanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	_MagneticInfo = Cast<UPlayerUIMagneticInfoWidget>(GetWidgetFromName(TEXT("MagneticInfo")));
	_AimImage = Cast<UImage>(GetWidgetFromName(TEXT("Aim")));
}

void UPlayerUICanvasWidget::SetAnimColor(FColor color)
{
	if (_AimImage == nullptr || _MagneticInfo==nullptr) return;

	_AimImage->SetColorAndOpacity(color);
}
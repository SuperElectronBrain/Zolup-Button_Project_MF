// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUICanvasWidget.h"
#include "MagneticComponent.h"
#include "PlayerUIMagneticInfoWidget.h"
#include "PlayerUIAimWidget.h"
#include "CustomGameInstance.h"

void UPlayerUICanvasWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	_MagneticInfo = Cast<UPlayerUIMagneticInfoWidget>(GetWidgetFromName(TEXT("MagneticInfo")));
	_Aim = Cast<UPlayerUIAimWidget>(GetWidgetFromName(TEXT("PlayerUI_Aim")));
}

void UPlayerUICanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UPlayerUICanvasWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPlayerUICanvasWidget::GetMagneticInfoWidget(TWeakObjectPtr<UPlayerUIMagneticInfoWidget>& outPtr) const
{
	outPtr.Reset();
	outPtr = _MagneticInfo;
}

void UPlayerUICanvasWidget::GetAimWidget(TWeakObjectPtr<UPlayerUIAimWidget>& outPtr) const
{
	outPtr.Reset();
	outPtr = _Aim;
}
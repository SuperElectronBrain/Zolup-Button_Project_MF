// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUICanvasWidget.h"
#include "MagneticComponent.h"
#include "PlayerUIMagneticInfoWidget.h"
#include "PlayerUIAimWidget.h"
#include "PlayerUIBloodWidget.h"
#include "CustomGameInstance.h"
#include "HandlerImage.h"

void UPlayerUICanvasWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	_MagneticInfo = Cast<UPlayerUIMagneticInfoWidget>(GetWidgetFromName(TEXT("MagneticInfo")));
	_Aim = Cast<UPlayerUIAimWidget>(GetWidgetFromName(TEXT("PlayerUI_Aim")));
	_Blood = Cast<UPlayerUIBloodWidget>(GetWidgetFromName(TEXT("PlayerUI_Blood")));
	_ClimbAble = Cast<UHandlerImage>(GetWidgetFromName(TEXT("ClimbAble")));
	SetClimbAbleImgVisibility(false);
}

void UPlayerUICanvasWidget::SetClimbAbleImgVisibility(bool isVisible)
{
	if (::IsValid(_ClimbAble)==false) return;

	ESlateVisibility apply = (isVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	_ClimbAble->SetVisibility(apply);
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

void UPlayerUICanvasWidget::GetBloodEffectWidget(TWeakObjectPtr<UPlayerUIBloodWidget>& outPtr) const
{
	outPtr.Reset();
	outPtr = _Blood;
}
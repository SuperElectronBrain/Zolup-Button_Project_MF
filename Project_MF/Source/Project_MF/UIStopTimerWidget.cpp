// Fill out your copyright notice in the Description page of Project Settings.


#include "UIStopTimerWidget.h"
#include "Components/Image.h"

void UUIStopTimerWidget::NativeOnInitialized()
{
	//필요한 참조를 가져온다.
	ContentImage = Cast<UImage>(GetWidgetFromName(TEXT("Content")));
	GoalTime = 10.f;

	//머터리얼 인스턴스 생성.
	if (_ContentMaterial)
	{
		_MaterialDynamic = UMaterialInstanceDynamic::Create(_ContentMaterial, this);
	}

	//머터리얼 인스턴스를 적용한다.
	if (_MaterialDynamic && ContentImage)
	{
		ContentImage->SetBrushFromMaterial(_MaterialDynamic);
		_MaterialDynamic->SetScalarParameterValue(TEXT("CurrTime"), 0.f);
		_MaterialDynamic->SetScalarParameterValue(TEXT("GoalTime"), GoalTime);
	}
}

void UUIStopTimerWidget::SetCurrTime(float newValue)
{
	if (_MaterialDynamic)
	{
		_MaterialDynamic->SetScalarParameterValue(TEXT("CurrTime"), (newValue<0.f?0.f:newValue));
	}
}

void UUIStopTimerWidget::SetGoalTime(float newValue)
{
	if (_MaterialDynamic)
	{
		_MaterialDynamic->SetScalarParameterValue(TEXT("GoalTime"), (newValue < 0.f ? 0.f : newValue));
	}
}

float UUIStopTimerWidget::GetAlpha() const
{
	return ColorAndOpacity.A;
}
void UUIStopTimerWidget::SetAlpha(float newAlpha)
{
	FLinearColor color = ColorAndOpacity;
	color.A = FMath::Clamp(newAlpha, 0.f, 1.f);
	SetColorAndOpacity(color);
	ContentImage->SetColorAndOpacity(color);
}

FLinearColor UUIStopTimerWidget::GetColor() const
{
	return ColorAndOpacity;
}

void UUIStopTimerWidget::SetColor(FLinearColor newColor)
{
	SetColorAndOpacity(newColor);
 }
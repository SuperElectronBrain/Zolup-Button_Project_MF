// Fill out your copyright notice in the Description page of Project Settings.


#include "UIGameSettingsWidget.h"

float UUIGameSettingsWidget::GetAlpha() const
{
	return ColorAndOpacity.A;
}

void UUIGameSettingsWidget::SetAlpha(float newAlpha)
{
	FLinearColor Color = ColorAndOpacity;
	Color.A = newAlpha;
	SetColorAndOpacity(Color);
}

FLinearColor UUIGameSettingsWidget::GetColor() const
{
	return ColorAndOpacity;
}

void UUIGameSettingsWidget::SetColor(FLinearColor newColor)
{
	SetColorAndOpacity(newColor);
}

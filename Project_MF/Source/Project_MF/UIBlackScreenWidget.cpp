#include "UIBlackScreenWidget.h"

float UUIBlackScreenWidget::GetAlpha() const { return ColorAndOpacity.A; }
void UUIBlackScreenWidget::SetAlpha(float newAlpha)
{
	FLinearColor newColor = ColorAndOpacity;
	newColor.A = FMath::Clamp(newAlpha, 0.f, 1.f);
	SetColorAndOpacity(newColor);
}

FLinearColor UUIBlackScreenWidget::GetColor() const { return ColorAndOpacity; }
void UUIBlackScreenWidget::SetColor(FLinearColor newColor) { SetColorAndOpacity(newColor); }
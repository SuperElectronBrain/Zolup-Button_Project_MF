#include "HandlerImage.h"

float UHandlerImage::GetAlpha() const { return ColorAndOpacity.A; }
void UHandlerImage::SetAlpha(float newAlpha)
{
	FLinearColor newColor = ColorAndOpacity;
	newColor.A = FMath::Clamp(newAlpha, 0.f, 1.f);
	SetColorAndOpacity(newColor);
}

FLinearColor UHandlerImage::GetColor() const { return ColorAndOpacity; }
void UHandlerImage::SetColor(FLinearColor newColor) { SetColorAndOpacity(newColor); }
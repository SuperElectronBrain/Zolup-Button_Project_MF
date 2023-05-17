#include "PlayerUIAimWidget.h"
#include "MagneticComponent.h"

float UPlayerUIAimWidget::GetAlpha() const 
{
	return ColorAndOpacity.A;
}

void UPlayerUIAimWidget::SetAlpha(float newAlpha)
{
	FLinearColor color = ColorAndOpacity;
	color.A = newAlpha;

	SetColorAndOpacity(color);
}

FLinearColor UPlayerUIAimWidget::GetColor() const
{
	return ColorAndOpacity;
}

void UPlayerUIAimWidget::SetColor(FLinearColor newColor)
{
	SetColorAndOpacity(newColor);
}

void UPlayerUIAimWidget::SetAimUIByMagneticType(EMagneticType type)
{
	
}

void UPlayerUIAimWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPlayerUIAimWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerUIAimWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPlayerUIAimWidget::ChangeAnimProgress(float DeltaTime)
{

}


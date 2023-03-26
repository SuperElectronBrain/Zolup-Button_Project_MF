// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUIMagneticInfoWidget.h"

void UPlayerUIMagneticInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	_magL = Cast<UImage>(GetWidgetFromName(TEXT("MagnetL")));
	_magR = Cast<UImage>(GetWidgetFromName(TEXT("MagnetR")));

	//사용이 가능한 상태인지의 여부
	_bAvaliableImages = _magL != nullptr && _magR != nullptr;
	ClearInfo();
}

void UPlayerUIMagneticInfoWidget::ClearInfo()
{
	if (!_bAvaliableImages) return;
	
	FLinearColor clearColor(.0f, .0f, .0f, .0f);
	_magL->SetColorAndOpacity(clearColor);
	_magR->SetColorAndOpacity(clearColor);
}

void UPlayerUIMagneticInfoWidget::SetInfo(EMagneticType type1, EMagneticType type2)
{
	if (!_bAvaliableImages) return;

	FLinearColor clearColor(.0f, .0f, .0f, .0f);

	if (type1 == EMagneticType::NONE) _magL->SetColorAndOpacity(clearColor);
		else _magL->SetColorAndOpacity(UMagneticComponent::GetMagneticLinearColor(type1));

	if (type2 != EMagneticType::NONE) _magR->SetColorAndOpacity(clearColor);
		else _magR->SetColorAndOpacity(UMagneticComponent::GetMagneticLinearColor(type2));
}

void UPlayerUIMagneticInfoWidget::SetInfo(UMagneticComponent* t1, UMagneticComponent* t2=nullptr)
{
	if (!_bAvaliableImages) return;

	FLinearColor clearColor(.0f, .0f, .0f, .0f);
	EMagneticType type;

	if (t1 != nullptr && ::IsValid(t1))
	{
		type = t1->GetCurrentMagnetic();
		if (type == EMagneticType::NONE) _magL->SetColorAndOpacity(clearColor);
		else _magL->SetColorAndOpacity(UMagneticComponent::GetMagneticLinearColor(type));
	}

	if (t2 != nullptr && ::IsValid(t2))
	{
		type = t2->GetCurrentMagnetic();
		if (type == EMagneticType::NONE) _magR->SetColorAndOpacity(clearColor);
		else _magR->SetColorAndOpacity(UMagneticComponent::GetMagneticLinearColor(type));
	}


}
#include "PlayerUIMagneticInfoWidget.h"
#include "CustomGameInstance.h"
#include "HandlerImage.h"
#include "MagneticComponent.h"

void UPlayerUIMagneticInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	LLast = RLast = EMagneticType::NONE;

	_Instance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());
	_magL = Cast<UHandlerImage>(GetWidgetFromName(TEXT("MagnetL")));
	_magR = Cast<UHandlerImage>(GetWidgetFromName(TEXT("MagnetR")));

	//사용이 가능한 상태인지의 여부
	_bAvaliableImages = _magL != nullptr && _magR != nullptr;

	if (_bAvaliableImages)
	{
		LLast = RLast = EMagneticType::NONE;
		_magL->SetAlpha(0.f);
		_magR->SetAlpha(0.f);
	}
}

void UPlayerUIMagneticInfoWidget::ClearInfo()
{
	if (!_bAvaliableImages) return;

	LLast = RLast = EMagneticType::NONE;
	fadeOut(_magL, MAGINFO_FADEID_L);
	fadeOut(_magR, MAGINFO_FADEID_R);
}

void UPlayerUIMagneticInfoWidget::fadeIn(UHandlerImage* handler, int id)
{
	if (_Instance.IsValid())
	{
		_Instance->GetUIManager()->StopFadeInOut(id);
		_Instance->GetUIManager()->PlayFadeInOut(
			EFadeType::WHITE_TO_DARK,
			handler,
			MAGINFO_FADE_SECOND,
			0.f,
			0.f,
			0.f,
			0.f,
			0.f,
			id,
			handler->GetColor(),
			handler->GetColor(),
			true
		);
	}
}

void UPlayerUIMagneticInfoWidget::fadeOut(UHandlerImage* handler, int id)
{
	if (_Instance.IsValid())
	{
		_Instance->GetUIManager()->StopFadeInOut(id);
		_Instance->GetUIManager()->PlayFadeInOut(
			EFadeType::DARK_TO_WHITE,
			handler,
			0.f,
			MAGINFO_FADE_SECOND,
			1.f,
			0.f,
			0.f,
			0.f,
			id,
			handler->GetColor(),
			handler->GetColor(),
			true
		);
	}
}

void UPlayerUIMagneticInfoWidget::SetInfo(EMagneticType type1, EMagneticType type2)
{
	if (!_bAvaliableImages) return;

	FLinearColor clearColor(.0f, .0f, .0f, .0f);
	bool changeL = type1 != LLast;
	bool changeR = type2 != RLast;

	//왼쪽 
	if (changeL)
	{
		if (type1 == EMagneticType::NONE) fadeOut(_magL, MAGINFO_FADEID_L);
		else
		{
			_magL->SetColorAndOpacity(UMagneticComponent::GetMagneticEffectColor(type1, EMagneticEffectColorType::GRANT_EFFECT));
			fadeIn(_magL, MAGINFO_FADEID_L);
		}

		LLast = type1;
	}

	//오른쪽
	if (changeR)
	{
		if (type2 == EMagneticType::NONE) fadeOut(_magR, MAGINFO_FADEID_R);
		else
		{
			_magR->SetColorAndOpacity(UMagneticComponent::GetMagneticEffectColor(type1, EMagneticEffectColorType::GRANT_EFFECT));
			fadeIn(_magR, MAGINFO_FADEID_R);
		}

		RLast = type2;
	}
}

void UPlayerUIMagneticInfoWidget::SetInfo(UMagneticComponent* t1, UMagneticComponent* t2=nullptr)
{
	if (!_bAvaliableImages) return;

	FLinearColor clearColor(.0f, .0f, .0f, .0f);
	EMagneticType type;
	bool changeL = t1 ? t1->GetCurrentMagnetic() != LLast:false;
	bool changeR = t2 ? t2->GetCurrentMagnetic() != RLast:false;

	//왼쪽
	if (changeL)
	{
		type = t1->GetCurrentMagnetic();
		if (type == EMagneticType::NONE) fadeOut(_magL, MAGINFO_FADEID_L);
		else
		{
			_magL->SetColorAndOpacity(UMagneticComponent::GetMagneticEffectColor(type, EMagneticEffectColorType::GRANT_EFFECT));
			fadeIn(_magL, MAGINFO_FADEID_L);
		}

		LLast = type;
	}

	//오른쪽
	if (changeR)
	{
		type = t2->GetCurrentMagnetic();
		if (type == EMagneticType::NONE) fadeOut(_magR, MAGINFO_FADEID_R);
		else
		{
			_magR->SetColorAndOpacity(UMagneticComponent::GetMagneticEffectColor(type, EMagneticEffectColorType::GRANT_EFFECT));
			fadeIn(_magR, MAGINFO_FADEID_R);
		}

		RLast = type;
	}


}
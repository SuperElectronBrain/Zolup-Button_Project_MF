#include "PlayerUIAimWidget.h"
#include "MagneticComponent.h"
#include "Components/Image.h"
#include "CustomGameInstance.h"
#include "GameUIManager.h"
#include "HandlerImage.h"

UHandlerImage* FGivenImgInfo::GetImgByMagType() const
{ 
	return CurrType == EMagneticType::N ? RedImg : BlueImg; 
}

void FGivenImgInfo::SetImgOpacityByMagType()
{
	if (RedImg) RedImg->SetOpacity(CurrType == EMagneticType::N ? 1.f : 0.f);
	if (BlueImg) BlueImg->SetOpacity(CurrType == EMagneticType::S ? 1.f : 0.f);
}

void FGivenImgInfo::SetAllImgOpacityZero()
{
	if (RedImg) RedImg->SetOpacity(0.f);
	if (BlueImg) BlueImg->SetOpacity(0.f);
}

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

void UPlayerUIAimWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//GivenAnimProgress(_GivenInfoL, InDeltaTime);
}

void UPlayerUIAimWidget::SetAimUIByMagneticComp(UMagneticComponent* typeL, UMagneticComponent* typeR, EMagneticType playerType)
{
	EMagneticType t1 = ::IsValid(typeL) ? typeL->GetCurrentMagnetic() : EMagneticType::NONE;
	EMagneticType t2 = ::IsValid(typeR) ? typeR->GetCurrentMagnetic() : EMagneticType::NONE;

	SetAimUIByMagneticType(t1, t2, playerType);
}

void UPlayerUIAimWidget::PlayerGivenAnimProgress(float DeltaTime)
{



}

void UPlayerUIAimWidget::SetAimUIByMagneticType(EMagneticType typeL, EMagneticType typeR, EMagneticType playerType)
{
	bool bGivenLAddtive = _GivenInfoL.CurrType == EMagneticType::NONE && typeL != EMagneticType::NONE;
	bool bGivenLSubtract = _GivenInfoL.CurrType != EMagneticType::NONE && _GivenInfoL.CurrType != typeL;
	bool bGivenLEnd = _GivenInfoL.CurrType != EMagneticType::NONE && typeL == EMagneticType::NONE;

	bool bGivenRAddtive = _GivenInfoR.CurrType == EMagneticType::NONE && typeR != EMagneticType::NONE;
	bool bGivenRSubtract = _GivenInfoR.CurrType != EMagneticType::NONE && _GivenInfoR.CurrType != typeR;
	bool bGivenREnd = _GivenInfoR.CurrType != EMagneticType::NONE && typeR == EMagneticType::NONE;

	/*GivenL*/
	//공백에서의 추가
	if (bGivenLAddtive)
	{
		_GivenInfoL.NextType = EMagneticType::NONE;
		_GivenInfoL.SetAllImgOpacityZero();
		_GivenInfoL.CurrType = typeL;
		/*페이드 인*/
		if (_UIManager.IsValid())
		{
			_UIManager->StopFadeInOut(AIML_FADE_ID);
			_UIManager->PlayFadeInOut(
				EFadeType::WHITE_TO_DARK,
				_GivenInfoL.GetImgByMagType(),
				MagGivenApplySeconds,
				0.f,
				1.f,
				0.f,
				0.f,
				0.f,
				AIML_FADE_ID
			);
		}
	}
	else if(bGivenLSubtract)
	{
		/*페이드 아웃~인*/
		if (_UIManager.IsValid())
		{
			_UIManager->StopFadeInOut(AIML_FADE_ID);
			_UIManager->PlayFadeInOut(
				EFadeType::DARK_TO_WHITE,
				_GivenInfoL.GetImgByMagType(),
				0.f,
				MagGivenApplySeconds,
				1.f,
				0.f,
				0.f,
				0.f,
				AIML_FADE_ID,
				FLinearColor::White,
				FLinearColor::White,
				true
			);
		}

		_GivenInfoL.NextType = typeL;
	}


	/*GivenR*/
	//공백에서의 추가
	if (bGivenRAddtive)
	{
		_GivenInfoR.NextType = EMagneticType::NONE;
		_GivenInfoR.SetAllImgOpacityZero();
		_GivenInfoR.CurrType = typeR;

			/*페이드 인*/
			if (_UIManager.IsValid())
			{
				_UIManager->StopFadeInOut(AIMR_FADE_ID);
				_UIManager->PlayFadeInOut(
					EFadeType::WHITE_TO_DARK,
					_GivenInfoR.GetImgByMagType(),
					MagGivenApplySeconds,
					0.f,
					1.f,
					0.f,
					0.f,
					0.f,
					AIMR_FADE_ID
				);
			}
	}
	else if (bGivenRSubtract)
	{
			/*페이드 아웃~인*/
			if (_UIManager.IsValid())
			{
				_UIManager->StopFadeInOut(AIMR_FADE_ID);
				_UIManager->PlayFadeInOut(
					EFadeType::DARK_TO_WHITE,
					_GivenInfoR.GetImgByMagType(),
					0.f,
					MagGivenApplySeconds,
					1.f,
					0.f,
					0.f,
					0.f,
					AIMR_FADE_ID,
					FLinearColor::White,
					FLinearColor::White,
					true
				);
			}

		_GivenInfoR.NextType = typeR;
	}

}

void UPlayerUIAimWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*애니메이션에서 필요한 모든 참조를 가지고 온다.*/

	//GivenL 초기화
	_GivenInfoL.BlueImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("GivenL_Blue")));
	_GivenInfoL.RedImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("GivenL_Red")));
	_GivenInfoL.GoalTimeDiv = 1.f / MagGivenApplySeconds;
	if (_GivenInfoL.RedImg) _GivenInfoL.RedImg->SetOpacity(0.f);
	if (_GivenInfoL.BlueImg)
	{
		_GivenInfoL.OriginPos = _GivenInfoL.BlueImg->GetRenderTransform().Translation;
		_GivenInfoL.BlueImg->SetOpacity(0.f);
	}

	//GivenR 초기화
	_GivenInfoR.BlueImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("GivenR_Blue")));
	_GivenInfoR.RedImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("GivenR_Red")));
	_GivenInfoR.GoalTimeDiv = 1.f / MagGivenApplySeconds;
	if (_GivenInfoR.RedImg) _GivenInfoR.RedImg->SetOpacity(0.f);
	if (_GivenInfoR.BlueImg)
	{
		_GivenInfoR.OriginPos = _GivenInfoR.BlueImg->GetRenderTransform().Translation;
		_GivenInfoR.BlueImg->SetOpacity(0.f);
	}

	//PlayerGiven 초기화
	_PlayerCircle_Red = Cast<UImage>(GetWidgetFromName(TEXT("PlayerGivenCircle_Red")));
	_PlayerCircle_Blue = Cast<UImage>(GetWidgetFromName(TEXT("PlayerGivenCircle_Blue")));
	if (_PlayerCircle_Red) _PlayerCircle_Red->SetOpacity(0.f);
	if (_PlayerCircle_Blue) _PlayerCircle_Blue->SetOpacity(0.f);


	/*UIManager 초기화*/
	UCustomGameInstance* instance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());
	if (instance)
	{
		_UIManager = instance->GetUIManager();
	}
}

void UPlayerUIAimWidget::FadeChange(bool isDark, int id)
{
	/*GivenL*/
	if (id==AIML_FADE_ID)
	{
		/*알파가 0일 때,*/
		if (isDark==false) {
			_GivenInfoL.CurrType = _GivenInfoL.NextType;

			if (_GivenInfoL.NextType != EMagneticType::NONE && _UIManager.IsValid())
			{
				_UIManager->StopFadeInOut(AIML_FADE_ID);
				_UIManager->PlayFadeInOut(
					EFadeType::WHITE_TO_DARK,
					_GivenInfoL.GetImgByMagType(),
					MagGivenApplySeconds,
					0.f,
					1.f,
					0.f,
					0.f,
					0.f,
					AIML_FADE_ID
				);
			}

			_GivenInfoL.NextType = EMagneticType::NONE;
		}
	}

	/*GivenR*/
	if (id == AIMR_FADE_ID)
	{
		/*알파가 0일 때,*/
		if (isDark == false) {
			_GivenInfoR.CurrType = _GivenInfoR.NextType;

			if (_GivenInfoR.NextType != EMagneticType::NONE && _UIManager.IsValid())
			{
				_UIManager->StopFadeInOut(AIMR_FADE_ID);
				_UIManager->PlayFadeInOut(
					EFadeType::WHITE_TO_DARK,
					_GivenInfoR.GetImgByMagType(),
					MagGivenApplySeconds,
					0.f,
					1.f,
					0.f,
					0.f,
					0.f,
					AIMR_FADE_ID
				);
			}

			_GivenInfoR.NextType = EMagneticType::NONE;
		}
	}
}

void UPlayerUIAimWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*페이드 델리게이트 추가*/
	if (_UIManager.IsValid())
		_FadeDelegateHandle = _UIManager->OnUIFadeChange.AddUObject(this, &UPlayerUIAimWidget::FadeChange);

}

void UPlayerUIAimWidget::NativeDestruct()
{
	Super::NativeDestruct();

	/*페이드 델리게이트 제거*/
	if (_UIManager.IsValid())
		_UIManager->OnUIFadeChange.Remove(_FadeDelegateHandle);
}



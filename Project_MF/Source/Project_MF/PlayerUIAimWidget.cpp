#include "PlayerUIAimWidget.h"
#include "MagneticComponent.h"
#include "Components/Image.h"
#include "CustomGameInstance.h"
#include "GameUIManager.h"
#include "HandlerImage.h"

UHandlerImage* FAimImgInfo::GetImgByMagType() const
{ 
	return CurrType == EMagneticType::N ? RedImg : BlueImg; 
}

void FAimImgInfo::SetImgVisibleByMagType()
{
	if (RedImg) RedImg->SetOpacity(CurrType == EMagneticType::N ? 1.f:0.f);
	if (BlueImg) BlueImg->SetOpacity(CurrType == EMagneticType::S ? 1.f:0.f);

}

void FAimImgInfo::SetAllImgOpacityZero()
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

	PlayerGivenAnimProgress(InDeltaTime);
	PlayerGivenAEProgress(InDeltaTime);
}

void UPlayerUIAimWidget::SetAimUIByMagneticComp(UMagneticComponent* typeL, UMagneticComponent* typeR, EMagneticType playerType)
{
	EMagneticType t1 = typeL && ::IsValid(typeL) ? typeL->GetCurrentMagnetic() : EMagneticType::NONE;
	EMagneticType t2 = typeR && ::IsValid(typeR) ? typeR->GetCurrentMagnetic() : EMagneticType::NONE;

	SetAimUIByMagneticType(t1, t2, playerType);
}

void UPlayerUIAimWidget::PlayerGivenAEProgress(float DeltaTime)
{
	if (_PlayerCircleAE.ApplyCurrTime <= 0.f) return;

	float progressRatio = 1.f - (_PlayerCircleAE.ApplyCurrTime * _PlayerCircleAE.GoalTimeDiv);
	FVector2D result = _PlayerCircleAE.DefaultScale + _PlayerCircleAE.DistanceScale * progressRatio;
	float alpha = 1.f-progressRatio;

	/*보간 및 적용*/
	_PlayerCircleAE.GetImgByMagType()->SetRenderScale(result);
	_PlayerCircleAE.GetImgByMagType()->SetAlpha(alpha);
	_PlayerCircleAE.ApplyCurrTime -= DeltaTime;

	/*마무리 과정*/
	if (_PlayerCircleAE.ApplyCurrTime<=0.f)
	{
		_PlayerCircleAE.CurrType = EMagneticType::NONE;
		_PlayerCircleAE.SetAllImgOpacityZero();
	}
}

void UPlayerUIAimWidget::PlayerGivenAnimProgress(float DeltaTime)
{
	if (_PlayerCircle.ApplyCurrTime <= 0.f) return;

	float progressRatio = 1.f - (_PlayerCircle.ApplyCurrTime * _PlayerCircle.GoalTimeDiv);
	FVector2D result = _PlayerCircle.StartScale + _PlayerCircle.DistanceScale * progressRatio;

	/*보간 및 적용*/
	_PlayerCircle.GetImgByMagType()->SetRenderScale(result);
	_PlayerCircle.ApplyCurrTime -= DeltaTime;

	/*마무리 적용.*/
	if (_PlayerCircle.ApplyCurrTime<=0.f)
	{
		/*원이 작아지는 과정 마무리*/
		if (_PlayerCircle.IsAddtive == false) 
		{
			_PlayerCircle.CurrType = _PlayerCircle.NextType;

			/*추가적인 과정이 존재할 경우*/
			if (_PlayerCircle.NextType != EMagneticType::NONE) {

				_PlayerCircle.IsAddtive = true;
				_PlayerCircle.GetImgByMagType()->SetRenderScale(FVector2D::ZeroVector);
				_PlayerCircle.SetImgVisibleByMagType();

				_PlayerCircle.StartScale = _PlayerCircle.GetImgByMagType()->GetRenderTransform().Scale;
				_PlayerCircle.ApplyCurrTime = PlayerGivenApplySeconds * .5f;
				_PlayerCircle.DistanceScale =_PlayerCircle.DefaultScale - _PlayerCircle.StartScale;
				_PlayerCircle.GoalTimeDiv = 1.f / _PlayerCircle.ApplyCurrTime;
			}

			_PlayerCircle.NextType = EMagneticType::NONE;
			return;
		}

		/*원이 커지는 과정 마무리 및 잔상효과 실행.*/
		_PlayerCircle.ApplyCurrTime = 0.f;
		_PlayerCircle.NextType = EMagneticType::NONE;

		_PlayerCircleAE.ApplyCurrTime = PlayerGivenAEApplySeconds;
		_PlayerCircleAE.StartScale = _PlayerCircleAE.DefaultScale;
		_PlayerCircleAE.DistanceScale = FVector2D(0.5f, 0.5f);
		_PlayerCircleAE.GoalTimeDiv = 1.f / PlayerGivenAEApplySeconds;
		_PlayerCircleAE.CurrType = _PlayerCircle.CurrType;
		_PlayerCircleAE.GetImgByMagType()->SetRenderScale(_PlayerCircle.DefaultScale);
		_PlayerCircleAE.SetImgVisibleByMagType();
	}

}

void UPlayerUIAimWidget::SetAimUIByMagneticType(EMagneticType typeL, EMagneticType typeR, EMagneticType playerType)
{
	const bool bGivenLAddtive	 = (_GivenInfoL.CurrType == EMagneticType::NONE) && (typeL != EMagneticType::NONE);
	const bool bGivenLSubtract	 = (_GivenInfoL.CurrType != EMagneticType::NONE) && (_GivenInfoL.CurrType != typeL);
	const bool bGivenLEnd		 = (_GivenInfoL.CurrType != EMagneticType::NONE) && (typeL == EMagneticType::NONE);

	const bool bGivenRAddtive	 = (_GivenInfoR.CurrType == EMagneticType::NONE) && (typeR != EMagneticType::NONE);
	const bool bGivenRSubtract	 = (_GivenInfoR.CurrType != EMagneticType::NONE) && (_GivenInfoR.CurrType != typeR);
	const bool bGivenREnd		 = (_GivenInfoR.CurrType != EMagneticType::NONE) && (typeR == EMagneticType::NONE);

	const bool bPCircleChange	 = (_PlayerCircle.CurrType != playerType);
	const bool bPCircleScaleUp	 = (_PlayerCircle.CurrType == EMagneticType::NONE) && (bPCircleChange);
	const bool bPCircleScaleDown = (_PlayerCircle.CurrType != EMagneticType::NONE) && (bPCircleChange);

	/*플레이어 원형 이펙트*/
	if (bPCircleChange)
	{
		_PlayerCircle.ApplyCurrTime = PlayerGivenApplySeconds * .5f;
		_PlayerCircle.GoalTimeDiv = 1.f / _PlayerCircle.ApplyCurrTime;

		/*원이 커질 경우*/
		if (bPCircleScaleUp)
		{
			_PlayerCircle.IsAddtive = true;
			_PlayerCircle.CurrType = playerType;
			_PlayerCircle.SetImgVisibleByMagType();
			_PlayerCircle.NextType = EMagneticType::NONE;
			_PlayerCircle.GetImgByMagType()->SetRenderScale(FVector2D::ZeroVector);
			_PlayerCircle.StartScale = FVector2D::ZeroVector;
			_PlayerCircle.DistanceScale = _PlayerCircle.DefaultScale - _PlayerCircle.StartScale;
		}
		/*원이 작아질 경우*/
		else if (bPCircleScaleDown)
		{
			_PlayerCircle.IsAddtive = false;
			_PlayerCircle.NextType = playerType;
			_PlayerCircle.StartScale = _PlayerCircle.GetImgByMagType()->GetRenderTransform().Scale;
			_PlayerCircle.DistanceScale = _PlayerCircle.StartScale * -1.f;
		}
	}


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
	_GivenInfoL.SetAllImgOpacityZero();

	//GivenR 초기화
	_GivenInfoR.BlueImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("GivenR_Blue")));
	_GivenInfoR.RedImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("GivenR_Red")));
	_GivenInfoR.GoalTimeDiv = 1.f / MagGivenApplySeconds;
	_GivenInfoR.SetAllImgOpacityZero();

	//PlayerGiven 초기화
	_PlayerCircle.RedImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("PlayerGivenCircle_Red")));
	_PlayerCircle.BlueImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("PlayerGivenCircle_Blue")));
	_PlayerCircle.DefaultScale = _PlayerCircle.RedImg->GetRenderTransform().Scale;
	_PlayerCircle.SetAllImgOpacityZero();

	/*PlayerGivenAE 초기화*/
	_PlayerCircleAE.RedImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("PlayerGivenCircle_RedAE")));
	_PlayerCircleAE.BlueImg = Cast<UHandlerImage>(GetWidgetFromName(TEXT("PlayerGivenCircle_BlueAE")));
	_PlayerCircleAE.DefaultScale = _PlayerCircle.RedImg->GetRenderTransform().Scale;
	_PlayerCircleAE.SetAllImgOpacityZero();

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
		_UIManager->OnUIFadeChange.AddDynamic(this, &UPlayerUIAimWidget::FadeChange);

}

void UPlayerUIAimWidget::NativeDestruct()
{
	Super::NativeDestruct();

	/*페이드 델리게이트 제거*/
	if (_UIManager.IsValid())
		_UIManager->OnUIFadeChange.RemoveDynamic(this, &UPlayerUIAimWidget::FadeChange);
}



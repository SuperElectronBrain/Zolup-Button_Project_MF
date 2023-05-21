#include "PlayerUIAimWidget.h"
#include "MagneticComponent.h"
#include "Components/Image.h"

UImage* FGivenImgInfo::GetImgByMagType() const 
{ 
	return CurrType == EMagneticType::N ? RedImg : BlueImg; 
}

void FGivenImgInfo::SetImgOpacityByMagType()
{
	if (RedImg) RedImg->SetOpacity(CurrType == EMagneticType::N ? 1.f : 0.f);
	if (BlueImg) BlueImg->SetOpacity(CurrType == EMagneticType::S ? 1.f : 0.f);
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

	GivenAnimProgress(_GivenInfoL, InDeltaTime);
}

void UPlayerUIAimWidget::SetAimUIByMagneticComp(UMagneticComponent* typeL, UMagneticComponent* typeR, bool playerMagChange)
{
	EMagneticType t1 = ::IsValid(typeL) ? typeL->GetCurrentMagnetic() : EMagneticType::NONE;
	EMagneticType t2 = ::IsValid(typeR) ? typeR->GetCurrentMagnetic() : EMagneticType::NONE;

	SetAimUIByMagneticType(t1, t2, playerMagChange);
}

void UPlayerUIAimWidget::SetAimUIByMagneticType(EMagneticType typeL, EMagneticType typeR, bool playerMagChange)
{
	//계산에 필요한 것들을 모두 구한다.
	bool bGivenL_IsNone = _GivenInfoL.CurrType == EMagneticType::NONE;
	bool bGivenL_IsChanged = _GivenInfoL.CurrType != typeL;
	bool bGivenL_IsAddtive = bGivenL_IsNone && typeL != EMagneticType::NONE;
	bool bGivenL_IsSubtract = !bGivenL_IsNone && bGivenL_IsChanged;

	/*GivenL*/
	//Additive
	if (bGivenL_IsAddtive)
	{
		_GivenInfoL.ApplyAimType = EGivenAnimType::ADDTIVE;
		_GivenInfoL.CurrType = typeL;
		_GivenInfoL.SetImgOpacityByMagType();
		_GivenInfoL.ApplyCurrTime = 0.f;
	}
	//Subtract
	else if (bGivenL_IsSubtract)
	{
		_GivenInfoL.ApplyAimType = EGivenAnimType::SUBTRACT;
		_GivenInfoL.ApplyCurrTime = 0.f;

		if (typeL!=EMagneticType::NONE)
		{
			_GivenInfoL.NextAimType = EGivenAnimType::ADDTIVE;
			_GivenInfoL.NextType = typeL;
		}
	}


}

void UPlayerUIAimWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	/*애니메이션에서 필요한 모든 참조를 가지고 온다.*/

	//GivenL 초기화
	_GivenInfoL.BlueImg = Cast<UImage>(GetWidgetFromName(TEXT("GivenL_Blue")));
	_GivenInfoL.RedImg = Cast<UImage>(GetWidgetFromName(TEXT("GivenL_Red")));
	_GivenInfoL.GoalTimeDiv = 1.f / MagGivenApplySeconds;
	if (_GivenInfoL.RedImg) _GivenInfoL.RedImg->SetOpacity(0.f);
	if (_GivenInfoL.BlueImg)
	{
		_GivenInfoL.OriginPos = _GivenInfoL.BlueImg->GetRenderTransform().Translation;
		_GivenInfoL.BlueImg->SetOpacity(0.f);
	}

	//GivenR 초기화
	_GivenInfoR.BlueImg = Cast<UImage>(GetWidgetFromName(TEXT("GivenR_Blue")));
	_GivenInfoR.RedImg = Cast<UImage>(GetWidgetFromName(TEXT("GivenR_Red")));
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
}

void UPlayerUIAimWidget::GivenAnimProgress(FGivenImgInfo& info, float DeltaTime)
{
	//연산에 사용될 요소들을 모두 구한다.
	float progressRatio = FMath::Clamp(info.ApplyCurrTime * info.GoalTimeDiv, 0.f, 1.f);
	FVector2D offset;
	UImage* UsedImg = info.GetImgByMagType();

	//Addtive
	if (info.ApplyAimType==EGivenAnimType::ADDTIVE)
	{
		offset.X = -30.f * (1.f-progressRatio);

		UsedImg->SetRenderTranslation(_GivenInfoL.OriginPos + offset);

		if (progressRatio >= 1.f) {

			/*종료 후의 동작이 예약되어있을 경우*/
			if (info.NextAimType!=EGivenAnimType::NONE)
			{
				info.ApplyAimType = info.NextAimType;
				info.CurrType = info.NextType;
				info.NextAimType = EGivenAnimType::NONE;
				info.ApplyCurrTime = 0.f;
			}
			else info.ApplyAimType = EGivenAnimType::NONE;
		}
		else info.ApplyCurrTime += DeltaTime;

		return;
	}

	//Subtract
	if (info.ApplyAimType == EGivenAnimType::SUBTRACT)
	{
		offset.X = -30.f * progressRatio;

		UsedImg->SetRenderTranslation(_GivenInfoL.OriginPos + offset);

		/*마무리*/
		if (progressRatio >= 1.f) {

			/*종료 후의 동작이 예약되어있을 경우*/
			if (info.NextAimType != EGivenAnimType::NONE)
			{
				info.ApplyAimType = info.NextAimType;
				info.CurrType = info.NextType;
				info.NextAimType = EGivenAnimType::NONE;
				info.ApplyCurrTime = 0.f;
				info.SetImgOpacityByMagType();
			}
			else
			{
				info.ApplyAimType = EGivenAnimType::NONE;
				info.CurrType = EMagneticType::NONE;
			}
		}
		else info.ApplyCurrTime += DeltaTime;

		return;
	}

}

void UPlayerUIAimWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UPlayerUIAimWidget::NativeDestruct()
{
	Super::NativeDestruct();
}



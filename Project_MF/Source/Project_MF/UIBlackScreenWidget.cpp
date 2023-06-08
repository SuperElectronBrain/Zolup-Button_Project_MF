#include "UIBlackScreenWidget.h"
#include "GameUIManager.h"
#include "Components/Image.h"
#include "CustomGameInstance.h"

float UUIBlackScreenWidget::GetAlpha() const { return ColorAndOpacity.A; }
void UUIBlackScreenWidget::SetAlpha(float newAlpha)
{
	FLinearColor newColor = ColorAndOpacity;
	newColor.A = FMath::Clamp(newAlpha, 0.f, 1.f);
	SetColorAndOpacity(newColor);
	if (_ScreenImage) _ScreenImage->SetColorAndOpacity(newColor);
}

FLinearColor UUIBlackScreenWidget::GetColor() const { return ColorAndOpacity; }
void UUIBlackScreenWidget::SetColor(FLinearColor newColor) 
{ 
	SetColorAndOpacity(newColor); 
	if (_ScreenImage) _ScreenImage->SetColorAndOpacity(newColor);
}

void UUIBlackScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//게임 인스턴스가 유효하면 UIManager를 얻어온다.
	UCustomGameInstance* Instance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());
	if (::IsValid(Instance)) _UIManager = Instance->GetUIManager();

	//스크린에 쓰이는 이미지를 가져온다.
	_ScreenImage = Cast<UImage>(GetWidgetFromName(TEXT("screenImage")));
}

void UUIBlackScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

}
void UUIBlackScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (_UIManager.IsValid() == false) return;

	//현재 이 위젯으로 페이드 진행중일 경우, 뷰포트에서 제거되지 않도록 한다.
	if (_UIManager->IsPlayingFadeByID(WIDGET_BLACKSCREEN_KEEP_ADDED_VIEWPORT_FADE_ID))
	{
		AddToViewport(5);
	}
}
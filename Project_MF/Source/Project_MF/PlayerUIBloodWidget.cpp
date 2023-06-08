#include "PlayerUIBloodWidget.h"
#include "HandlerImage.h"
#include "CustomGameInstance.h"
#include "GameUIManager.h"

void UPlayerUIBloodWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//게임인스턴스를 초기화한다.
	_Instance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());

	//블러딩 이펙트
	FBloodImages level0;
	FillBloodImages(level0, 0, 6);
	BloodEffectLevels.Add(level0);

	FBloodImages level1;
	FillBloodImages(level1, 1, 5);
	BloodEffectLevels.Add(level1);

	FBloodImages level2;
	FillBloodImages(level2, 2, 5);
	BloodEffectLevels.Add(level2);
}

void UPlayerUIBloodWidget::FillBloodImages(FBloodImages& level, int levelCount, int count)
{
	FString levelName = FString("Blood");
	levelName.AppendInt(levelCount);

	level.Images.Reset();
	for(int i=1; i<=count; i++)
	{
		FString findString = levelName + FString("_") + FString::FromInt(i);
		UWidget* widget = GetWidgetFromName(*findString);
		UHandlerImage* image = Cast<UHandlerImage>(widget);

		if (image == nullptr) continue;

		level.Images.Add(image);
	}
}

void UPlayerUIBloodWidget::ShowBloodEffect(int level)
{
	const int LevelCount = BloodEffectLevels.Num();
	float levelDiv = 1.f / LevelCount;
	float ratio = 1.f - (level*levelDiv);

	if (_Instance.IsValid() == false || level<0 || level>LevelCount) return;
	
	UGameUIManager* UIManager = _Instance->GetUIManager();
	FBloodImages& bloodImages = BloodEffectLevels[level];
	for (UHandlerImage* img : bloodImages.Images)
	{
		if (img == nullptr) continue;

		UIManager->PlayFadeInOut(
			EFadeType::DARK_TO_WHITE,
			img,
			0.f,
			(1.5f * ratio),
			1.f,
			0.f,
			1.f,
			0.f,
			-1,
			FLinearColor::Green,
			FLinearColor::Green
		);
	}
}
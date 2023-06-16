#include "GameLevelPlayerController.h"
#include "CustomGameInstance.h"
#include "UIGameSettingsWidget.h"

AGameLevelPlayerController::AGameLevelPlayerController()
{
}

void AGameLevelPlayerController::SetupInputComponent()
{
	InputComponent->BindAction(
		TEXT("ShowSettings"), EInputEvent::IE_Pressed, this, &AGameLevelPlayerController::ShowGameSettings
	);
}

void AGameLevelPlayerController::ShowGameSettings()
{
	if (GameSettingsWidget.IsValid() == false) return;

	//뷰포트에 추가가 되어있지 않다면 추가한다.
	if (GameSettingsWidget->IsInViewport() == false)
	{
		GameSettingsWidget->AddToViewport(4);


	}
	else
	{
		GameSettingsWidget->RemoveFromParent();
	}
}
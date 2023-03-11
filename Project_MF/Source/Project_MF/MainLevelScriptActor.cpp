// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelScriptActor.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainLevelGameMode.h"
#include "CustomGameInstance.h"
#include "Components/Button.h"

AMainLevelScriptActor::AMainLevelScriptActor()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_UICANVAS_C(TEXT("/Game/UI/MainLevel_UICanvas.MainLevel_UICanvas_C"));
	if (UI_UICANVAS_C.Succeeded() == true)
	{
		MainLevelUICanvasClass = UI_UICANVAS_C.Class;
	}
}

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	MainLevelUICanvasInstance = CreateWidget<UUserWidget>(GetWorld(), MainLevelUICanvasClass);
	MainLevelUICanvasInstance->AddToViewport();

	UCustomGameInstance* GameModeInstance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());
	if (GameModeInstance != nullptr)
	{
		if (GameModeInstance->GetEditmode() == false)
		{
			UUserWidget* ChildWidget = Cast<UUserWidget>(MainLevelUICanvasInstance->GetWidgetFromName(TEXT("MainMenu_ModeSelectionButtons")));
			if (ChildWidget != nullptr)
			{
				UButton* ButtonWidget = Cast<UButton>(ChildWidget->GetWidgetFromName(TEXT("Vertical Box")));
				if (ButtonWidget != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("챤"));

					ButtonWidget->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "MainLevelUICanvasWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformMisc.h"

void UMainLevelUICanvasWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UUserWidget* ChildWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("MainMenu_ModeSelectionButtons")));
	if (ChildWidget != nullptr)
	{
		GameStartButton = Cast<UButton>(ChildWidget->GetWidgetFromName(TEXT("Button_GameStart")));
		if (GameStartButton != nullptr)
		{
			GameStartButton->OnClicked.AddDynamic(this, &UMainLevelUICanvasWidget::OnStartButtonClicked);
		}
		GameQuitButton = Cast<UButton>(ChildWidget->GetWidgetFromName(TEXT("Button_GameQuit")));
		if (GameQuitButton != nullptr)
		{
			GameQuitButton->OnClicked.AddDynamic(this, &UMainLevelUICanvasWidget::OnQuitButtonClicked);
		}
		GameEditButton = Cast<UButton>(ChildWidget->GetWidgetFromName(TEXT("Button_GameEdit")));
		if (GameEditButton != nullptr)
		{
			GameEditButton->OnClicked.AddDynamic(this, &UMainLevelUICanvasWidget::OnEditButtonClicked);
		}
	}
}

void UMainLevelUICanvasWidget::GameStart()
{
	//UE_LOG(LogTemp, Warning, TEXT("î"));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Tutorial_0"));
}

void UMainLevelUICanvasWidget::GameQuit()
{
	if (GetWorld()->WorldType == EWorldType::Game)
	{
		FGenericPlatformMisc::RequestExit(true);
	}
	else if (GetWorld()->WorldType == EWorldType::PIE)
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("quit"));
	}
}

void UMainLevelUICanvasWidget::EnterEditMode()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("EditLevel"));
}


void UMainLevelUICanvasWidget::OnStartButtonClicked()
{
	GameStart();
}

void UMainLevelUICanvasWidget::OnQuitButtonClicked()
{
	GameQuit();
}

void UMainLevelUICanvasWidget::OnEditButtonClicked()
{
	EnterEditMode();
}

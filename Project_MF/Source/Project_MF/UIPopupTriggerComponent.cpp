// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPopupTriggerComponent.h"
#include "GameFramework/Character.h"
#include "Engine/LevelScriptActor.h"
#include "Misc/OutputDeviceNull.h"

UUIPopupTriggerComponent::UUIPopupTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	OneTime = true;
}

void UUIPopupTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetGenerateOverlapEvents(true);

	if (::IsValid(CanvasClass) == true)
	{
		CanvasInstance = CreateWidget<UUserWidget>(GetWorld(), CanvasClass);
		CanvasInstance->AddToViewport();
		CanvasInstance->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUIPopupTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (int i = 0; i < OverlappingActors.Num(); i = i + 1)
	{
		if (OverlappingActors[i] != GetOwner())
		{
			if (::IsValid(Cast<ACharacter>(OverlappingActors[i])) == true)
			{
				if (::IsValid(CanvasInstance) == true)
				{
					//FOutputDeviceNull Ar;
					//bool result = GetWorld()->GetCurrentLevel()->GetLevelScriptActor()->CallFunctionByNameWithArguments(TEXT("Activatewidget"), Ar, NULL, true);
					if (CanvasInstance->GetVisibility() == ESlateVisibility::Collapsed || CanvasInstance->GetVisibility() == ESlateVisibility::Hidden)
					{
						CanvasInstance->SetVisibility(ESlateVisibility::Visible);
					}

					if (OneTime == true)
					{
						PrimaryComponentTick.bCanEverTick = false;
					}
				}
				break;
			}
		}
	}
}
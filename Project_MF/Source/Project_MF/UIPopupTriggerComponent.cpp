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
				FOutputDeviceNull Ar;
				const FString command = FString::Printf(TEXT("Activatewidget"));
				bool result = GetWorld()->GetCurrentLevel()->GetLevelScriptActor()->CallFunctionByNameWithArguments(*command, Ar, NULL, true);
				//if (result == true)
				//{
				//	UE_LOG(LogTemp, Warning, TEXT("î"));
				//}

				if (OneTime == true)
				{
					PrimaryComponentTick.bCanEverTick = false;
				}
				break;
			}
		}
	}
}
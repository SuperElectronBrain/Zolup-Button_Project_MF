// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeLevelComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UChangeLevelComponent::UChangeLevelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	OneTime = true;
}

void UChangeLevelComponent::BeginPlay()
{
	Super::BeginPlay();
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetGenerateOverlapEvents(true);
}

void UChangeLevelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("Stage_1"));

				if (OneTime == true)
				{
					PrimaryComponentTick.bCanEverTick = false;
				}
				break;
			}
		}
	}
}
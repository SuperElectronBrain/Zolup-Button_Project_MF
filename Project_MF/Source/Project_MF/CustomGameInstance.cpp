// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"

UCustomGameInstance::UCustomGameInstance()
{
	bEditmode = false;
}

void UCustomGameInstance::Init()
{
	_UI = NewObject<UGameUIManager>(this, TEXT("UI_MANAGER"));

	Super::Init();

	//if (::IsValid(SoundMix) == true && ::IsValid(SoundClass) == true)
	//{
	//	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SoundClass, 0.0f);
	//	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
	//}
	
	//if (GetWorld()->WorldType == EWorldType::Game)
	//{
	//	bEditmode = false;
	//}

	//else if (GetWorld()->WorldType == EWorldType::PIE)
	//else
	//{
	//	bEditmode = true;
	//}
}

bool UCustomGameInstance::GetEditmode()
{
	return bEditmode;
}

void UCustomGameInstance::SetEditmode(bool param)
{
	bEditmode = param;
}
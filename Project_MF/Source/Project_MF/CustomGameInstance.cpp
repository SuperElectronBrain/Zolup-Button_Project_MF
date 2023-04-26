// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"

UCustomGameInstance::UCustomGameInstance()
{
	bEditmode = false;
	_UI = NewObject<UGameUIManager>(this, TEXT("UI_MANAGER"));
}

void UCustomGameInstance::Init()
{
	if (GetWorld()->WorldType == EWorldType::Game)
	{
		bEditmode = false;
	}
	//else if (GetWorld()->WorldType == EWorldType::PIE)
	else
	{
		bEditmode = true;
	}
}

bool UCustomGameInstance::GetEditmode()
{
	return bEditmode;
}

void UCustomGameInstance::SetEditmode(bool param)
{
	bEditmode = param;
}
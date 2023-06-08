// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"

FSoundList* USoundManager::GetSoundList(FName SoundListName)
{
	for (int i = 0; i < SoundLists.Num(); i = i + 1)
	{
		if (SoundLists[i].SoundListName == SoundListName.ToString())
		{
			return &SoundLists[i];
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}

USoundManager::USoundManager()
{
}

void USoundManager::Init()
{
}

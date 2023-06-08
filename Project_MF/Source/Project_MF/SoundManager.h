// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundBase.h"
#include "SoundManager.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FSoundData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString SoundSourceName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<USoundBase*> Sounds;
};

USTRUCT(Atomic, BlueprintType)
struct FSoundList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString SoundListName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FSoundData> SoundSources;

	USoundBase* GetSoundSource(FName SoundSourceName)
	{
		for (int i = 0; i < SoundSources.Num(); i = i + 1)
		{
			if (SoundSources[i].SoundSourceName == SoundSourceName.ToString())
			{
				if (SoundSources[i].Sounds.Num() > 0)
				{
					return SoundSources[i].Sounds[0];
				}
				else
				{
					return nullptr;
				}
			}
		}
		return nullptr;
	}

	USoundBase* GetSoundSourceByVariation(FName SoundSourceName, int32 index)
	{
		for (int i = 0; i < SoundSources.Num(); i = i + 1)
		{
			if (SoundSources[i].SoundSourceName == SoundSourceName.ToString())
			{
				if (SoundSources[i].Sounds.Num() > index)
				{
					return SoundSources[i].Sounds[index];
				}
				else
				{
					return nullptr;
				}
			}
		}
		return nullptr;
	}

	USoundBase* GetSoundSourceByRandom(FName SoundSourceName)
	{
		for (int i = 0; i < SoundSources.Num(); i = i + 1)
		{
			if (SoundSources[i].SoundSourceName == SoundSourceName.ToString())
			{
				if (SoundSources[i].Sounds.Num() > 0)
				{
					return SoundSources[i].Sounds[FMath::RandRange(0, SoundSources[i].Sounds.Num() - 1)];
				}
				else
				{
					return nullptr;
				}
			}
		}
		return nullptr;
	}
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECT_MF_API USoundManager : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TArray<FSoundList> SoundLists;

protected:
	//virtual void Tick(float Delta) override;

public:
	FSoundList* GetSoundList(FName SoundListName);

	USoundManager();
	virtual void Init();
};

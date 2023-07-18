// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundListBase.h"

USoundBase* USoundListBase::GetSoundSource(const FName& SourceName)
{
	if (Descs.Contains(SourceName) && Descs[SourceName].Variations.Num() > 0)
	{
		return Descs[SourceName].Variations[0];
	}

	return nullptr;
}

USoundBase* USoundListBase::GetSoundSourceVariation(const FName& SourceName, int index)
{
	if (Descs.Contains(SourceName) && Descs[SourceName].Variations.Num() > (index+1))
	{
		return Descs[SourceName].Variations[index];
	}

	return nullptr;
}

USoundBase* USoundListBase::GetSoundSourceVariationByRandom(const FName& SourceName)
{
	if (Descs.Contains(SourceName) && Descs[SourceName].Variations.Num() > 0)
	{
		FRandomStream Stream;
		int32 Index = Stream.RandRange(0, Descs[SourceName].Variations.Num());

		return Descs[SourceName].Variations[Index];
	}

	return nullptr;
}

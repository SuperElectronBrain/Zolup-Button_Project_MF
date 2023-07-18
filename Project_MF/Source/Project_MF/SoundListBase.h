// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundListBase.generated.h"

USTRUCT(BlueprintType)
struct FSoundSourceDesc
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=SoundList, BlueprintReadWrite)
	TArray<USoundBase*> Variations;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (SoundList), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API USoundListBase : public UObject
{
	GENERATED_BODY()
	
public:
	USoundBase* GetSoundSource(const FName& SourceName);
	USoundBase* GetSoundSourceVariation(const FName& SourceName, int index);
	USoundBase* GetSoundSourceVariationByRandom(const FName& SourceName);

private:
	UPROPERTY(EditAnywhere, Category = SoundList, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	TMap<FName, FSoundSourceDesc> Descs;

};

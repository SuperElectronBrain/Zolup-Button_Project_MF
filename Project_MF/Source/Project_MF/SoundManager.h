// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API USoundManager : public UObject
{
	GENERATED_BODY()
private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TArray<FSoundTuple> FSoundDatas;

protected:
	//virtual void Tick(float Delta) override;

public:
	USoundManager();
	virtual void Init();
};

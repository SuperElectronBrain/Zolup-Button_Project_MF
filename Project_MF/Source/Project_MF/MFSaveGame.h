// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MFSaveGame.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMFObjectData
{
	GENERATED_BODY()

	UPROPERTY() FString ObjectName;

	UPROPERTY() FString ObjectType;
	UPROPERTY() int32 ObjectState;
	UPROPERTY() int32 ObjectMovement;

	UPROPERTY() FVector ObjectLocation;
	UPROPERTY() FRotator ObjectRotation;
	UPROPERTY() FVector ObjectScale;
	UPROPERTY() FVector ObjectVelocity;
};

USTRUCT(BlueprintType)
struct FMFStageData
{
	GENERATED_BODY()

	UPROPERTY() FString StageName;
	UPROPERTY() int32 CurrentCheckPoint;
	UPROPERTY() TArray<FMFObjectData> StageObjects;
};

UCLASS()
class PROJECT_MF_API UMFSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMFSaveGame();

	UPROPERTY() FVector PlayerLocation;
	UPROPERTY() FRotator PlayerRotation;
	UPROPERTY() FVector PlayerVelocity;

	UPROPERTY() FString CurrentStage;
	UPROPERTY() TArray<FMFStageData> StagesData;
};

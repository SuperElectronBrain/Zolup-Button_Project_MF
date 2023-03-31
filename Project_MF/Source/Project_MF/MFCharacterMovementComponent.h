// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MFCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UMFCharacterMovementComponent final : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual bool IsWalkable(const FHitResult& Hit) const override;
	
};

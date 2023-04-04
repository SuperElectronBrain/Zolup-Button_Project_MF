// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerCharacter.h"
#include "MFCharacterMovementComponent.h"

bool UMFCharacterMovementComponent::IsWalkable(const FHitResult& Hit) const
{
	if (Hit.GetActor() && Hit.GetActor()->IsA(ACharacter::StaticClass()))
	{
		return false;
	}

	return Super::IsWalkable(Hit);
}


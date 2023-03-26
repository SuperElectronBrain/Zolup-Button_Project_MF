// Fill out your copyright notice in the Description page of Project Settings.


#include "EditLevelScriptActor.h"
#include "EditLevelPawn.h"

AEditLevelScriptActor::AEditLevelScriptActor()
{

}

void AEditLevelScriptActor::BeginPlay()
{
	AEditLevelPawn* EditLevelPawn = Cast<AEditLevelPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (EditLevelPawn != nullptr)
	{
		EditLevelPawn->SetEditLevelMFActorManagementActor
		(
			GetWorld()->SpawnActor<AEditLevelMFActorManagementActor>(AEditLevelMFActorManagementActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator)
		);
	}
}
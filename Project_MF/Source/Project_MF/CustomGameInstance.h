// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere) bool bEditmode;

protected:
	virtual void Init() override;
public:
	UCustomGameInstance();
	
	bool GetEditmode();
	void SetEditmode(bool param);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameUIManager.h"
#include "CustomGameInstance.generated.h"

/*
*게임을 전반적으로 관리하는 기능들이 내장된 GameInstance파생 클래스입니다.
 */
UCLASS()
class PROJECT_MF_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	////////////////////
	/// Constructor ////
	////////////////////
	UCustomGameInstance();

	////////////////////////
	/// Public methods ////
	///////////////////////
	bool GetEditmode();
	void SetEditmode(bool param);
	UGameUIManager* GetUIManager() const { return _UI; }

private:
	///////////////////////
	/// Private methods ///
	//////////////////////
	virtual void Init() override;

	////////////////////////////
	/// fields And Components //
	////////////////////////////
	UPROPERTY(VisibleAnywhere)
	bool bEditmode;

	UPROPERTY()
	UGameUIManager* _UI;
};

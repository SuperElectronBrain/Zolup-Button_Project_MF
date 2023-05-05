// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameUIManager.h"
#include "SoundManager.h"
#include "CustomGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSoundTuple
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString MaterialType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<USoundBase> MaterialSound;
};

/*
*게임을 전반적으로 관리하는 기능들이 내장된 GameInstance파생 클래스입니다.
 */
UCLASS()
class PROJECT_MF_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	//Fields And Components
private:
	UPROPERTY() bool bEditmode;

	UPROPERTY() UGameUIManager* _UI;
	UPROPERTY() TObjectPtr<USoundManager> SoundManager;

protected:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound) TArray<FSoundTuple> FSoundDatas;

	//Methods
private:
	virtual void Init() override;

protected:

public:
	UCustomGameInstance();
	UGameUIManager* GetUIManager() const { return _UI; }
	TObjectPtr<USoundManager> GetSoundManager() { return SoundManager; }
	
	bool GetEditmode();
	void SetEditmode(bool param);
};

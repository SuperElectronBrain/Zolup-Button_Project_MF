// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameUIManager.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "SoundManager.h"
#include "UIBlackScreenWidget.h"
#include "Blueprint/UserWidget.h"
#include "CustomGameInstance.generated.h"

//USTRUCT(BlueprintType)
//struct FMaterialSoundData
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString MaterialType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<USoundBase> MaterialSound;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> Ignore;
//};

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true)) TObjectPtr<UGameUIManager> _UI;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true)) TObjectPtr<USoundManager> SoundManager;
	UPROPERTY() TSubclassOf<USoundManager> SoundManagerClass;

protected:

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound) TArray<FMaterialSoundData> MaterialTypes;

	//Methods
private:
	virtual void Init() override;

protected:

public:
	UCustomGameInstance();
	UGameUIManager* GetUIManager() const { return _UI; }
	USoundManager* GetSoundManager() { return SoundManager; }

	bool GetEditmode();
	void SetEditmode(bool param);
};

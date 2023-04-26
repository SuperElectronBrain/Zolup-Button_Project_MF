// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameUIManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FUIFadeChangeDelegate, bool isDark, int id)

class IGameUIHandler;
class UPlayerUICanvasWidget;
class UUIBlackScreenWidget;

UENUM()
enum class EFadeType
{
	DARK_TO_WHITE = 0b100,
	WHITE_TO_DARK = 0b011,
	DARK_TO_WHITE_TO_DARK = 0b101,
	WHITE_TO_DARK_TO_WHITE = 0b010
};

USTRUCT()
struct FUIFadeInfo
{
	GENERATED_BODY()

public:
	EFadeType type;
	FLinearColor start, goal1, goal3;
	TScriptInterface<IGameUIHandler> handler;
	int id;
	float progressTime;
	float goal1TimeDiv, goal2TimeDiv, startWaitTimeDiv, middleWaitTimeDiv;
	int progress;
	bool pendingKill;
};

/*게임의 모든 UI를 관리하고, UI관련 유틸리티 기능을 사용할 수 있도록 해주는 클래스입니다.
 */
UCLASS()
class PROJECT_MF_API UGameUIManager final : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	///////////////////
	/// Constructor ///
	///////////////////
	UGameUIManager();

	///////////////////////
	/// Public delegate ///
	///////////////////////
	FUIFadeChangeDelegate OnUIFadeChange;

	/////////////////////////
	//// Public methods ////
	////////////////////////

	/*Fade InOut*/
	void PlayFadeInOut(	EFadeType fadeType,
						TScriptInterface<IGameUIHandler> handler,
						float darkTime,
						float whiteTime,
						float darkAlpha = 1.f,
						float whiteAlpha = 0.f,
						float startWaitTime = 0.f,
						float middleWaitTime=0.f,
						int id = -1,
						FLinearColor darkColor=FLinearColor::White,
						FLinearColor whiteColor=FLinearColor::White,
						bool bStartAlphaUsedOrigin = false );

	void StopFadeInOut(int fadeID);
	void StopFadeInOutAll();
	bool IsPlayingFadeByID(int fadeID);
	bool IsPlayingFade() const { return _fadeInfos.Num() > 0; }

	void GetPlayerUICanvasWidget(TWeakObjectPtr<UPlayerUICanvasWidget>& outPtr);
	void GetUIBlackScreenWidget(TWeakObjectPtr<UUIBlackScreenWidget>& outPtr);

private:
	/////////////////////////
	/// Override methods /////
	////////////////////////
	void Tick(float DeltaTime) override;
	bool IsTickable() const override { return true; };
	bool IsTickableInEditor() const override { return false; };
	bool IsTickableWhenPaused() const override { return false; };
	TStatId GetStatId() const override { return TStatId(); };
	UWorld* GetWorld() const override { return GetOuter()->GetWorld(); };

	/////////////////////////
	/// Private methods /////
	////////////////////////
	void FadeProgress(float DeltaTime);

	/////////////////////////////
	/// Fields and Components ///
	/////////////////////////////
	TArray<FUIFadeInfo> _fadeInfos;
	UPlayerUICanvasWidget* _PlayerUICanvas;
	UUIBlackScreenWidget* _BlackScreen;

	UPROPERTY(EditInstanceOnly, Category = UI)
	TSubclassOf<UPlayerUICanvasWidget> PlayerUICanvas_Class;

	UPROPERTY(EditInstanceOnly, Category = UI)
	TSubclassOf<UUIBlackScreenWidget> BlackScreen_Class;
};

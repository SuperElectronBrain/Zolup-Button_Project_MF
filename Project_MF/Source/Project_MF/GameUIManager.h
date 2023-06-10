// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerUICanvasWidget.h"
#include "GameUIManager.generated.h"

class IGameUIHandler;
class UPlayerUICanvasWidget;
class UUIBlackScreenWidget;

UENUM(BlueprintType)
enum class EFadeType : uint8
{
	NONE,
	DARK_TO_WHITE = 0b100,
	WHITE_TO_DARK = 0b011,
	DARK_TO_WHITE_TO_DARK = 0b101,
	WHITE_TO_DARK_TO_WHITE = 0b010
};

USTRUCT()
struct FUIFadeInfo
{
	GENERATED_BODY()

	EFadeType type;
	FLinearColor start, goal1, goal3;
	TScriptInterface<IGameUIHandler> handler;
	int id;
	float progressTime;
	float goal1TimeDiv, goal2TimeDiv, startWaitTimeDiv, middleWaitTimeDiv;
	int progress;
	bool pendingKill;
	bool bRemoveFromParentAtLast;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUIFadeChangeDelegate, bool, isDark, int, id);

/**
* 전역적으로 접근이 필요한 UIWidget들을 제공 및 UI에 대한 추가기능을 제공합니다.
*/
UCLASS(Blueprintable, BlueprintType, ClassGroup = (UIManagers), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UGameUIManager final : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	////////////////////////////////
	////	Constructor		///////
	//////////////////////////////
	UGameUIManager();

	////////////////////////////////
	////	Public Delegates	////
	////////////////////////////////
	UPROPERTY(BlueprintAssignable, Blueprintcallable, Category = UIManager)
	FUIFadeChangeDelegate OnUIFadeChange;


	/////////////////////////////////
	/////	Public methods		////
	////////////////////////////////

	/******************************************************************
	* 페이드 관련 함수들입니다.
	*******************************************************************/

	/**
	* 인자로 건네준 GameUIHandler를 대상으로 페이드 인/아웃 효과를 적용합니다.
	* 
	* @param fadeType		적용할 페이드의 종류입니다.
	* @param handler		페이드 효과를 적용할 대상입니다.
	* @param darkTime		페이드 효과로 어두워지는데 걸리는 시간(초)입니다.
	* @param whiteTime		페이드 효과로 밝아지는데 걸리는 시간(초)입니다.
	* @param darkAlpha		페이드 효과로 어두워졌을 때의 알파값입니다.
	* @param whiteAlpha		페이드 효과로 밝아졌을 때의 알파값입니다.
	* @param startWaitTime	페이드 효과를 적용하기 전, 대기할 시간(초)입니다.
	* @param middleWaitTime	페이드 효과를 적용하고, 다음 페이드 효과를 적용하기 전에 대기할 시간(초)입니다.
	* @param id				이 페이드 효과의 ID값입니다. 이값이 OnUIFadeChange델리게이트에 전달됩니다.
	* @param darkColor		페이드 효과로 어두워졌을 때의 색깔입니다.
	* @param whiteColor		페이드 효과로 밝아졌을 때의 색깔입니다.
	* @param bStartAlphaUsedOrigin	페이드를 적용할 때, 처음 알파값을 유지하는지에 대한 여부입니다.
	* @param bAutoRemoveViewportAtLast	페이드 효과가 마무리될 때, 자동으로 추가되어있는 부모로부터 제거되는지에 대한 여부입니다.
	*/
	UFUNCTION(BlueprintCallable)
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
						bool bStartAlphaUsedOrigin = false,
						bool bAutoRemoveFromParentAtLast=false);

	/**지정한 ID를 가진 페이드 프로그레스를 종료시킵니다.*/
	UFUNCTION(BlueprintCallable, Category = UIManager)
	void StopFadeInOut(int fadeID);

	UFUNCTION(BlueprintCallable, Category = UIManager)
	void StopFadeInOutByHandler(TScriptInterface<IGameUIHandler> handler);

	/**모든 페이드 프로그래스를 종료시킵니다.*/
	UFUNCTION(BlueprintCallable, Category = UIManager)
	void StopFadeInOutAll();

	/**지정한 ID를 가진 페이드 프로그래스가 실행중인지 확인합니다.*/
	UFUNCTION(BlueprintCallable, Category = UIManager)
	bool IsPlayingFadeByID(int fadeID);

	/**지정한 handler를 대상으로 하는 페이드 프로그래스가 실행중인지 확인합니다.*/
	UFUNCTION(BlueprintCallable, Category = UIManager)
	bool IsPlayingFadeByHandler(TScriptInterface<IGameUIHandler> handler);

	/**UIManager에서 페이드가 하나라도 실행중인지 확인합니다.*/
	UFUNCTION(BlueprintCallable, Category = UIManager)
	bool IsPlayingFade() const { return _fadeInfos.Num() > 0; }


	/**************************************************************
	* 전역적으로 접근이 필요한 UI Widget들을 제공하는 함수들입니다.
	***************************************************************/
	void GetPlayerUICanvasWidget(TWeakObjectPtr<UPlayerUICanvasWidget>& outPtr);
	void GetUIBlackScreenWidget(TWeakObjectPtr<UUIBlackScreenWidget>& outPtr);

private:
	/////////////////////////
	/// Override methods /////
	////////////////////////
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; };
	virtual bool IsTickableInEditor() const override { return false; };
	virtual bool IsTickableWhenPaused() const override { return false; };
	virtual TStatId GetStatId() const override { return TStatId(); };
	virtual UWorld* GetWorld() const override { return GetOuter()->GetWorld(); };

	/////////////////////////
	/// Private methods /////
	////////////////////////

	/**전역으로 쓰이는 플레이어 캔버스 위젯을 가져옵니다.*/
	UFUNCTION(BlueprintCallable, Meta = (AllowPrivateAccess = true), Category = UIManager)
	UPlayerUICanvasWidget* GetPlayerUICanvasWidget();

	/**전역으로 쓰이는 블랙스크린 위젯을 가져옵니다.*/
	UFUNCTION(BlueprintCallable, Meta = (AllowPrivateAccess = true), Category = UIManager)
	UUIBlackScreenWidget* GetUIBlackScreenWidget();


	void FadeProgress(float DeltaTime);

	/////////////////////////////
	/// Fields and Components ///
	/////////////////////////////

	TArray<FUIFadeInfo> _fadeInfos;

	UPROPERTY(EditInstanceOnly, Category = UI)
	TSubclassOf<UPlayerUICanvasWidget> PlayerUICanvas_Class;

	UPROPERTY(EditInstanceOnly, Category = UI)
	TSubclassOf<UUIBlackScreenWidget> BlackScreen_Class;

	UPROPERTY()
	UPlayerUICanvasWidget* _PlayerUICanvas;

	UPROPERTY()
	UUIBlackScreenWidget* _BlackScreen;
};

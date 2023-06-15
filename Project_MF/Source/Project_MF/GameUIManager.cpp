#include "GameUIManager.h"
#include "PlayerUICanvasWidget.h"
#include "UIBlackScreenWidget.h"
#include "UIGameSettingsWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameUIHandler.h"

UGameUIManager::UGameUIManager()
{
	/*********************************************************
	* CDO( UserWidget )
	* 전역으로 사용될 위젯 에셋들을 가져오고, 유효하면 참조를 저장합니다.
	***********************************************************/
	static ConstructorHelpers::FClassFinder<UUserWidget> PLAYER_UI_CANVAS(
		TEXT("/Game/UI/Player/PlayerUI_Canvas.PlayerUI_Canvas_C")
	);
	static ConstructorHelpers::FClassFinder<UUIBlackScreenWidget> BLACK_SCREEN(
		TEXT("/Game/UI/UI_BlackScreen.UI_BlackScreen_C")
	);
	static ConstructorHelpers::FClassFinder<UUIGameSettingsWidget> GAME_SETTINGS(
		TEXT("/Game/UI/Menu/MainLevelUI_GameSettings.MainLevelUI_GameSettings_C")
	);


	if (PLAYER_UI_CANVAS.Succeeded()) PlayerUICanvas_Class = PLAYER_UI_CANVAS.Class;
	if (BLACK_SCREEN.Succeeded()) BlackScreen_Class = BLACK_SCREEN.Class;
	if (GAME_SETTINGS.Succeeded()) GameSettings_Class = GAME_SETTINGS.Class;
}

void UGameUIManager::FadeProgress(float DeltaTime)
{
	#pragma region Omission
	int count = _fadeInfos.Num();

	for (int i = 0; i < count; i++)
	{
		FUIFadeInfo& info = _fadeInfos[i];
		float progressRatio = 0.f;
		bool bHandlerIsValid = (::IsValid(info.handler.GetObject())) || (info.handler.GetInterface() != nullptr);

		//유효하지 않다면 삭제.
		if (bHandlerIsValid==false || info.pendingKill)
		{
			if (info.bRemoveFromParentAtLast) {

				UUserWidget* widget = Cast<UUserWidget>(info.handler.GetObject());
				if (widget)
				{
					widget->RemoveFromParent();
				}
			}

			_fadeInfos.RemoveAt(i);
			i--;
			count = _fadeInfos.Num();
			continue;
		}

		//단계별로 처리
		switch (info.progress){

			//시작 딜레이
			case(0): 
			{
				progressRatio = info.progressTime * info.startWaitTimeDiv;
				break;
			}

			//첫번째 페이드
			case(1):
			{
				progressRatio = info.progressTime * info.goal1TimeDiv;
				if (progressRatio >= 1.f) progressRatio = 1.f;
				FLinearColor result((info.goal1-info.start)*progressRatio);

				info.handler->SetColor(info.start + result);
				break;
			}

			//중간 딜레이
			case(2):
			{
				progressRatio = info.progressTime * info.middleWaitTimeDiv;
				break;
			}

			//두번째 페이드
			case(3):
			{
				progressRatio = info.progressTime * info.goal2TimeDiv;
				if (progressRatio >= 1.f) progressRatio = 1.f;
				FLinearColor result((info.goal3 - info.goal1) * progressRatio);

				info.handler->SetColor(info.goal1 + result);
				break;
			}
		}

		//시간 업데이트
		if (progressRatio >= 1.f)
		{
			//델리게이트
			if (info.progress == 1 || info.progress == 3)
			{
				bool isDark = ((int)info.type & (info.progress==1? 0b010:0b001)) >= 1;
				OnUIFadeChange.Broadcast(isDark, info.id);
			}

			info.progressTime = 0.f;
			info.progress++;

			//종료처리
			if (info.progress>=4 || (info.progress == 2 && info.goal1.A==info.goal3.A) || bHandlerIsValid ==false || info.pendingKill)
			{
				UE_LOG(LogTemp, Warning, TEXT("페이드 아웃 마무리!!"))

				if (info.bRemoveFromParentAtLast) {

					UUserWidget* widget =  Cast<UUserWidget>(info.handler.GetObject());
					if (widget)
					{
						widget->RemoveFromViewport();
					}
				}

				_fadeInfos.RemoveAt(i);
				i--;
				count = _fadeInfos.Num();
				continue;
			}
		}
		else info.progressTime += DeltaTime;
	}

	#pragma endregion
}

void UGameUIManager::Tick(float DeltaTime)
{
	//페이드 아웃 처리
	FadeProgress(DeltaTime);
}

void UGameUIManager::PlayFadeInOut(	EFadeType fadeType,
									TScriptInterface<IGameUIHandler> handler,
									float darkTime,
									float whiteTime,
									float darkAlpha,
									float whiteAlpha,
									float startWaitTime,
									float middleWaitTime,
									int id,
									FLinearColor darkColor,
									FLinearColor whiteColor,
									bool bStartAlphaUsedOrigin,
									bool bAutoRemoveFromParentAtLast)
{
	#pragma region Omission
	//유효하지 않은 위젯이라면 스킵한다.
	FUIFadeInfo info;
	if (::IsValid(handler.GetObject())==false) return;
	info.handler = handler;

	if (bStartAlphaUsedOrigin)
	{
		darkAlpha = info.handler->GetAlpha();
	}

	//시간이 0보다 작다면 보정.
	if (darkTime <= 0.f) darkTime = 0.001f;
	if (whiteTime <= 0.f) whiteTime = 0.001f;
	if (startWaitTime <= 0.f) startWaitTime = 0.001f;
	if (middleWaitTime <= 0.f) middleWaitTime = 0.001f;

	bool startDark = ((int)fadeType & 0b100) >= 1;
	bool middleDark = ((int)fadeType & 0b010) >= 1;
	bool endDark = ((int)fadeType & 0b001) >= 1;

	info.start = startDark ? darkColor : whiteColor;
	info.start.A = startDark ? darkAlpha : whiteAlpha;

	info.goal1 = middleDark ? darkColor : whiteColor;
	info.goal1.A = middleDark ? darkAlpha : whiteAlpha;

	info.goal3 = endDark ? darkColor : whiteColor;
	info.goal3.A = endDark ? darkAlpha : whiteAlpha;

	info.type = fadeType;
	info.pendingKill = false;

	//계산에 필요한 요소들을 미리 구한다.
	info.goal1TimeDiv = 1.f / (middleDark ? darkTime : whiteTime);
	info.goal2TimeDiv = 1.f / (endDark ? darkTime : whiteTime);
	info.startWaitTimeDiv = 1.f / startWaitTime;
	info.middleWaitTimeDiv = 1.f / middleWaitTime;
	info.id = id;
	info.progress = 0;
	info.progressTime = 0.f;
	info.bRemoveFromParentAtLast = bAutoRemoveFromParentAtLast;

	//시작 색깔을 적용한다.
	info.handler->SetColor(info.start);

	_fadeInfos.Add(info);
	#pragma endregion
}

void UGameUIManager::StopFadeInOut(int fadeID)
{
	for (FUIFadeInfo& info : _fadeInfos)
	{
		if (info.id != fadeID) continue;
		info.pendingKill = true;
	}
}

void UGameUIManager::StopFadeInOutAll()
{
	for (FUIFadeInfo& info : _fadeInfos)
	{
		info.pendingKill = true;
	}
}

bool UGameUIManager::IsPlayingFadeByID(int fadeID)
{
	for (FUIFadeInfo& info : _fadeInfos)
	{
		if (info.id != fadeID || info.pendingKill) continue;
		
		return true;
	}

	return false;
}

UPlayerUICanvasWidget* UGameUIManager::GetPlayerUICanvasWidget()
{
	TWeakObjectPtr<UPlayerUICanvasWidget> temp;
	GetPlayerUICanvasWidget(temp);

	return temp.Get();
}

void UGameUIManager::StopFadeInOutByHandler(TScriptInterface<IGameUIHandler> handler)
{
	if (handler.GetInterface() == nullptr) return;

	for (FUIFadeInfo& info : _fadeInfos)
	{
		if (info.handler != handler) continue;

		//실행중임이 확인됬을 경우 pendingKill상태로 만든다.
		info.pendingKill = true;
		return;
	}

	return;
}

bool UGameUIManager::IsPlayingFadeByHandler(TScriptInterface<IGameUIHandler> handler)
{
	if (handler.GetInterface() == nullptr) return false;

	for (FUIFadeInfo& info : _fadeInfos)
	{
		if (info.handler != handler) continue;

		//실행중임이 확인됬을 경우
		return true;
	}

	return false;
}

UUIBlackScreenWidget* UGameUIManager::GetUIBlackScreenWidget()
{
	TWeakObjectPtr<UUIBlackScreenWidget> temp;
	GetUIBlackScreenWidget(temp);

	return temp.Get();
}

UUIGameSettingsWidget* UGameUIManager::GetUIGameSettingsWidget()
{
	TWeakObjectPtr<UUIGameSettingsWidget> temp;
	GetUIGameSettingsWidget(temp);

	return temp.Get();
}

void UGameUIManager::GetUIGameSettingsWidget(TWeakObjectPtr<UUIGameSettingsWidget>& outPtr)
{
	if (::IsValid(_GameSettings) == false && GameSettings_Class)
	{
		UGameInstance* ins = GetWorld()->GetGameInstance();
		_GameSettings = Cast<UUIGameSettingsWidget>(CreateWidget(ins, GameSettings_Class));
	}

	outPtr.Reset();
	outPtr = _GameSettings;
}

void UGameUIManager::GetUIBlackScreenWidget(TWeakObjectPtr<UUIBlackScreenWidget>& outPtr)
{
	if (::IsValid(_BlackScreen)==false && BlackScreen_Class)
	{
		UGameInstance* ins = GetWorld()->GetGameInstance();
		_BlackScreen = Cast<UUIBlackScreenWidget>(CreateWidget(ins, BlackScreen_Class));
	}

	outPtr.Reset();
	outPtr = _BlackScreen;
}

void UGameUIManager::GetPlayerUICanvasWidget(TWeakObjectPtr<UPlayerUICanvasWidget>& outPtr)
{
	if (::IsValid(_PlayerUICanvas)==false && PlayerUICanvas_Class)
	{
		UGameInstance* ins = GetWorld()->GetGameInstance();
		_PlayerUICanvas = Cast<UPlayerUICanvasWidget>(CreateWidget(ins, PlayerUICanvas_Class));
	}

	outPtr.Reset();
	outPtr = _PlayerUICanvas;
}
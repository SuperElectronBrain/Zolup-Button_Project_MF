#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIHandler.h"
#include "UIBlackScreenWidget.generated.h"

constexpr const int WIDGET_BLACKSCREEN_KEEP_ADDED_VIEWPORT_FADE_ID = 834;
/**
 * 
 */
UCLASS()
class PROJECT_MF_API UUIBlackScreenWidget final : public UUserWidget, public IGameUIHandler
{
	GENERATED_BODY()

	//////////////////////////////////
	////	Public methods		  ////
	//////////////////////////////////
public:
	UFUNCTION(BlueprintCallable, Category=BlackScreenWidget)
	int GetKeepAddedViewPortFadeID() const { return WIDGET_BLACKSCREEN_KEEP_ADDED_VIEWPORT_FADE_ID; }


	//////////////////////////////////
	///      Override methods      ///
	/////////////////////////////////

private:
	/**UserWidget 제공 함수의 오버라이드입니다.*/
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	/**IGameUIHandler의 인터페이스 구현부입니다.*/
	virtual float GetAlpha() const override;
	virtual void SetAlpha(float newAlpha) override;

	virtual FLinearColor GetColor() const override;
	virtual void SetColor(FLinearColor newColor) override;

	
	/////////////////////////////////////
	////	Field and Components	////
	///////////////////////////////////

private:
	UPROPERTY()
	class UImage* _ScreenImage;

	TWeakObjectPtr<class UGameUIManager> _UIManager;

};

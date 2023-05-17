// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIHandler.h"
#include "PlayerUIAimWidget.generated.h"

enum class EMagneticType : uint8;

/**
 * 플레이어 UI의 애임에 대한 UI를 담당합니다.
 */
UCLASS()
class PROJECT_MF_API UPlayerUIAimWidget final : public UUserWidget, public IGameUIHandler
{
	GENERATED_BODY()

public:
	//////////////////////////////
	////    Public methods   ////
	/////////////////////////////
	void SetAimUIByMagneticType(EMagneticType type);

private:
	//////////////////////////////
	////   override methods   ///
	/////////////////////////////
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	virtual float GetAlpha() const override;
	virtual void SetAlpha(float newAlpha) override;

	virtual FLinearColor GetColor() const override;
	virtual void SetColor(FLinearColor newColor) override;


	///////////////////////////////
	////   Private methods    /////
	///////////////////////////////
private:
	void ChangeAnimProgress(float DeltaTime);


	////////////////////////////////////
	////    Fields and Components  ////
	///////////////////////////////////

	EMagneticType _CurrType;

};

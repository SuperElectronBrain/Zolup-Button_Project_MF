// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUICanvasWidget.generated.h"

class UImage;
class UHandlerImage;
class UPlayerUIMagneticInfoWidget;
class UPlayerUIAimWidget;
class UPlayerUIBloodWidget;
/**
 * 
 */
UCLASS()
class PROJECT_MF_API UPlayerUICanvasWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	/////////////////////////////////////
	////						     ////
	////	  Override methods		 ////
	////						    ////
	///////////////////////////////////
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


	/////////////////////////////////////
	////						     ////
	////	  Public methods		 ////
	////						    ////
	///////////////////////////////////
	void GetMagneticInfoWidget(TWeakObjectPtr<UPlayerUIMagneticInfoWidget>& outPtr) const;
	void GetAimWidget(TWeakObjectPtr<UPlayerUIAimWidget>& outPtr) const;
	void GetBloodEffectWidget(TWeakObjectPtr<UPlayerUIBloodWidget>& outPtr) const;

	void SetClimbAbleImgVisibility(bool isVisible);

private:
	/////////////////////////////////////
	////						     ////
	////     Fields and Components   ////
	////						    ////
	///////////////////////////////////
	UPROPERTY()
	UPlayerUIMagneticInfoWidget* _MagneticInfo;

	UPROPERTY()
	UPlayerUIAimWidget* _Aim;

	UPROPERTY()
	UPlayerUIBloodWidget* _Blood;

	UPROPERTY()
	UHandlerImage* _ClimbAble;
	
};

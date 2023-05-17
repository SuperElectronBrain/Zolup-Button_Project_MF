// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UMG/Public/Components/Image.h>
#include "PlayerUIMagneticInfoWidget.generated.h"

class UMagneticComponent;
enum class EMagneticType : uint8;
class UCustomGameInstance;
class UHandlerImage;

#define MAGINFO_FADEID_L 87
#define MAGINFO_FADEID_R 88 
#define MAGINFO_FADE_SECOND .8f

UCLASS()
class PROJECT_MF_API UPlayerUIMagneticInfoWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	////////////////////
	/// Constructor ////
	////////////////////
	virtual void NativeOnInitialized() override;

	//////////////////////
	/// Public method ///
	/////////////////////
	void ClearInfo();
	void SetInfo(EMagneticType type1, EMagneticType type2);
	void SetInfo(UMagneticComponent* t1, UMagneticComponent* t2);

private:
	///////////////////////
	/// Private methods ///
	///////////////////////
	void fadeIn(UHandlerImage* handler, int id);
	void fadeOut(UHandlerImage* handler, int id);

	////////////////////////////////
	///// fields and components ////
	///////////////////////////////
	TWeakObjectPtr<UCustomGameInstance> _Instance;
	bool _bAvaliableImages;
	EMagneticType LLast, RLast;

	UPROPERTY()
	UHandlerImage* _magL;

	UPROPERTY()
	UHandlerImage* _magR;
	
};

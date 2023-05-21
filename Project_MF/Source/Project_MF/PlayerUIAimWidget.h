// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIHandler.h"
#include "PlayerUIAimWidget.generated.h"

class UImage;
class UCustomGameInstance;
class UMagneticComponent;
enum class EMagneticType : uint8;

UENUM()
enum class EGivenAnimType : uint8
{
	NONE,
	ADDTIVE,
	SUBTRACT
};

USTRUCT()
struct FGivenImgInfo
{
	GENERATED_BODY()

	EGivenAnimType ApplyAimType	= EGivenAnimType::NONE;
	EMagneticType CurrType		= EMagneticType::NONE;
	float ApplyCurrTime			= 0.f;
	float GoalTimeDiv			= 0.f;

	EGivenAnimType NextAimType = EGivenAnimType::NONE;
	EMagneticType NextType	  = EMagneticType::NONE;

	FVector2D OriginPos;
	UImage* BlueImg;
	UImage* RedImg;

	UImage* GetImgByMagType() const;
	void SetImgOpacityByMagType();
};


/**
 * 플레이어 UI의 애임에 대한 UI를 담당합니다.
 */
UCLASS()
class PROJECT_MF_API UPlayerUIAimWidget : public UUserWidget, public IGameUIHandler
{
	GENERATED_BODY()

public:
	//////////////////////////////
	////    Public methods   ////
	/////////////////////////////
	void SetAimUIByMagneticComp(UMagneticComponent* typeL, UMagneticComponent* typeR, bool playerMagChange = false);
	void SetAimUIByMagneticType(EMagneticType typeL, EMagneticType typeR, bool playerMagChange = false);


	//////////////////////////////
	////   override methods   ///
	/////////////////////////////
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual float GetAlpha() const override;
	virtual void SetAlpha(float newAlpha) override;

	virtual FLinearColor GetColor() const override;
	virtual void SetColor(FLinearColor newColor) override;


	///////////////////////////////
	////   Private methods    /////
	///////////////////////////////
private:
	void GivenAnimProgress(FGivenImgInfo& info, float DeltaTime);


	////////////////////////////////////
	////    Fields and Components  ////
	///////////////////////////////////
	bool _bIsInit = false;
	UImage *_PlayerCircle_Red, *_PlayerCircle_Blue;
	FGivenImgInfo _GivenInfoL, _GivenInfoR;

	UPROPERTY(EditAnywhere, Category = PlayerAim, Meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	float MagGivenApplySeconds= .2f;

	UPROPERTY(EditAnywhere, Category = PlayerAim, Meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	float PlayerGivenApplySeconds = .2f;
};

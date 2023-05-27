// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIHandler.h"
#include "PlayerUIAimWidget.generated.h"

class UHandlerImage;
class UImage;
class UCustomGameInstance;
class UMagneticComponent;
class UGameUIManager;
enum class EMagneticType : uint8;

constexpr int AIML_FADE_ID =  36;
constexpr int AIMR_FADE_ID = 37;

UENUM()
enum class EGivenAnimType : uint8
{
	NONE,
	ADDTIVE,
	SUBTRACT
};

USTRUCT()
struct FAimImgInfo
{
	GENERATED_BODY()

	EMagneticType CurrType = EMagneticType::NONE;
	EMagneticType NextType = EMagneticType::NONE;
	UHandlerImage* BlueImg;
	UHandlerImage* RedImg;

	float ApplyCurrTime	= 0.f;
	float GoalTimeDiv	= 0.f;
	bool IsAddtive = false;

	UHandlerImage* GetImgByMagType() const;
	void SetAllImgOpacityZero();
	void SetImgVisibleByMagType();
};

USTRUCT()
struct FPlayerCircleInfo : public FAimImgInfo
{
	GENERATED_BODY()

	FVector2D StartScale, DistanceScale, DefaultScale;
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
	void SetAimUIByMagneticComp(UMagneticComponent* typeL, UMagneticComponent* typeR, EMagneticType playerType = EMagneticType::NONE);
	void SetAimUIByMagneticType(EMagneticType typeL, EMagneticType typeR, EMagneticType playerType=EMagneticType::NONE);


	//////////////////////////////
	////   override methods   ///
	/////////////////////////////
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	virtual float GetAlpha() const override;
	virtual void SetAlpha(float newAlpha) override;

	virtual FLinearColor GetColor() const override;
	virtual void SetColor(FLinearColor newColor) override;


	///////////////////////////////
	////   Private methods    /////
	///////////////////////////////
private:
	void PlayerGivenAnimProgress(float DeltaTime);
	void PlayerGivenAEProgress(float DeltaTime);

	UFUNCTION()
	void FadeChange(bool isDark, int id);


	////////////////////////////////////
	////    Fields and Components  ////
	///////////////////////////////////
	TWeakObjectPtr<UGameUIManager> _UIManager;
	FDelegateHandle _FadeDelegateHandle;

	/**각 에임 이미지에 대한 참조 및 러프 정보가 담긴 필드들입니다.*/
	FAimImgInfo _GivenInfoL, _GivenInfoR;
	FPlayerCircleInfo _PlayerCircle;
	FPlayerCircleInfo _PlayerCircleAE;

	/**플레이어 원형 이펙트 애니메이션에 필요한 필드입니다.*/
	EMagneticType _PlayerType = EMagneticType::NONE;
	FVector2D _startCircleScale, _goalCircleScale;

	/**자성 부여시 나타거나*/
	UPROPERTY(EditAnywhere, Category = PlayerAim, Meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	float MagGivenApplySeconds= .2f;

	UPROPERTY(EditAnywhere, Category = PlayerAim, Meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	float PlayerGivenApplySeconds = .3f;

	UPROPERTY(EditAnywhere, Category = PlayerAim, Meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	float PlayerGivenAEApplySeconds = .25f;
};

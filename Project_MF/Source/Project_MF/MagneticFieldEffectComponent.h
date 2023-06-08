// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "MagneticFieldEffectComponent.generated.h"

enum class EMagneticType : uint8;

constexpr const float MAGNETIC_FIELD_RADIUS_DEFAULT = 120.488693f;
constexpr const float MAGNETIC_FIELD_RADIUS_DIV = 1.f / MAGNETIC_FIELD_RADIUS_DEFAULT;

constexpr const TCHAR* FIELD_EFFECT_SCALE_PARAM			 = TEXT("effect_scale");
constexpr const TCHAR* FIELD_EFFECT_COLOR_MATERIAL_PARAM = TEXT("ScopeMaterial");
constexpr const TCHAR* FIELD_EFFECT_MAIN_MAT_COLOR_PARAM = TEXT("color");

/**
 * 자기장 나이아가라 이펙트에 대한 효과들을 담당하는 컴포넌트입니다.
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (MagneticEffect), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UMagneticFieldEffectComponent final : public UNiagaraComponent
{
	GENERATED_BODY()

public:
	/////////////////////////
	///    Constructor    ///
	/////////////////////////
	UMagneticFieldEffectComponent();


	///////////////////////////////
	////   Public methods    /////
	//////////////////////////////
	void SetMagneticFieldInfo(EMagneticType fieldType, float fieldRadius);
	EMagneticType GetFieldMagneticType() const { return _CurrMagType; }


	////////////////////////////
	///   Override methods  ///
	///////////////////////////
private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaSeconds, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//////////////////////////////
	////   Private methods  /////
	////////////////////////////
	void SetFieldScaleParameter( float newScale );


	/////////////////////////////////
	////  Fields and Components  ///
	////////////////////////////////
	float _ProgressTime	= 0.f,
		  _StartRadius	= 0.f,
		  _GoalRadius	= 0.f,
		  _TakeGoalTimeDiv = 0.f;

	TWeakObjectPtr<UCurveFloat> _UsedCurve;
	EMagneticType _CurrMagType;

	UPROPERTY()
	UMaterialInstanceDynamic* MainMaterialIns;

	/**효과 적용에 걸리는 시간을 나타내는 필드입니다.*/
	UPROPERTY(EditAnywhere, Category = MagneticFieldEffectSetting, Meta = (AllowPrivateAccess = true))
	float FieldStartTakeTime = 2.f;

	UPROPERTY(EditAnywhere, Category = MagneticFieldEffectSetting, Meta = (AllowPrivateAccess = true))
	float FieldEndTakeTime = 2.f;

	UPROPERTY(EditAnywhere, Category = MagneticFieldEffectSetting, Meta = (AllowPrivateAccess = true))
	float FieldScaleUpDownTime = 0.4f;

	/**효과 적용에 쓰이는 에셋의 참조입니다.*/
	UPROPERTY(EditAnywhere, Category = MagneticFieldEffect, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* EffectMainMaterial;

	UPROPERTY(EditAnywhere, Category = MagneticFieldEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* EffectAsset;

	UPROPERTY(EditAnywhere, Category=MagneticFieldEffectCurve, Meta=(AllowPrivateAccess=true))
	UCurveFloat* StartCurveAsset;

	UPROPERTY(EditAnywhere, Category = MagneticFieldEffectCurve, Meta = (AllowPrivateAccess = true))
	UCurveFloat* EndCurveAsset;
	
};

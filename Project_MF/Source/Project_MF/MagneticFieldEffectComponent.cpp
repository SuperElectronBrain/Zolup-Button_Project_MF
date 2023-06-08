#include "MagneticFieldEffectComponent.h"
#include "NiagaraDataInterfaceCurve.h"
#include "MagneticComponent.h"
#include "Curves/CurveVector.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"

UMagneticFieldEffectComponent::UMagneticFieldEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	/**CDO - 사용할 이펙트 및 머터리얼 에셋들을 불러옵니다.*/
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EFFECT_ASSET(
		TEXT("/Game/Effect/Magnetic/Field/magnet_scope_grow_big_nia.magnet_scope_grow_big_nia")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MAIN_COLOR_MATERIAL(
		TEXT("/Game/Effect/Magnetic/Field/magnet_scope_m.magnet_scope_m")
	);

	/**CDO - 필요한 모든 커브 에셋들을 불러옵니다.*/
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CURVE_START(
		TEXT("/Game/Effect/Magnetic/Field/FieldStartCurve")
	);
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CURVE_END(
		TEXT("/Game/Effect/Magnetic/Field/FieldEndCurve")
	);

	/**Apply - 에셋 적용.*/
	if (EFFECT_ASSET.Succeeded()) EffectAsset = EFFECT_ASSET.Object;
	if (CURVE_START.Succeeded()) StartCurveAsset = CURVE_START.Object;
	if (CURVE_END.Succeeded()) EndCurveAsset = CURVE_END.Object;
	if (MAIN_COLOR_MATERIAL.Succeeded()) EffectMainMaterial = MAIN_COLOR_MATERIAL.Object;

	///**기본값 세팅.*/
	_CurrMagType = EMagneticType::NONE;
	bAutoActivate = true;
	SetAutoDestroy(false);
	bAllowAnyoneToDestroyMe = true;
	SetVisibleInRayTracing(false);
}

void UMagneticFieldEffectComponent::TickComponent(float DeltaSeconds, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	float progressRatio = FMath::Clamp((_ProgressTime * _TakeGoalTimeDiv), 0.f, 1.f);
	bool  isComplete	= (progressRatio >= 1.f);

	/**자기장 생성/사라짐 효과*/
	if (_UsedCurve.IsValid())
	{
		float curveScale = _UsedCurve->GetFloatValue(progressRatio);

		SetFieldScaleParameter(_GoalRadius * curveScale);
		if (isComplete) _UsedCurve.Reset();
	}
	/**자기장 크기 변환 효과*/
	else {

		float addScale = (_GoalRadius - _StartRadius) * progressRatio;
		SetFieldScaleParameter( _StartRadius + addScale );
	}

	if (isComplete) SetComponentTickEnabled(false);
	_ProgressTime += DeltaSeconds;
}

void UMagneticFieldEffectComponent::SetFieldScaleParameter(float newScale)
{
	SetVectorParameter(
		FIELD_EFFECT_SCALE_PARAM,
		FVector::OneVector * (newScale * MAGNETIC_FIELD_RADIUS_DIV)
	);
}

void UMagneticFieldEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	if (EffectAsset)
	{
		SetAsset(EffectAsset);
		SetFieldScaleParameter(0.f);
	}

	//새로운 머터리얼을 적용한다.
	if (EffectMainMaterial && MainMaterialIns==false)
	{
		MainMaterialIns = UMaterialInstanceDynamic::Create(EffectMainMaterial, this);
		SetVariableMaterial(FIELD_EFFECT_COLOR_MATERIAL_PARAM, MainMaterialIns);
	}

	SetComponentTickEnabled(false);
}

void UMagneticFieldEffectComponent::SetMagneticFieldInfo(EMagneticType fieldType, float fieldRadius)
{
	bool bChangeFieldType	= (_CurrMagType != fieldType);
	bool bChangeFieldScale  = (_GoalRadius != fieldRadius);
	bool bConstructField	= (_CurrMagType == EMagneticType::NONE && fieldType != EMagneticType::NONE) ||
		                      (_CurrMagType!=EMagneticType::NONE && fieldType!=EMagneticType::NONE && bChangeFieldType);
	bool bDestructField		= (_CurrMagType != EMagneticType::NONE && fieldType == EMagneticType::NONE) || (fieldRadius<=0.f);

	/**자기장이 사라질 경우*/
	if (bDestructField)
	{
		_GoalRadius = fieldRadius;
		_ProgressTime = 0.f;
		_TakeGoalTimeDiv = 1.f / FieldEndTakeTime;
		_UsedCurve.Reset();
		_UsedCurve = EndCurveAsset;
		SetFieldScaleParameter(0.f);
	}
	/**자기장이 생성될 경우*/
	else if (bConstructField)
	{
		_GoalRadius = fieldRadius;
		_ProgressTime = 0.f;
		_TakeGoalTimeDiv = 1.f / FieldStartTakeTime;
		_UsedCurve.Reset();
		_UsedCurve = StartCurveAsset;
	}
	/**자기장 크기만 변경될 경우*/
	else if(bChangeFieldScale)
	{
		_TakeGoalTimeDiv = 1.f / FieldScaleUpDownTime;
	}

	/**색깔을 변경한다.*/
	if (MainMaterialIns && fieldType!=EMagneticType::NONE) {

		MainMaterialIns->SetVectorParameterValue(
			FIELD_EFFECT_MAIN_MAT_COLOR_PARAM,
			UMagneticComponent::GetMagneticEffectColor(fieldType, EMagneticEffectColorType::RING_EFFECT)
		);

	}

	_CurrMagType = fieldType;
	_StartRadius = _GoalRadius;
	_GoalRadius = fieldRadius;
	_ProgressTime = 0.f;
	SetComponentTickEnabled(true);
}
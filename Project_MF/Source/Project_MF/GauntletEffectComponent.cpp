#include "GauntletEffectComponent.h"
#include "MagneticComponent.h"

UGauntletEffectComponent::UGauntletEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	/************************************************
	*	( CDO )
	*	사용할 이펙트 및 머터리얼 에셋들을 불러옵니다.
	***/
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EFFECT_ASSET(
		TEXT("/Game/Effect/Magnetic/Gauntlet/Glove_effect_n_fix.Glove_effect_n_fix")
	);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DISTORTION_MATERIAL(
		TEXT("/Game/Effect/Magnetic/Gauntlet/Glove_effect_distortion_material.Glove_effect_distortion_material")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> THUNDER_MATERIAL(
		TEXT("/Game/Effect/Magnetic/Gauntlet/Glove_thunder_material.Glove_thunder_material")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ONE_MATERIAL(
		TEXT("/Game/Effect/Magnetic/Gauntlet/Glove_effect_01_material.Glove_effect_01_material")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TWO_MATERIAL(
		TEXT("/Game/Effect/Magnetic/Gauntlet/Glove_effect_02_matetial.Glove_effect_02_matetial")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> THREE_MATERIAL(
		TEXT("/Game/Effect/Magnetic/Gauntlet/Glove_effect_03_material.Glove_effect_03_material")
	);

	if (EFFECT_ASSET.Succeeded()) GauntletEffect = EFFECT_ASSET.Object;
	if (DISTORTION_MATERIAL.Succeeded()) DisortionMaterial = DISTORTION_MATERIAL.Object;
	if (THUNDER_MATERIAL.Succeeded())	 ThunderMaterial = THUNDER_MATERIAL.Object;
	if (ONE_MATERIAL.Succeeded())  OneMaterial = ONE_MATERIAL.Object;
	if (TWO_MATERIAL.Succeeded())  TwoMaterial = TWO_MATERIAL.Object;
	if (THREE_MATERIAL.Succeeded()) ThreeMaterial = THREE_MATERIAL.Object;

	///**기본값 세팅.*/
	_CurrMagType = EMagneticType::NONE;
	bAutoActivate = true;
	SetAutoDestroy(false);
	bAllowAnyoneToDestroyMe = true;
	SetVisibleInRayTracing(false);
}

void UGauntletEffectComponent::CreateMaterialInsAndInitParam(UMaterialInterface* source, UMaterialInstanceDynamic*& Out, FName initParamName)
{
	if (source)
	{
		Out = UMaterialInstanceDynamic::Create(source, this);
		SetVariableMaterial(initParamName, Out);
	}
}

void UGauntletEffectComponent::SetGauntletEffectScaleAndDepth(float newScaleAndDepth)
{
	if (DisortionMaterialInstance)
	{
		DisortionMaterialInstance->SetScalarParameterValue(GAUNTLET_EFFECT_SCALE_AND_DEPTH_PARAM, newScaleAndDepth);
	}

	if (ThunderMaterialInstance)
	{
		ThunderMaterialInstance->SetScalarParameterValue(GAUNTLET_EFFECT_CIRCLE_SCALE_PARAM, newScaleAndDepth);
	}

	if (OneMaterialInstance)
	{
		OneMaterialInstance->SetScalarParameterValue(GAUNTLET_EFFECT_SCALE_AND_DEPTH_PARAM, newScaleAndDepth);
	}

	if (TwoMaterialInstance)
	{
		TwoMaterialInstance->SetScalarParameterValue(GAUNTLET_EFFECT_SCALE_AND_DEPTH_PARAM, newScaleAndDepth);
	}

	if (ThreeMaterialInstance)
	{
		ThreeMaterialInstance->SetScalarParameterValue(GAUNTLET_EFFECT_SCALE_AND_DEPTH_PARAM, newScaleAndDepth);
	}
}

void UGauntletEffectComponent::SetGauntletEffectInfo(EMagneticType effectType, float effectScale)
{
	bool bChangedType = (effectType != _CurrMagType);

	//색깔 적용
	if (effectType!=EMagneticType::NONE)
	{
		SetColorParameter(
			GAUNTLET_EFFECT_CIRCLE_COLOR_PARAM,
			UMagneticComponent::GetMagneticEffectColor(effectType, EMagneticEffectColorType::GAUNTLET_SPHERE_EFFECT)
		);

		SetColorParameter(
			GAUNTLET_EFFECT_THUNDER_COLOR_PARAM,
			UMagneticComponent::GetMagneticEffectColor(effectType, EMagneticEffectColorType::GAUNTLET_THUNDER_EFFECT)
		);
	}

	_GoalScale = effectScale;
	_CurrScale = 0.02f;
	SetComponentTickEnabled(true);
}

void UGauntletEffectComponent::TickComponent(float DeltaSeconds, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//크기를 적용한다.
	_CurrScale += DeltaSeconds * .2f * (_GoalScale - _CurrScale);

	//자성이 없고, 크기가 0일 경우.
	if (_CurrMagType==EMagneticType::NONE && _CurrScale <= 0.01f)
	{
		_CurrScale = 0.f;
		SetComponentTickEnabled(false);
	}

	//최종 적용
	SetNiagaraVariableVec2(GAUNTLET_EFFECT_CIRCLE_SCALE_PARAM, FVector2D(400.f, 400.f) * _CurrScale);
	SetNiagaraVariableVec2(GAUNTLET_EFFECT_THUNDER_SCALE_PARAM, FVector2D(200.f, 50.f) * _CurrScale);
	SetVectorParameter(GAUNTLET_EFFECT_MESH_SCALE_PARAM, FVector(5.f, 5.f, 5.f) * _CurrScale);
}

void UGauntletEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	//이펙트 생성
	if (GauntletEffect) SetAsset(GauntletEffect);

	//머터리얼 생성 및 적용
	CreateMaterialInsAndInitParam(DisortionMaterial, DisortionMaterialInstance, GAUNTLET_EFFECT_DISORTION_PARAM);
	CreateMaterialInsAndInitParam(ThunderMaterial, ThunderMaterialInstance, GAUNTLET_EFFECT_THUNDER_PARAM);
	CreateMaterialInsAndInitParam(OneMaterial, OneMaterialInstance, GAUNTLET_EFFECT_ONE_PARAM);
	CreateMaterialInsAndInitParam(TwoMaterial, TwoMaterialInstance, GAUNTLET_EFFECT_TWO_PARAM);
	CreateMaterialInsAndInitParam(ThreeMaterial, ThreeMaterialInstance, GAUNTLET_EFFECT_THREE_PARAM);

	SetComponentTickEnabled(false);
	SetGauntletEffectInfo(EMagneticType::NONE, 0.f);
}
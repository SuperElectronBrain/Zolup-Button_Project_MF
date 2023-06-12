// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GauntletEffectComponent.generated.h"

enum class EMagneticType : uint8;

constexpr const TCHAR* GAUNTLET_EFFECT_DISORTION_PARAM	= TEXT("GloveEffectDisortion");
constexpr const TCHAR* GAUNTLET_EFFECT_THUNDER_PARAM	= TEXT("GloveEffectThunder");
constexpr const TCHAR* GAUNTLET_EFFECT_ONE_PARAM	= TEXT("GloveEffect01");
constexpr const TCHAR* GAUNTLET_EFFECT_TWO_PARAM	= TEXT("GloveEffect02");
constexpr const TCHAR* GAUNTLET_EFFECT_THREE_PARAM	= TEXT("GloveEffect03");

constexpr const TCHAR* GAUNTLET_EFFECT_CIRCLE_SCALE_PARAM = TEXT("circlescale");
constexpr const TCHAR* GAUNTLET_EFFECT_THUNDER_SCALE_PARAM = TEXT("thunderScale");
constexpr const TCHAR* GAUNTLET_EFFECT_MESH_SCALE_PARAM = TEXT("meshScale");

constexpr const TCHAR* GAUNTLET_EFFECT_CIRCLE_COLOR_PARAM = TEXT("CircleColor");
constexpr const TCHAR* GAUNTLET_EFFECT_THUNDER_COLOR_PARAM = TEXT("thunterColor");
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (MagneticEffect), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UGauntletEffectComponent final : public UNiagaraComponent
{
	GENERATED_BODY()
	
public:
	/////////////////////////////////////////
	/////								////
	////		*Constructor*			////
	///									///
	//////////////////////////////////////
	UGauntletEffectComponent();


	/////////////////////////////////////////
	/////								////
	////		 Public methods			////
	///									///
	//////////////////////////////////////
	void SetGauntletEffectInfo(EMagneticType effectType, float effectScale);
	EMagneticType GetGauntletEffectType() const { return _CurrMagType; }


	/////////////////////////////////////////
	/////								////
	////	   Override methods			////
	///									///
	//////////////////////////////////////
private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaSeconds, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/////////////////////////////////////////
	/////								////
	////	   Private methods			////
	///									///
	//////////////////////////////////////	
	inline void CreateMaterialInsAndInitParam( UMaterialInterface* source, UMaterialInstanceDynamic*& Out, FName initParamName );


	/////////////////////////////////////////
	/////								////
	////	 Fields and Components	    ////
	///									///
	//////////////////////////////////////
	EMagneticType _CurrMagType;
	float _GoalScale = 0.f;
	float _CurrScale = 0.f;

	/****************************************************
	*	이 컴포넌트의 이펙트에서 사용되는 에셋들의 참조값들입니다.
	**/
	UPROPERTY(EditAnywhere, Category = GauntletEffectSetting, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* DisortionMaterial;

	UPROPERTY(EditAnywhere, Category = GauntletEffectSetting, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* ThunderMaterial;

	UPROPERTY(EditAnywhere, Category = GauntletEffectSetting, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* OneMaterial;

	UPROPERTY(EditAnywhere, Category = GauntletEffectSetting, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* TwoMaterial;

	UPROPERTY(EditAnywhere, Category = GauntletEffectSetting, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* ThreeMaterial;


	UPROPERTY(EditAnywhere, Category = GauntletEffectSetting, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* GauntletEffect;


	/******************************************************
	*	이 컴포넌트의 이펙트에서 사용되는 머터리얼 인스턴스입니다.
	***/
	UPROPERTY()
	UMaterialInstanceDynamic* DisortionMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* ThunderMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* OneMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* TwoMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* ThreeMaterialInstance;

};

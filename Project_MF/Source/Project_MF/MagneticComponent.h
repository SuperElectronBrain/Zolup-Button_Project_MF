#pragma once
#include "EngineMinimal.h"
#include "MagneticMovementComponent.h"
#include "MagneticComponent.generated.h"

class USceneComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UMagneticMovementComponent;
class UMagneticComponent;
enum class EMagneticType : uint8;

/**
*자석 컴포넌트가 가지는 자성의 종류에 대한 열거형입니다.
*/
UENUM(BlueprintType)
enum class EMagneticType : uint8
{
	NONE, S, N
};

/**
*자성 이펙트들이 가질 수 있는 색깔을 종류별로 가져오는데 필요한 열거형입니다.
*/
UENUM()
enum class EMagneticEffectColorType : uint8
{
	RING_EFFECT,
	GUN_EFFECT_LAZER,
	GUN_EFFECT_SPARK_MAX,
	GUN_EFFECT_SPARK_MIN,
	GUN_SHOOT_EFFECT_MIN,
	GUN_SHOOT_EFFECT_MAX,
	GRANT_EFFECT,
	ELECTRIC_VIGNETTING_EFFECT,
	GAUNTLET_SPHERE_EFFECT,
	GAUNTLET_THUNDER_EFFECT
};

/*해당 컴포넌트에서 쓰이는 컴파일 전용 상수다.*/
constexpr const int					MAGNETIC_FIELD_PRECISION		= 60;
constexpr const ECollisionChannel	MAGNETIC_COLLISION_OBJECTTYPE	= ECollisionChannel::ECC_GameTraceChannel11;
constexpr const TCHAR*				MAGNETIC_COLLISION_PROFILE		= TEXT("MagneticField");

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FComponentMagneticChanged, EMagneticType, changedMagType, UMagneticComponent*, changedMagComp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FComponentMagnetBeginMovement, EMagnetMoveType, moveType, UMagneticComponent*, moveBeginMagComp, UMagneticComponent*, operatorMagComp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FComponentMagnetEndMovement, EMagnetMoveType, prevMoveType, UMagneticComponent*, moveEndMagComp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FComponentMagnetMoveHit, AActor*, HitActor, UMagneticComponent*, HitMagComp, FVector, hitNormal);

/**엔진 충돌 설정
* 기본적으로, ObjectType은 MagneticField를 사용하고,
* CollisionProfile도 MagneticField로 설정한다.
* CollisionProfile은 MagneticField만 겹침으로, 나머지는 다 무시로 설정.
*/

/**
* 자성 및 주변의 자석을 탐지하는 기능을 가지게 됩니다.
* 이 컴포넌트가 UMeshComponent계열 컴포넌트에 붙여지면 자성에 따라 해당 메시의 머터리얼이
* 바뀌게 되며, 해당 메시의 바운딩 박스의 크기에 따라 무게 및 자기장 범위가 결정됩니다.
* 이 컴포넌트가 부착된 같은 엑터에 UMagneticMovementComponent계열의 컴포넌트가 부착되어 있을 경우,
* 주변의 자석에 영향을 받게 될 때 해당 UMagneticMovmentComponent에 정의된 움직임으로 밀려나거나 끌어당겨지게 됩니다.
*/
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Magnetic), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UMagneticComponent final : public USceneComponent
{
	GENERATED_BODY()

public:
	////////////////////////////
	////     Constructor   /////
    ////////////////////////////
	UMagneticComponent();


	/////////////////////////////
	///   Public delegates    ///
	////////////////////////////

	/**부여된 자성의 극이 바뀌었을 때 호출되는 델리게이트입니다.*/
	UPROPERTY(BlueprintAssignable, Blueprintcallable, Category = "Magnetic")
	FComponentMagneticChanged OnComponentMagneticChanged;

	/**해당 자석이 다른 자성에 의해 움직임을 시작했을 때 호출되는 델리게이트입니다.*/
	UPROPERTY(BlueprintAssignable, Blueprintcallable, Category = "Magnetic")
	FComponentMagnetBeginMovement OnComponentMagnetBeginMovement;

	/**해당 자석이 다른 자성에 의해 움직이다가 멈췄을 때 호출되는 델리게이트입니다.*/
	UPROPERTY(BlueprintAssignable, Blueprintcallable, Category = "Magnetic")
	FComponentMagnetEndMovement OnComponentMagnetEndMovement;

	/**해당 자석이 다른 자성에 의해 움직이다가 부딫혔을 때 호출되는 델리게이트입니다.*/
	UPROPERTY(BlueprintAssignable, Blueprintcallable, Category = "Magnetic")
	FComponentMagnetMoveHit OnComponentMagnetMoveHit;


	/////////////////////////////////
	////    Public methods       ////
	////////////////////////////////

	/**
	* 해당 자석의 무게와 자기장 범위를 계산하고 갱신합니다.
	* 만약 이 컴포넌트가 부착된 곳이 MeshComponent 계열일 경우, 메시의  바운딩 박스를 기준으로 계산됩니다.
	*/
	UFUNCTION(BlueprintCallable, Category=Magnetic)
	void SettingMagnetWeightAndFieldRange();

	/**Get 해당 자석의 최대 강화횟수를 얻습니다.*/
	UFUNCTION(BlueprintCallable, Category = Magnetic)
	int32 GetMaxEnchantableCount() const { return MaxEnchantableCount; }

	/**Get 해당 자석이 강회되어있는 횟수를 얻습니다.*/
	UFUNCTION(BlueprintCallable, Category = Magnetic)
	int32 GetCurrEnchantableCount() const { return CurrEnchantCount; }

	/**
	*  해당 자석의 인챈트 정보를 지정합니다.
	* 
	*  @param maxEnchantCount	이 자석이 강화될 수 있는 최대 횟수입니다.
	*  @param enchantWeight		이 자석이 강화될 때마다 증가할 무게값입니다.
	*  @param enchantRange		이 자석이 강화될 때마다 증가할 자기장 범위값입니다. 
	*/
	UFUNCTION(BlueprintCallable, Category = Magnetic)
	void SetEnchantInfo(int32 maxEnchantCount, float enchantWeight, float enchantRange);

	/**
	*  해당 자석의 자성을 변경합니다.
	*  변경된 자성에 알맞는 효과가 메시들에게 적용됩니다. - 이 컴포넌트가 UMeshComponent계열에 부착되어있을 때만 적용됨.
	* 
	*  @param newType	변경할 자성의 타입입니다.
	*/
	UFUNCTION(BlueprintCallable, Category = Magnetic)
	void SetCurrentMagnetic(EMagneticType newType);

	/*Get 해당 자석에게 부여되어 있는 자성의 극을 얻습니다.*/
	EMagneticType GetCurrentMagnetic() const { return CurrMagnetic; }

	/*Get 해당 자석이 자성을 띄고 있을 수 있는 최대 시간값을 얻습니다.*/
	float GetMaxHaveMangeticSeconds() const { return MaxHaveMagneticSeconds; }
	
	/**
	* 해당 자석이 부여된 자성을 가질 수 있는 최대시간을 지정합니다.
	* 
	* @param newValue	변경할 최대 시간값입니다.
	*/
	UFUNCTION(BlueprintCallable, Category = Magnetic)
	void SetMaxHaveMagneticSeconds(float newValue) { if (newValue >= 0.f) MaxHaveMagneticSeconds = newValue; }

	/*Get 해당 자석의 무게를 얻어옵니다.*/
	UFUNCTION(BlueprintCallable, Category = Magnetic)
	float GetWeight() const { return Weight; }

	/**
	* 해당 자석의 무게를 임의로 지정합니다. 임의로 지정한 무게는 일부 상황에서,
	* 메시 무게 추산기능으로 값이 바뀔 수 있습니다. 이부분은 고정 무게를 설정함으로써 해결할 수 있습니다.
	* 
	* @param value	새롭게 지정할 무게값입니다.
	* @param usedFixedWeight  고정 무게를 설정할 것인지에 대한 값입니다.
	*/
	UFUNCTION(BlueprintCallable, Category=Magnetic)
	void SetWeight(float value, bool usedFixedWeight);

	/**해당 자석의 자기장의 반지름을 얻어옵니다.*/
	UFUNCTION(BlueprintCallable, Category=Magnetic)
	float GetMagneticFieldRadius() const { return FieldCollision->GetScaledSphereRadius(); }

	/*Get 해당 자석의 자기장 범위 배율을 얻습니다.*/
	float GetMagneticFieldRadiusScale() const { return MagneticFieldRadiusScale; }

	/**
	* 해당 자석의 자기장 반지름 배율을 설정합니다. 이 값에 비례해서 자기장의 크기가 조절됩니다.
	*
	* @param newValue  새롭게 지정할 자기장 반지름 배율값입니다. 
	*/
	UFUNCTION(BlueprintCallable, Category=Magnetic)
	void SetMagneticFieldRadiusScale(float newValue);

	/*Get 자기장의 위치를 얻어옵니다.*/
	FVector GetMagneticFieldLocation() const { return FieldCollision->GetComponentLocation(); }

	static FLinearColor GetMagneticEffectColor(EMagneticType type, EMagneticEffectColorType effect);

	/*Get 이 컴포넌트가 부착되어 있는 PrimitiveComponent를 얻어옵니다.*/
	UPrimitiveComponent* GetAttachmentPrimitive() const { return _parent; }

private:
	////////////////////////////////////
	/////    Override methods     //////
	///////////////////////////////////
	virtual void OnAttachmentChanged() override;
	virtual void BeginPlay() override;
	virtual bool CanAttachAsChild(const USceneComponent* ChildComponent, FName SocketName) const override;
	virtual void DestroyComponent(bool bPromoteChilderen) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif


	///////////////////////////////////
	//////   Private methods    ///////
	///////////////////////////////////
	void UpdateMagneticField();
	void UpdateFieldMeshsColor(EMagneticType type);
	void ClearMagneticField();

	void InitParentAndMaterial();
	void SetParentMaterial(EMagneticType type);


	///////////////////////////////
	//// Fields and Components ////
	///////////////////////////////
	float _RotCounter = FMath::DegreesToRadians(360.f / MAGNETIC_FIELD_PRECISION); 
	float _applyRadius = 0.f, _goalRadius = 0.f;
	float _currMagMaterialApplyRatio=0.f, _goalMagMaterialApplyRatio = 0.f;
	float _magFieldDiv = 1.f / 1000.f;
	bool _magActivate = false;
	EMagnetMoveType _lastMoveType = EMagnetMoveType::NONE;
	bool _applyMovement = true;
	UMagneticMovementComponent* _movement;

	UPROPERTY()
	UPrimitiveComponent* _parent;

	UPROPERTY()
	UMeshComponent* _parentMesh;

	UPROPERTY(EditAnywhere, Category = Magnetic, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	EMagneticType CurrMagnetic = EMagneticType::NONE;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	bool bCanChangeMagnetic = true;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	float CurrHaveMagneticSeconds = 0.f;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float MaxHaveMagneticSeconds = 20.f;

	UPROPERTY()
	UNiagaraSystem* MagneticFieldEffect;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AccessPrivateAccess = true))
	UNiagaraComponent* MagneticFieldEffectComp;

	UPROPERTY(EditAnywhere, Category=Magnetic, Meta=(AccessPrivateAccess=true))
	UMaterialInterface* MagneticApplyMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* _material;

	UPROPERTY()
	USphereComponent* FieldCollision;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float FinalMagneticFieldRadius = 0.f;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float MagneticFieldRadiusScale = 5.f;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float Weight = 0.f;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	bool bUsedFixedWeight = false;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	int32 CurrEnchantCount = 0;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (ClampMin = 1, AllowPrivateAccess = true))
	int32 MaxEnchantableCount = 0;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	float EnchantWeight = 0.f;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	float EnchantRange = 0.f;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	bool bShowMagneticFieldSphereInGame=false;

public:

	/**
	* 자기장 필드를 화면에 표시할지에 대한 여부입니다.
	* true일 경우 인 게임중에 자기장이 표시됩니다.
	*/
	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool bShowMagneticField = true;

	/**
	* 주변 자성에 의해 영향을 받게 될 경우, 움직임을 구현할지에 대한 여부입니다.
	* true일 경우 이 Component와 같은 Actor에 부착된 UMagneticMovementComponent의 움직임을 적용합니다.
	*/
	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool bAllowMagneticMovement = true;

	/**
	* 자성 머터리얼을 이 Component가 부착된 Mesh에 적용할지에 대한 여부입니다.
	* true일 경우 부착된 UMeshComponent의 머터리얼이 이 Component에 지정한 Material로 변경됩니다.
	*/
	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool bMagneticMaterialApplyAttachMesh = true;

	/**
	* 이 컴포넌트의 자성 움직임이 마무리될 때, 원상복귀될 부착된 엑터의 가장 최상위 UPrimitiveComponent의
	* 중력 사용 여부입니다.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	bool bDefaultPrimitiveGravity = false;

	/**
	* 자성을 영원히 보유하는지에 대한 여부를 결정합니다.
	* 만약 해당 값이 true일 경우, 자성 보유 시간이 감소되지 않게됩니다.
	*/
	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool bEternalHaveMagnetic = false;
};
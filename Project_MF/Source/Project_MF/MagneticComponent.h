// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "MagneticComponent.generated.h"

class USceneComponent;
class USplineComponent;
class USplineMeshComponent;
class UMagneticMovementComponent;
enum class EMagnetMoveType;

UENUM()
enum class EMagneticType
{
	NONE, S, N
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMagneticDelegate, EMagneticType)
DECLARE_MULTICAST_DELEGATE_OneParam(FOffMagneticDelegate, EMagneticType)
DECLARE_MULTICAST_DELEGATE_OneParam(FMoveStartDelegate, EMagnetMoveType)
DECLARE_MULTICAST_DELEGATE_OneParam(FMoveHitDelegate, AActor*)
DECLARE_MULTICAST_DELEGATE_OneParam(FMoveEndDelegate, EMagnetMoveType)

#define MAGNETIC_FIELD_PRECISION 60
#define MAGNETIC_COLLISION_OBJECTTYPE ECollisionChannel::ECC_GameTraceChannel11
#define MAGNETIC_COLLISION_PROFILE "MagneticField"

/*엔진 충돌 설정
기본적으로, ObjectType은 MagneticField를 사용하고,
CollisionProfile도 MagneticField로 설정한다.
CollisionProfile은 MagneticField만 겹침으로, 나머지는 다 무시로 설정.
*/

/*자성 및 주변의 자석을 탐지하는 기능을 가지게 됩니다.
* 이 컴포넌트가 UMeshComponent계열 컴포넌트에 붙여지면 자성에 따라 해당 메시의 머터리얼이
* 바뀌게 되며, 해당 메시의 바운딩 박스의 크기에 따라 무게 및 자기장 범위가 결정됩니다.
* 이 컴포넌트가 부착된 같은 엑터에 UMagneticMovementComponent계열의 컴포넌트가 부착되어 있을 경우,
* 주변의 자석에 영향을 받게 될 때 해당 UMagneticMovmentComponent에 정의된 움직임으로 밀려나거나 끌어당겨지게 됩니다.
*/
UCLASS(ClassGroup = (Magnetic), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UMagneticComponent final : public USceneComponent
{
	GENERATED_BODY()

public:
	/*Constructor*/
	UMagneticComponent();

	/*Delegates*/
	FOnMagneticDelegate			OnMagneticEvent;
	FOffMagneticDelegate		OffMagneticEvent;
	FMoveStartDelegate			MagnetMoveStartEvent;
	FMoveEndDelegate			MagnetMoveEndEvent;
	FMoveHitDelegate			MagnetMoveHitEvent;

	/*Public methods*/
	void SettingMagnetWeightAndFieldRange();

	int32 GetMaxEnchantableCount() const { return MaxEnchantableCount; }
	int32 GetCurrEnchantableCount() const { return CurrEnchantCount; }
	void SetEnchantInfo(int32 maxEnchantCount, float enchantWeight, float enchantRange );

	void SetCurrentMagnetic(EMagneticType newType);
	EMagneticType GetCurrentMagnetic() const { return CurrMagnetic; }

	float GetMaxHaveMangeticSeconds() const { return MaxHaveMagneticSeconds; }
	void SetMaxHaveMagneticSeconds(float newValue) { if (newValue >= 0.f) MaxHaveMagneticSeconds = newValue; }

	float GetWeight() const { return Weight; }
	void SetWeight(float value, bool usedFixedWeight) { if (value > 0.f) { Weight = value; _bUsedFixedWeight = usedFixedWeight; } }

	float GetMagneticFieldRadius() const { return FieldCollision->GetScaledSphereRadius(); }
	void SetMagneticFieldRadius(float newValue);

	bool GetEternalHaveMagnetic() const { return EternalHaveMagnetic; }
	void SetEternalHaveMagnetic(bool value) { EternalHaveMagnetic = value; }

	FVector GetMagneticFieldLocation() const { return FieldCollision->GetComponentLocation(); }

	static FLinearColor GetMagneticLinearColor(EMagneticType type);
	static FColor GetMagneticColor(EMagneticType type);
	static FVector GetMagneticColorVector(EMagneticType type);

	void AddNoActiveMovement(UMovementComponent* element);
	void RemoveNoActiveMovmeent(UMovementComponent* element);

private:
	/*Private method*/
	void UpdateMagneticField();
	void UpdateFieldMeshsColor(EMagneticType type);
	void ClearMagneticField();

	void InitParentAndMaterial();
	void SetParentMaterial(EMagneticType type);

	void SetNoActiveMovementsActive(bool value);

	/*Override methods*/
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual bool CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const override;
	virtual void DestroyComponent(bool bPromoteChilderen) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

	/*Fields and Components*/
	float _RotCounter, _applyRadius, _goalRadius;
	EMagnetMoveType _lastMoveType;
	bool _applyMovement, _bUsedFixedWeight, _blastUsedGravity;
	FVector _fieldColor;
	UMagneticMovementComponent* _movement;

	UPROPERTY()
	UPrimitiveComponent* _parent;

	UPROPERTY()
	UMeshComponent* _parentMesh;

	UPROPERTY()
	TArray<UMovementComponent*> _NoActiveMovements;

	UPROPERTY()
	TArray<USplineMeshComponent*> FieldMeshs;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	EMagneticType CurrMagnetic;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	bool bCanChangeMagnetic;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	float CurrHaveMagneticSeconds;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float MaxHaveMagneticSeconds;

	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool EternalHaveMagnetic;

	UPROPERTY()
	UStaticMesh* MagneticFieldMesh;

	UPROPERTY()
	UMaterialInterface* MagneticFieldMaterial;

	UPROPERTY()
	UMaterialInterface* MagneticApplyMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* _material;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UTexture2D* Texture;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	FLinearColor RGB;

	UPROPERTY()
	USphereComponent* FieldCollision;

	UPROPERTY()
	USplineComponent* FieldSpline;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float FinalMagneticFieldRadius;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float MagneticFieldRadiusScale;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float Weight;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	int32 CurrEnchantCount;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (ClampMin = 1, AllowPrivateAccess = true))
	int32 MaxEnchantableCount;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	float EnchantWeight;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	float EnchantRange;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	bool bShowMagneticFieldSphereInGame;

public:

	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool bShowMagneticField;

	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool bAllowMagneticMovement;

	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool bMagneticMaterialApplyAttachMesh;
};

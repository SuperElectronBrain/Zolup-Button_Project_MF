// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "MagneticComponent.generated.h"

class USceneComponent;
class UFloatingPawnMovement;
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

UPrimitiveComponent;

UCLASS( ClassGroup=(Magnetic), meta=(BlueprintSpawnableComponent) )
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

	void SetCurrentMagnetic(EMagneticType newType);
	EMagneticType GetCurrentMagnetic() const { return CurrMagnetic; }

	float GetMaxHaveMangeticSeconds() const { return MaxHaveMagneticSeconds; }
	void SetMaxHaveMagneticSeconds(float newValue) { if (newValue >= 0.f) MaxHaveMagneticSeconds = newValue; }
	
	float GetWeight() const {return Weight;}
	void SetFixedWeight(float value) { if (value > 0.f) { Weight = value; _bUsedFixedWeight = true; } }

	float GetMagneticFieldRadius() const { return FinalMagneticFieldRadius; }
	void SetMagneticFieldRadius(float newValue);

	bool GetEternalHaveMagnetic() const { return EternalHaveMagnetic; }
	void SetEternalHaveMagnetic(bool value);

	FVector GetMagneticFieldLocation() const { return FieldCollision->GetComponentLocation(); }

	static FLinearColor GetMagneticLinearColor(EMagneticType type);
	static FColor GetMagneticColor(EMagneticType type);
	static FVector GetMagneticColorVector(EMagneticType type);

	void AddNoActiveMovement(UMovementComponent* element);
	void RemoveNoActiveMovmeent(UMovementComponent* element);

private:
	/*Private method*/
	void UpdateMagneticField();
	void ClearMagneticField();
	void SetNoActiveMovementsActive(bool value);
	void SetChildMaterials(EMagneticType type);

	/*Override methods*/
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void DestroyComponent(bool bPromoteChilderen) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif

	/*Fields and Components*/
	float _RotCounter, _applyRadius, _goalRadius;
	EMagnetMoveType _lastMoveType;
	bool _applyMovement, _bUsedFixedWeight;
	FVector _fieldColor;
	UMagneticMovementComponent* _movement;

	UPROPERTY()
	TArray<UMeshComponent*> PrevMagnetsMaterials;

	UPROPERTY()
	TArray<UMovementComponent*> _NoActiveMovements;

	UPROPERTY()
	TArray<USplineMeshComponent*> FieldMeshs;

	UPROPERTY(EditAnywhere, Category=Magnetic, Meta=(AllowPrivateAccess=true))
	EMagneticType CurrMagnetic;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	bool bCanChangeMagnetic;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	float CurrHaveMagneticSeconds;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float MaxHaveMagneticSeconds;

	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool EternalHaveMagnetic;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UStaticMesh* MagneticFieldMesh;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* MagneticFieldMaterial;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UMaterialInterface* MagneticApplyMaterial;

	UPROPERTY()
	TArray<UMeshComponent*> ApplyMagMaterialMeshs;
	
	UPROPERTY()
	USphereComponent* FieldCollision;

	UPROPERTY()
	USplineComponent* FieldSpline;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float FinalMagneticFieldRadius;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float MagneticFieldRadius;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (ClampMin = 0.f))
	float Weight;

public:

	UPROPERTY(EditAnywhere, Category = Magnetic)
	bool bShowMagneticField;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MagneticSenserComponent.generated.h"

class UMagneticComponent;
class UMagneticSenserEffectComponent;
class UPrimitiveComponent;

/*
* 이 컴포넌트에 부착된 UPrimitiveComponent계열의 컴포넌트의 충돌 범위안의 자석을 탐지하고,
* 이 컴포넌트에 부착된 UMagneticEffectComponent계열의 컴포넌트에 정의된 효과를 부여/해제를 합니다.
*/
UCLASS( ClassGroup=(MagneticSenser), meta=(BlueprintSpawnableComponent) )
class PROJECT_MF_API UMagneticSenserComponent final : public USceneComponent
{
	GENERATED_BODY()

public:	
	/*Constructor*/
	UMagneticSenserComponent();

	/*Public methods*/
	bool GetEffectIsValid() const;
	bool GetRangeIsValid() const;

	UMagneticSenserEffectComponent* GetCurrUsedEffect() const { return _effect; }

	static void GetMagnetAppliedSenserList(UMagneticComponent* magnet, TArray<UMagneticSenserComponent*>& outList);
	static void GetMagnetAppliedSenserListByClass(UMagneticComponent* magnet, TArray<UMagneticSenserComponent*>& outList, UClass* filterClass);

private:
	/*Override methods*/
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnChildAttached(USceneComponent* ChildComponent) override;
	virtual void OnChildDetached(USceneComponent* ChildComponent) override;
	virtual bool CanAttachAsChild(const USceneComponent* ChildComponent, FName SocketName) const override;
	virtual void DestroyComponent(bool bPromoteChilderen) override;

	/*Private methods*/
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ApplyEffect(UMagneticComponent* const magnet);
	void ReleaseEffect(UMagneticComponent* const magnet);

	/*Components and property*/
	static TMap<UMagneticComponent*, TArray<UMagneticSenserComponent*>> _applyList;

	UPROPERTY()
	UPrimitiveComponent* _senseRange;

	UPROPERTY()
	UMagneticSenserEffectComponent* _effect;
};

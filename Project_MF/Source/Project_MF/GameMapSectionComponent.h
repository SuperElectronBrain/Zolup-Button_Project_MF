// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameMapSectionComponent.generated.h"

class UBoxComponent;
class UMagneticComponent;
enum class EMagneticType;

UENUM()
enum class ESectionSettingType
{
	SECTION_RESET_BEGIN_PLAY,
	SECTION_COMPLETE
};

USTRUCT()
struct FActorBeginInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	AActor* Actor;

	FTransform Transform;
};

USTRUCT()
struct FActorCheckInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	AActor* Actor;

	UPROPERTY()
	AActor* CheckPoint;
};

USTRUCT()
struct FMagneticBeginInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UMagneticComponent* Magnetic;

	EMagneticType Type;
	float MaxHaveMagneticSeconds;
	float MagneticFieldRadiusScale;
};

UCLASS( ClassGroup=(GameMapSection), meta=(BlueprintSpawnableComponent) )
class PROJECT_MF_API UGameMapSectionComponent final : public UBoxComponent
{
	GENERATED_BODY()

public:	
	/////////////////////
	//// Constructor ////
	/////////////////////
	UGameMapSectionComponent();

	///////////////////////
	//// Public methods ///
	///////////////////////
	void SetSection(ESectionSettingType type);

private:
	////////////////////////
	//// Override methods //
	////////////////////////
	virtual void BeginPlay() override;
	virtual void OnAttachmentChanged() override;
	virtual bool CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const override { return false; }

	///////////////////////
	// Private methods ///
	//////////////////////
	bool AddActorInfo(AActor* actor);
	bool AddMagnetInfo(USceneComponent* components);


	/////////////////////////////
	/// Fields And Components ///
	////////////////////////////
	UPROPERTY(VisibleAnywhere, Category = GameMapSection, Meta = (AllowPrivateAccess = true))
	bool bIsCompleteSection;

	UPROPERTY(EditAnywhere, Category = GameMapSection, Meta = (AllowPrivateAccess = true))
	bool bShowSectionRangeInGame;

	UPROPERTY()
	TArray<FActorCheckInfo> _checkList;

	UPROPERTY()
	TArray<FActorBeginInfo> _infoList;

	UPROPERTY()
	TArray<FMagneticBeginInfo> _magInfoList;
};

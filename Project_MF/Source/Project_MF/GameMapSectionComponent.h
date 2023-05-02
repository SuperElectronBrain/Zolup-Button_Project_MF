// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
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

/*게임맵의 영역을 지정하고, 초기 상태를 기록하거나, 클리어 여부를 기록하는 컴포넌트입니다.
* 이 컴포넌트가 엑터에게 부착되면, 부착되어있는 엑터의 모든 자식 엑터들의 초기 트랜스폼/자성정보등을 기록하고,
* 원하는 시점에 되돌릴 수 있게 됩니다.
*/

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
	virtual bool CanAttachAsChild(const USceneComponent* ChildComponent, FName SocketName) const override { return false; }

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

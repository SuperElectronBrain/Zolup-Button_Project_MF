// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameMapSectionComponent.generated.h"

class UBoxComponent;

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

UCLASS( ClassGroup=(GameMapSection), meta=(BlueprintSpawnableComponent) )
class PROJECT_MF_API UGameMapSectionComponent final : public USceneComponent
{
	GENERATED_BODY()

public:	
	/////////////////////
	////*Constructor*////
	/////////////////////
	UGameMapSectionComponent();

	///////////////////////
	////*Public methods*///
	///////////////////////
	void SetSection(ESectionSettingType type);

private:
	////////////////////////
	////*Override methods*//
	////////////////////////
	virtual void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/////////////////////////////
	///*Fields And Components*///
	////////////////////////////
	UPROPERTY(VisibleAnywhere, Category = GameMapSection, Meta = (AllowPrivateAccess = true))
	bool bIsCompleteSection;

	UPROPERTY()
	TArray<FActorBeginInfo> _infoList;

	UPROPERTY()
	UBoxComponent* Range;

	UPROPERTY(EditAnywhere, Category = GameMapSection, Meta = (AllowPrivateAccess = true))
	uint32 id;

	UPROPERTY(EditAnywhere, Category = GameMapSection, Meta = (AllowPrivateAccess = true))
	bool bShowSectionRangeInGame;
};

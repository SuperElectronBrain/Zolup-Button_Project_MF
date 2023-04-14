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
	void AddResetPoint(AActor* actor);
	void RemoveResetPoint(AActor* actor);

private:
	////////////////////////
	//// Override methods //
	////////////////////////
	virtual void BeginPlay() override;
	virtual bool CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const;
	virtual void DestroyComponent(bool bPromoteChildren) override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/////////////////////////////
	/// Fields And Components ///
	////////////////////////////
	UPROPERTY(VisibleAnywhere, Category = GameMapSection, Meta = (AllowPrivateAccess = true))
	bool bIsCompleteSection;

	UPROPERTY()
	TArray<FActorBeginInfo> _infoList;
};

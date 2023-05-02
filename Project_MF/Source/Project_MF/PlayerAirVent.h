// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerAirVent.generated.h"

class UArrowComponent;
class UBoxComponent;
class AGamePlayerCharacter;

UENUM()
enum class EStandingHandType
{
	DOWN_LEFT,
	DOWN_RIGHT
};

UCLASS()
class PROJECT_MF_API APlayerAirVent final : public AActor
{
	GENERATED_BODY()
	
public:	
	////////////////////////
	//// Constructor ///////
	////////////////////////
	APlayerAirVent();

	//////////////////////
	/// Public methods /// 
	//////////////////////
	FVector GetFinalEnterLocation() const;
	FVector GetStandingHandLocation(EStandingHandType type) const;
	FRotator GetStandingHandRotation(EStandingHandType type) const;
	FVector GetAirVentFloorLocation() const;
	void GetStandingHandInfo(EStandingHandType type, FVector& outLocation, FRotator& outRotator) const;

private:
	////////////////////////
	/// Override methods ///
	///////////////////////
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	////////////////////////
	/// Private methods ////
	////////////////////////
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void EnterVent(AGamePlayerCharacter* player);

	////////////////////////////
	/// Filds and Components ///
	///////////////////////////
	TWeakObjectPtr<AGamePlayerCharacter> _Player;

	UPROPERTY()
	UArrowComponent* Arrow;

	UPROPERTY()
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, Category = AirVent, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* LStandingMesh;

	UPROPERTY(EditAnywhere, Category = AirVent, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* RStandingMesh;

public:
	UPROPERTY(EditAnywhere, Category = AirVent)
	bool _bShowEnterRange;

};

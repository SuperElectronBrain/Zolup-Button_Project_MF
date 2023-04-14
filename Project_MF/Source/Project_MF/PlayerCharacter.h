// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UPlayerAnimInstance;
class UPlayerUICanvasWidget;
class UMagneticComponent;
class UDefaultMagneticMovementComponent;

UCLASS()
class PROJECT_MF_API APlayerCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	/*Constructor*/
	APlayerCharacter();

private:
	/*Override methods*/
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;
	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent) override;
	#endif
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Input methods*/
	void MoveUpDown(float value);
	void MoveRightLeft(float value);
	void LookUp(float value);
	void Turn(float value);
	void ShootMagnetic_N();
	void ShootMagnetic_S();
	void OnShootMine();
	void OffShootMine();
	void ResetMagnetic();
	void JumpStart();
	void JumpEnd();

	/*Private method*/
	void Shoot(EMagneticType shootType);
	void ShootMine(EMagneticType shootType);

	void GivenTestMagnet(UMagneticComponent* newMagnet, EMagneticType givenType);
	bool IsAlreadyGiven(UMagneticComponent* element) const;
	bool IsFulledGiven() const { return _givenIndex >= 2; }
	bool IsGivenInvalid(int index) const;
	void RemoveGiven(UMagneticComponent* remove);
	void ClearGivens() { _GivenMagnets[0] = _GivenMagnets[1] = nullptr; _givenIndex = _oldGivenIndex = 0; }

	UFUNCTION()
	void OnMagnetic(EMagneticType type, UMagneticComponent* magnet);

	UFUNCTION()
	void OffMagnetic(EMagneticType prevType, UMagneticComponent* magnet);

	UFUNCTION()
	void MagnetMoveStart(EMagnetMoveType moveType, UMagneticComponent* magnet);

	UFUNCTION()
	void MagnetMoveEnd(EMagnetMoveType moveType, UMagneticComponent* magnet);

	UFUNCTION()
	void MagnetMoveHit(AActor* hit, UMagneticComponent* magnet);

	/*fields And Components*/
	bool _bCanJump;
	bool _bShootMine;
	float _zoomInLength;
	AActor* _StickTo;
	int32 _givenIndex = 0, _oldGivenIndex;
	
	TStaticArray<UMagneticComponent*, 2> _GivenMagnets;

	UPROPERTY()
	UPlayerUICanvasWidget* PlayUIInstance;

	UPROPERTY(EditInstanceOnly, Category = UI)
	TSubclassOf<UPlayerUICanvasWidget> PlayUIClass;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Visual, Meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(VisibleAnywhere, Category = Visual, Meta = (AllowPrivateAccess = true))
	UPlayerAnimInstance* PlayerAnim;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UMagneticComponent* Magnetic;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UDefaultMagneticMovementComponent* MagMovement;

	UPROPERTY(VisibleAnywhere, Category = Magnet, Meta = (AllowPrivateAccess = true))
	EMagneticType ReloadType;

public:
	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite, Meta=(ClampMin=0.f))
	float ShootLength;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite)
	FVector ShootExtend;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite)
	float CameraRotationSpeed;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite)
	float JumpPower;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite, Meta=(ClampMin=0.f))
	float MoveSpeed;
};

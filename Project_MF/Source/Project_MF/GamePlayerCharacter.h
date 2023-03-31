// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "GamePlayerCharacter.generated.h"

class UPlayerAnimInstance;
class UPlayerUICanvasWidget;
class UMagneticComponent;
class UDefaultMagneticMovementComponent;
enum class EMagneticType;
enum class EMagnetMoveType;
/*
*
*/
UCLASS()
class PROJECT_MF_API AGamePlayerCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	/*Constructor*/
	AGamePlayerCharacter();

private:
	/*Override methods*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent) override;
	#endif

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

	/*Private methods*/
	void Shoot(EMagneticType shootType);
	void ShootMine(EMagneticType shootType);

	void GivenTestMagnet(UMagneticComponent* newMagnet, EMagneticType givenType);
	bool IsAlreadyGiven(UMagneticComponent* element) const;
	bool IsFulledGiven() const { return _givenIndex >= 2; }
	bool IsGivenInvalid(int index) const;
	void RemoveGiven(UMagneticComponent* remove);
	void ClearGivens() { _GivenMagnets[0] = _GivenMagnets[1] = nullptr; _givenIndex = _oldGivenIndex = 0; }

	UFUNCTION()
	void OnMagnetic(EMagneticType type);

	UFUNCTION()
	void OffMagnetic(EMagneticType prevType);

	UFUNCTION()
	void MagnetMoveStart(EMagnetMoveType moveType);

	UFUNCTION()
	void MagnetMoveEnd(EMagnetMoveType moveType);

	UFUNCTION()
	void MagnetMoveHit(AActor* hit);

	/*Components*/
	UPROPERTY()
	UPlayerUICanvasWidget* PlayUIInstance;

	UPROPERTY(EditInstanceOnly, Category = UI)
	TSubclassOf<UPlayerUICanvasWidget> PlayUIClass;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UMagneticComponent* Magnetic;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UDefaultMagneticMovementComponent* MagMovement;

	UPROPERTY()
	UPlayerAnimInstance* PlayerAnim;

private:
	/*fields*/
	bool _bCanJump, _bShootMine;
	float _GivenIndex, _OldGivenIndex;
	AActor* _StickTo;
	int32 _givenIndex = 0, _oldGivenIndex;
	TStaticArray<UMagneticComponent*, 2> _GivenMagnets;

public:
	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite, Meta = (ClampMin = 0.f))
	float ShootLength;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite)
	FVector ShootExtend;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite)
	float CameraRotationSpeed;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite)
	float JumpPower;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite, Meta = (ClampMin = 0.f))
	float MoveSpeed;

	//UPROPERTY(EditAnywhere, Category = BoneTransform, BlueprintReadWrite)
	//FTransform _ArmLAddTransform;

};

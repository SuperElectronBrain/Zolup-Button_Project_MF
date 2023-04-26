// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "GamePlayerCharacter.generated.h"

#define PLAYER_FADE_ID 83

class UGameCheckPointContainerComponent;
class UPlayerAnimInstance;
class UPlayerUICanvasWidget;
class UMagneticComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UDefaultMagneticMovementComponent;
class UCustomGameInstance;
class UGameMapSectionComponent;
enum class EMagneticType;
enum class EMagnetMoveType;

UENUM()
enum class EPlayerMode
{
	STANDING, CREEPY
};

/*
*
*/
UCLASS()
class PROJECT_MF_API AGamePlayerCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	/////////////////
	//*Constructor*//
	////////////////
	AGamePlayerCharacter();

	/*Public methods*/
	FRotator GetPlayerCameraQuat() const;
	FVector GetPlayerForwardVector() const;
	FVector GetPlayerRightVector() const;
	FVector GetPlayerDownVector() const;
	FQuat GetPlayerQuat() const { if (GetController() == nullptr) return FQuat::Identity;  return GetController()->GetControlRotation().Quaternion(); }
	void SetPlayerMode(EPlayerMode mode);
	void SetPlayerRotator(FRotator& newValue);

private:
	//////////////////////
	//*Override methods*//
	//////////////////////

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent) override;
	#endif

	///////////////////
	//*Input methods*//
	///////////////////
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
	void StageRestart();

	///////////////////////
	///*Private methods*//
	//////////////////////
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

	UFUNCTION()
	void FadeChange(bool isDark, int id);

	/////////////////
	///*Components*//
	/////////////////
	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UMagneticComponent* Magnetic;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UDefaultMagneticMovementComponent* MagMovement;

	UPROPERTY()
	UNiagaraSystem* ShootEffect;

	UPROPERTY()
	UNiagaraSystem* MagneticEffect;

	UPROPERTY(VisibleAnywhere, Category = Effect, Meta = (AllowPrivateAccess = true))
	UNiagaraComponent* MagneticEffectComp;

	UPROPERTY(VisibleAnywhere, Category = Effect, Meta = (AllowPrivateAccess = true))
	UNiagaraComponent* ShootEffectComp;

	UPROPERTY()
	UPlayerAnimInstance* PlayerAnim;

	UPROPERTY(EditAnywhere, Category = CheckPoint, Meta = (AllowPrivateAccess = true))
	UGameCheckPointContainerComponent* CheckPointContainer;

private:
	//////////////
	///*fields*///
	//////////////
	bool _bCanJump, _bShootMine;
	float _GivenIndex, _OldGivenIndex, _ArmPenetrateDiv, _stiffen;
	TWeakObjectPtr<UCustomGameInstance> _Instance;
	TWeakObjectPtr<UGameMapSectionComponent> _CurrSection;
	TWeakObjectPtr<AActor> _StickTo;
	TStaticArray<UMagneticComponent*, 2> _GivenMagnets;
	int32 _givenIndex = 0, _oldGivenIndex;
	FVector _goalLook, _currLook;
	FDelegateHandle _fadeHandle;

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

	UPROPERTY(EditAnywhere, Category = BoneTransform, BlueprintReadWrite)
	FTransform _ArmLAddTransform;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadWrite)
	EPlayerMode PlayerMode;

};
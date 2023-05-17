#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "GamePlayerCharacter.generated.h"

#define PLAYER_FADE_ID 83
#define STOPTIMER_FADE_ID 84

class UGameCheckPointContainerComponent;
class UPlayerAnimInstance;
class UMagneticComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UParticleSystemComponent;
class UParticleSystem;
class UDefaultMagneticMovementComponent;
class UCustomGameInstance;
class UGameMapSectionComponent;
class UWidgetComponent;
class UUIStopTimerWidget;
class APlayerAirVent;
class UAudioComponent;
class USoundCue;
enum class EMagneticType : uint8;
enum class EMagnetMoveType : uint8;

/**
* 플레이어의 적용모드를 나타내는 열거형입니다.
*/
UENUM()
enum class EPlayerMode
{
	STANDING,
	AIRVENT_ENTER,
	AIRVENT_ENTER_UP,
	AIRVENT_ENTER_DOWN,
	AIRVENT_ENTER_LHAND,
	AIRVENT_ENTER_RHAND,
	AIRVENT_ENTER_FINAL,
	AIRVENT_EXIT_UP,
	AIRVENT_EXIT_DOWN,
	CREEPY,
	STICK_JUMP
};

/**
* 플레이어가 시간정지로 멈춘 객체에 대한 정보를 담는 구조체입니다.
*/
USTRUCT()
struct FTimeStopMagnetInfo
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<UMagneticComponent> Magnetic;
	bool DefaultCanMovement = false;
	bool DefaultApplyPhysics = false;
};

/**
* 플레이어가 총으로 맞춘 대상에 대한 정보를 담는 구조체입니다.
*/
USTRUCT()
struct FShootTargetInfo
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<UMagneticComponent> ApplyTarget;
	EMagneticType ApplyType = EMagneticType::NONE;
	FVector ShootEnd		= FVector::ZeroVector;
	bool isHit				= false;
};

/**
*  게임의 플레이어 캐릭터의 모든 기능을 책임지는 클래스입니다.
*/
UCLASS()
class PROJECT_MF_API AGamePlayerCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	//////////////////////////////
	/////	  Constructor	 ////
	/////////////////////////////
	AGamePlayerCharacter();


	//////////////////////////////////
	//////     Public methods   //////
	//////////////////////////////////
	FRotator GetPlayerCameraQuat() const;
	FVector GetPlayerForwardVector() const;
	FVector GetPlayerRightVector() const;
	FVector GetPlayerDownVector() const;
	FQuat GetPlayerQuat() const { if (GetController() == nullptr) return FQuat::Identity;  return GetController()->GetControlRotation().Quaternion(); }
	void SetPlayerRotator(FRotator& newValue);
	void SetPlayerWalkMode();
	void SetCreepyMode(APlayerAirVent* airvent=nullptr, bool enter = false);


	//////////////////////////////////
	//////    Override methods  //////
	//////////////////////////////////
private:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent) override;
	#endif


	/////////////////////////////////////
	//////     Key input methods    /////
	/////////////////////////////////////
	void MoveUpDown(float value);
	void MoveRightLeft(float value);
	void LookUp(float value);
	void Turn(float value);
	void ShootMagnetic_N();
	void ShootMagnetic_S();
	void DashStart();
	void DashEnd();
	void OnShootMine();
	void OffShootMine();
	void ResetMagnetic();
	void JumpStart();
	void JumpEnd();
	void StageRestart();
	void ApplyTimeStop();


	////////////////////////////////////
	/////     Private methods   ///////
	///////////////////////////////////
	void UnApplyTimeStop();

	/*Player Sound methods*/
	void PlayMoveSound(bool playSound);

	/*Shoot Magnetic methods*/
	void Shoot(EMagneticType shootType);
	void ShootMine(EMagneticType shootType);

	/*Character action Start and progress methods*/
	void CamLookProgress(float DeltaTime);
	void ClimbProgress(float DeltaTime);
	void CreepyProgress(float DeltaTime);
	FVector GetBezirCurve2(const FVector& startPos, const FVector& controlPos, const FVector& endPos, const float& timeRatio) const;

	/*Magnetic given test methods*/
	void GivenTestMagnet(UMagneticComponent* newMagnet, EMagneticType givenType);
	bool IsAlreadyGiven(UMagneticComponent* element) const;
	bool IsFulledGiven() const { return _givenIndex >= 2; }
	bool IsGivenInvalid(int index) const;
	void RemoveGiven(UMagneticComponent* remove);
	void ClearGivens() { _GivenMagnets[0] = _GivenMagnets[1] = nullptr; _givenIndex = _oldGivenIndex = 0; }

	/**
	* 플레이어가 총을 쏘는 모션에서 총구가 반동을 얻는 부분에서 호출됩니다.
	* 이 함수가 호출되는 시점에서, 발사 이펙트와 피격된 대상의 자성이 수정됩니다.
	*/
	UFUNCTION()
	void ShootStart();

	/**
	* 플레이어의 자성이 변화가 있을 때 호출됩니다.
	* 이 함수가 호출되는 시점에서, 플레이어의 건틀렛의 자성 부여/해제 모션이 실행됩니다.
	*/
	UFUNCTION()
	void ChangeMagnetic(EMagneticType changedMagType, UMagneticComponent* changedMagComp);

	/**
	* 플레이어가 다른 자석의 자성에 의해 움직임이 시작되었을 때 호출됩니다.
	*/
	UFUNCTION()
	void MagnetMoveStart(EMagnetMoveType moveType, UMagneticComponent* moveBeginMagComp, UMagneticComponent* operatorMagComp);

	/**
	* 플레이어가 다른 자석의 자성에 의해 움직이다가 움직임을 마무리지을 때 호출됩니다.
	*/
	UFUNCTION()
	void MagnetMoveEnd(EMagnetMoveType prevMoveType, UMagneticComponent* moveEndMagComp);

	/**
	* 플레이어가 다른 자석의 자성에 의해 움직이다가 부딫혔을 경우 호출됩니다.
	* 이 함수가 호출되는 시점에서, 벽에 붙는 로직이 적용됩니다.
	*/
	UFUNCTION()
	void MagnetMoveHit(AActor* HitActor, UMagneticComponent* HitMagComp, FVector hitNormal);

	/**
	* UI 페이드 아웃이 일어날 경우 호출되는 함수입니다.
	*/
	UFUNCTION()
	void FadeChange(bool isDark, int id);

	UFUNCTION()
	void ResetCamLookTarget();

	///////////////////////////////
	//// Fields and Components ///
	//////////////////////////////
	bool _bCanJump, _bShootMine;
	float _timeStopCurrTime;
	float _playerHeight;
	float _stiffen;
	float _currDashScale;
	FVector _stickNormal;

	/**
	* Magnet Shoot Fields
	* 
	* 플레이어가 자성을 부여하기위해 필요한 필드들입니다.
	*/
	float _GivenIndex, _OldGivenIndex, _ArmPenetrateDiv;
	int32 _givenIndex = 0, _oldGivenIndex;

	/**
	* Action progress fields
	* 
	* 플레이어의 특정 동작에 대한 처리를 위해 필요한 필드들입니다.
	*/
	float _goalTimeDiv, _currTime;
	FVector _startPos, _endPos, _cPos1;
	FVector _goalLook, _currLook;

	FDelegateHandle _fadeHandle;
	FShootTargetInfo _ShootTargetInfo;
	TWeakObjectPtr<UCustomGameInstance> _Instance;
	TWeakObjectPtr<UGameMapSectionComponent> _CurrSection;
	TWeakObjectPtr<AActor> _StickTo;
	TWeakObjectPtr<APlayerAirVent> _EnterAirVent;
	TWeakObjectPtr<AActor> _CamLookTarget;
	TStaticArray<UMagneticComponent*, 2> _GivenMagnets;
	TStaticArray<FTimeStopMagnetInfo, 2> _TimeStopMagnets;

	UPROPERTY()
	UPlayerAnimInstance* PlayerAnim;

	/**
	* Source fields
	* 
	* 해당 클래스에서 사용될 오디오 & UI & 이펙트등의 원본 소스의 참조값을 담는 필드들입니다.
	*/

	/**@Sounds fields*/
	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundCue* MagOnSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundCue* MagOffSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundCue* MagShootSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundCue* MagOnGloveSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundCue* MagOffGloveSound;

	/**@UI fields*/
	UPROPERTY()
	UUIStopTimerWidget* TimerWidgetInsA;

	UPROPERTY()
	UUIStopTimerWidget* TimerWidgetInsB;

	/**@Effect fields*/
	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* ShootEffect;

	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* MagneticEffect;

	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UParticleSystem* ShootWaveEffect;

public:
	/**
	* Player Default Status fields
	*/
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

	UPROPERTY(VisibleAnywhere, Category = PlayerCharacter, BlueprintReadWrite)
	EPlayerMode PlayerMode;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadwrite)
	float MaxTimeStopSeconds;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float AirVentEnterSeconds;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float AirVentExitSeconds;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float AirVentEnterHandSeconds;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float ClimbWallSeconds;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float ClimbableWallHeight;

	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float PlayerDashScale;

private:
	/**
	* Magnetic Components
	*/
	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UMagneticComponent* Magnetic;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true))
	UDefaultMagneticMovementComponent* MagMovement;

	/**
	* Camera Components
	*/
	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	/**
	* TimeStop_UI Components
	*/
	UPROPERTY()
	UWidgetComponent* TimerWidgetA;

	UPROPERTY()
	UWidgetComponent* TimerWidgetB;

	/**
	*Effect Components
	*/
	UPROPERTY(VisibleAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraComponent* MagneticEffectComp;

	UPROPERTY(VisibleAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraComponent* ShootEffectComp;

	UPROPERTY(VisibleAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShootWaveEffectComp;

	/**
	*Sound Components
	*/
	UPROPERTY(VisibleAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	UAudioComponent* SoundEffectComp;

	/**
	* Map Components...
	*/
	UPROPERTY(EditAnywhere, Category = CheckPoint, Meta = (AllowPrivateAccess = true))
	UGameCheckPointContainerComponent* CheckPointContainer;
};
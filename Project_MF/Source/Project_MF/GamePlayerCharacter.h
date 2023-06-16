#pragma once
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "MagneticComponent.h"
#include "GamePlayerCharacter.generated.h"

constexpr const int PLAYER_FADE_ID = 83;
constexpr const int STOPTIMER_FADE_ID = 84;

constexpr const TCHAR* PLAYER_SHOOT_SOCKET = TEXT("ShootSocket");
constexpr const TCHAR* PLAYER_GAUNTLET_SOCKET = TEXT("GauntletSocket");


enum class EMagnetMoveType : uint8;
enum class EPlayerAnimNotifyType : uint8;
class UGameCheckPointContainerComponent;
class UPlayerAnimInstance;
class UMagneticComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UDefaultMagneticMovementComponent;
class UGameMapSectionComponent;
class UWidgetComponent;
class APlayerAirVent;
class UAudioComponent;
class USoundCue;

/**
* 플레이어의 적용모드를 나타내는 열거형입니다.
*/
UENUM()
enum class EPlayerMode : uint8
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
	STICK_JUMP_READY,
	STICK_JUMP,
	STICK_JUMP_STANDING,
	GAMEOVER,
	DMG_EVENT
};

/**
* 플레이어의 게임오버에 대한 이유를 나타내는 열거형입니다.
*/
UENUM()
enum class EPlayerGameOverReason : uint8
{
	NONE,
	FALLEN,
	DROWNING,
	FIRED,
	HURT
};

/**
* 플레이어가 시간정지로 멈춘 객체에 대한 정보를 담는 구조체입니다.
*/
USTRUCT()
struct FTimeStopMagnetInfo
{
	GENERATED_BODY()

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

	TWeakObjectPtr<UMagneticComponent> ApplyTarget;
	EMagneticType ApplyType;
	FVector ShootEnd		= FVector::ZeroVector;
	bool isHit				= false;
};

/**
* 플레이어의 이동 사운드를 담아둘 구조체입니다.
*/
USTRUCT(Blueprintable, BlueprintType)
struct FPlayerMoveSoundInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	USoundBase* WalkSound;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	USoundBase* DashSound;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	USoundBase* JumpEndSound;
};

/**
*  게임의 플레이어 캐릭터의 모든 기능을 책임지는 클래스입니다.
*/
UCLASS(Blueprintable, BlueprintType, ClassGroup = (GamePlayer), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API AGamePlayerCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	//////////////////////////////////////
	/////							  ////
	////		Constructor			  ////
	////							  ////
	//////////////////////////////////////
	AGamePlayerCharacter();


	//////////////////////////////////////
	/////							  ////
	////		Public methods		  ////
	////							  ////
	//////////////////////////////////////

	/*******************************************************
	* 현재 플레이어의 방향 및 정보를 얻을 수 있는 함수들입니다.
	* 
	* @Func GetPlayerCameraQuat	: 플레이어의 카메라가 바라보고 있는 회전값을 얻어옵니다.
	* @Func GetPlayerForwardVector	: 플레이어가 현재 바라보고 있는 전방 방향 벡터를 얻어옵니다.
	* @Func GetPlayerRightVector : 플레이어가 현재 바라보고 있는 방향을 기준으로 한 오른쪽 방향 벡터를 얻어옵니다.
	* @Func GetPlayerDownVector  : 플레이어가 현재 바라보고 있는 방향을 기준으로 한 아래 방향 벡터를 얻어옵니다.
	* TODO: 
	***/
	FRotator GetPlayerCameraQuat() const;
	FVector GetPlayerForwardVector() const;
	FVector GetPlayerRightVector() const;
	FVector GetPlayerDownVector() const;
	FQuat GetPlayerQuat() const { if (GetController() == nullptr) return FQuat::Identity;  return GetController()->GetControlRotation().Quaternion(); }
	void SetPlayerRotator(FRotator& newValue);
	float GetPlayerHeight() const;
	void GetPlayerCameraComponent(TWeakObjectPtr<class UCameraComponent>& OutPtr);

	/**플레이어의 동작모드를 결정하는 함수입니다.*/
	void SetPlayerWalkMode();
	void SetCreepyMode(APlayerAirVent* airvent=nullptr, bool enter = false);
	void SetDMGMode();
	void SetPlayerGameOverMode(EPlayerGameOverReason gameOverReason);
	void SetLimitPlayerCamRotation(	FVector2D xAxisLimits = FVector2D::ZeroVector, bool applyXAxis = false,
									FVector2D yAxisLimits = FVector2D::ZeroVector, bool applyYAxis = false,
									FVector2D zAxisLimits = FVector2D::ZeroVector, bool applyZAxis = false );

	void SetPlayerCurrHP(float newCurrHP);
	void SetPlayerMaxHP(float newMaxHP);

	bool PlayerCanClimbWall() const;


	//////////////////////////////////////
	/////							  ////
	////	    Override methods	  ////
	////							  ////
	//////////////////////////////////////
private:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnJumped_Implementation() override;

	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent) override;
	#endif


	//////////////////////////////////////
	/////							  ////
	////	   Private methods		  ////
	////							  ////
	//////////////////////////////////////
	void FindOverlapSection();

	/**********************************************************
	* 시스템으로부터 키입력을 받았을 때 호출되는 함수들입니다.
	* 
	* @Func MoveUpDown	 : 키보드 W,S 입력시 플레이어가 전후로 이동합니다.
	* @Func MoveRightLeft: 키보드 A,D 입력시 플레이어가 좌우로 이동합니다.
	* @Func LookUp	: 마우스 상하 이동시 카메라 시점이 상하로 회전합니다.
	* @Func Turn	: 마우스 좌우 이동시 카메라 시점이 좌우로 회전합니다.
	* @Func ShootMagnetic_N	: 우측 마우스 입력시 N극을 발사합니다.
	* @Func ShootMagnetic_S : 좌측 마우스 입력시 S극을 발사합니다.
	* @Func DashStart	: Shift키 입력시 대시를 시작합니다.
	* @Func DashEnd		: Shift키 뗄 시 대시를 중지합니다.
	* @Func OnShootMine : (deprecated)Shift키 입력시 자신을 겨냥합니다.
	* @Func OffShootMine: (deprecated)Shift키 뗄 시 자신에게 겨냥한 것을 해제합니다.
	* @Func JumpStart	: Space키 입력시 점프를 시도 하는 상태가 됩니다.
	* @Func JumpEnd		: Space키 뗄 시 점프를 그만둡니다.
	* @Func StageRestart: Tab키 입력시 주변의 섹션을 탐색하고, 해당 섹션을 초기값을 되돌립니다.
	* @Func ApplyTimeStop: E키 입력시 현재 자성을 부여한 자석들의 시간을 일정시간동안 정지시킵니다.
	* @Func ShowGameSettings : ESC키 입력시 게임설정을 보여줍니다.
	***********************************************************/
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
	void ShowGameSettings();


	/**********************************************************************************
	* UI관련 함수들입니다.
	* 
	* @Func UpdateUIRef		: 사용할 UI들의 참조를 최신화합니다.
	* @Func UnApplyTimeStop : 현재 적용된 TimeStop UIWidget들에게 페이드 인을 적용시킵니다.
	****/
	void UpdateUIWidgetReference();
	void UnApplyTimeStop();

	/*********************************************************************************
	* 플레이어가 소리를 발생시키는데 사용될 함수들입니다.
	* 
	* @Func DetectFloorType : 플레이어가 서있는 바닥을 조사하고, 바닥의 물리재질 이름을 얻습니다.
	* @Func PlayMoveSound	: 플레이어가 이동할 때 나는 소리를 재생합니다.
	***/
	void DetectFloorType(FString& outPhysMatName);
	void PlayMoveSound(bool playSound);
	void PlayDamagedSound();


	/*********************************************************************************
	* 플레이어가 총을 쐈을 때 사용되는 함수들입니다.
	* 
	* @Func Shoot	 : 플레이어가 겨눈 방향으로 레이캐스트 검사를 하고, 그 대상에게 자성을 부여합니다.
	* @Func ShootMine: 플레이어가 자기자신에게 총을 쐈을 때 적용하는 함수입니다.
	****/
	void ShootStart();
	void Shoot(EMagneticType shootType);
	void ShootMine(EMagneticType shootType);

	void ResetStart();

	void CamLookProgress(float DeltaTime);
	void ClimbProgress(float DeltaTime);
	void CreepyProgress(float DeltaTime);
	FVector GetBezirCurve2(const FVector& startPos, const FVector& controlPos, const FVector& endPos, const float& timeRatio) const;

	/***************************************************************************
	* 플레이어가 자성을 부여할 때 사용되는 함수들입니다.
	* 
	* @Func GivenTestMagnet	: 플레이어가 인자로 건네준 자석에게 자성을 부여할 수 있는지 체크하고, 지정한 자성을 부여합니다.
	* @Func IsAlreadyGiven	: 인자로 건네준 자석에게 플레이어가 이미 자성을 부여한 상태인지 검사합니다.
	* @Func IsFullGiven		: 플레이어가 자성을 부여할 수 있는 횟수가 0인지 검사합니다.
	* @Func IsGivenInvalid	: 플레이어가 자성을 부여한 목록들중 인자로 건네준 자리에 유효한 객체가 있는지 확인합니다.
	* @Func RemoveGiven		: 지정한 자석이 플레이어가 자성을 부여한 목록에 있다면 해당 목록에서 제거합니다.
	* @Func ClearGivens		: 플레이어가 자성을 부여한 목록을 초기화시킵니다.
	*/
	void GivenTestMagnet(UMagneticComponent* newMagnet, EMagneticType givenType);
	bool IsAlreadyGiven(UMagneticComponent* element) const;
	bool IsFulledGiven() const { return _givenIndex >= 2; }
	bool IsGivenInvalid(int index) const;
	void RemoveGiven(UMagneticComponent* remove);
	void ClearGivens();


	/****************************************************************************
	* 플레이어가 구독한 델리게이트에서 수신될 함수들입니다.
	* 
	* @Func PlayerAnimNotify : 플레이어 애니메이션에서 발생하는 Notify에 대한 콜백입니다.
	* @Func ChangeMagnetic: 플레이어가 자성을 부여한 자석의 자성이 바뀌었을 때 호출됩니다.
	* @Func MagnetMoveStart: 플레이어가 주변 자기장에 영향을 받아서 움직임이 시작될 때 호출됩니다.
	* @Func MagnetMoveEnd  : 플레이어가 주변 자기장에 영향을 받아 움직이다가 움직임이 끝났을 때 호출됩니다.
	* @Func MagnetMoveHit  : 플레이어가 주변 자기장에 영향을 받아 움직이다가 자성을 끌려가는 대상과 충돌했을 때 호출됩니다.
	* @Func FadeChange	: Fade효과로 인해서 UI의 색깔 또는 알파값이 변화가 있을 때 호출됩니다.
	* @Func PlayerBeginOverlap: 플레이어의 캡슐 콜라이더가 주변 충돌체와 겹쳤을 때 호출됩니다.
	* @Func PlayerEndOverlap  : 플레이어의 캡슐 콜라이더가 주변 충돌체와 겹친 상태에서 벗어났을 때 호출됩니다.
	* @Func EnterGround	: 플레이어가 공중에서 땅에 착지했을 때 호출됩니다.
	***/
	UFUNCTION()
	void PlayerAnimNotify(EPlayerAnimNotifyType NotifyType);

	UFUNCTION()
	void ChangeMagnetic(EMagneticType changedMagType, UMagneticComponent* changedMagComp);

	UFUNCTION()
	void MagnetMoveStart(EMagnetMoveType moveType, UMagneticComponent* moveBeginMagComp, UMagneticComponent* operatorMagComp);

	UFUNCTION()
	void MagnetMoveEnd(EMagnetMoveType prevMoveType, UMagneticComponent* moveEndMagComp);

	UFUNCTION()
	void MagnetMoveHit(AActor* HitActor, UMagneticComponent* HitMagComp, FVector hitNormal);

	UFUNCTION()
	void FadeChange(bool isDark, int id);

	UFUNCTION()
	void PlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void PlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void EnterGround(const FHitResult& Hit);

	UFUNCTION()
	void ResetCamLookTarget();



	//////////////////////////////////////
	/////							  ////
	////	 Fields and Components    ////
	////							  ////
	//////////////////////////////////////

	/********************************************************
	* 해당 클래스에서 사용하게되는 클래스 및 컴포넌트들의 참조값들입니다.
	* 
	* 게임 인스턴스, 자주 접근이 필요한 위젯, 현재 플레이어가 붙어있는
	* 대상 또는 플레이어로부터 자성이 부여된 자석들에 대한 참조값들이 있습니다.
	***/
	TWeakObjectPtr<class UCustomGameInstance>			_Instance;
	TWeakObjectPtr<class UUIGameSettingsWidget>			_GameSettingsWidget;
	TWeakObjectPtr<class UUIBlackScreenWidget>			_BlackScreenWidget;

	TWeakObjectPtr<class UPlayerUICanvasWidget>			_PlayerUICanvasWidget;
	TWeakObjectPtr<class UPlayerUIAimWidget>			_AimWidget;
	TWeakObjectPtr<class UPlayerUIBloodWidget>			_BloodWidget;
	TWeakObjectPtr<class UPlayerUIMagneticInfoWidget>	_MagInfoWidget;

	TWeakObjectPtr<class AActor>                   _StickTo;
	TWeakObjectPtr<class APlayerAirVent>           _EnterAirVent;
	TWeakObjectPtr<class UGameMapSectionComponent> _OverlapSection;
	TStaticArray<class UMagneticComponent*, 2>     _GivenMagnets;
	TStaticArray<struct FTimeStopMagnetInfo, 2>     _TimeStopMagnets;

	bool _bCanJump = false;
	float _prevZVelocity = 0.f;
	bool _bShootMine = false;
	float _timeStopCurrTime = 0.f;
	float _playerHeight = 0.f;
	float _noHitTime = 0.f;
	float _gauntletScale = 1.f;
	FVector _stickNormal;
	float _leftTime = 0.f;

	/**
	* 플레이어의 카메라 회전 제한에 필요한 필드들입니다.
	*/
	bool _bApplyXRotLimit = false,
		 _bApplyYRotLimit = false, 
		 _bApplyZRotLimit = false;

	FVector2D _XRotLimits, 
			  _YRotLimits, 
			  _ZRotLimits;

	/**자성 비네팅 효과의 러프를 위한 필드들입니다.*/
	FLinearColor _vignettingCurrColor;
	FLinearColor _vignettingStartColor;
	FLinearColor _vignettingDistanceColor;
	float _vignettingcurrTime = 0.f;
	float _vignettingGoalDiv = 0.f;
	

	/**플레이어가 자성을 부여하기위해 필요한 필드들입니다.*/
	int _givenIndex = 0;
	int _oldGivenIndex = 0;

	/**플레이어의 특정 동작에 대한 처리를 위해 필요한 필드들입니다.*/
	float _goalTimeDiv = 0.f;
	float _currTime = 0.f;
	FVector _startPos, _endPos, _cPos1;
	FVector _goalLook, _currLook;
	EMagneticType _lastShootType = EMagneticType::NONE;

	/**나중에 접근이 필요한 참조들의 필드입니다.*/
	FShootTargetInfo  _ShootTargetInfo;

	/**플레이어가 특정 부분을 바라볼 때 사용되는 필드입니다.*/
	TWeakObjectPtr<AActor> _CamLookTarget;
	FVector _CamLookNormal;
	bool _bApplyCamLook = false;

	UPROPERTY()
	UPlayerAnimInstance* PlayerAnim;

	UPROPERTY()
	bool bTestPlay = false;

	/**
	* 해당 클래스에서 사용될 오디오 & UI & 이펙트등의 원본 소스의 참조값을 담는 필드들입니다.
	*/

	/**@Sounds fields*/
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	TMap<FString, FPlayerMoveSoundInfo> PlayerWalkSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* MagOnSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* MagOffSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* MagShootSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* MagOnGloveSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* MagOffGloveSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* MagGunChangeSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* PlayerDefaultBreathSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* PlayerDashBreathSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* GauntletStickSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* DamagedSound1;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* DamagedSound2;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* DamagedSound3;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* WalkIronSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* RunIronSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* JumpIronSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* WalkConcreteSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* RunConcreteSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* JumpConcreteSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* SirenSound;

	UPROPERTY(EditAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	USoundBase* BGM3Sound;

	/**@UI fields*/
	UPROPERTY()
	class UUIStopTimerWidget* TimerWidgetInsA;

	UPROPERTY()
	class UUIStopTimerWidget* TimerWidgetInsB;

	/**@Effect fields*/
	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UCameraShakeBase> CamShakeClass;

	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* ShootEffect;

	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* MagneticEffect;

	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* ShootWaveEffect;

	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* MagneticVignettingEffect;

	UPROPERTY(EditAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraSystem* AbsorbEffect;

	/**
	* Player Default fields
	*/
	UPROPERTY(VisibleAnywhere, Category = PlayerCharacter, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	EPlayerMode PlayerMode = EPlayerMode::STANDING;

	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite, Meta = (ClampMin = 0, AllowPrivateAccess = true))
	float PlayerNoDamageTime = 1.3f;

	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite, Meta = (ClampMin = 0, AllowPrivateAccess=true))
	float PlayerMaxHP = 3.f;

	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite, Meta = (ClampMin = 0, AllowPrivateAccess = true))
	float PlayerCurrHP = 3.f;

	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite, Meta = (ClampMin = 0, AllowPrivateAccess = true))
	bool bCanDash = true;

public:
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite)
	float _stiffen = 0.f;

	/**플레이어의 최대 발사 거리입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite, Meta = (ClampMin = 0.f))
	float ShootLength = 10000.f;

	/**플레이어가 발사할 자성의 크기입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite)
	FVector ShootExtend = FVector(2.f, 2.f, 2.f);

	/**플레이어의 카메라 회전 속도입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite)
	float CameraRotationSpeed = 420.f;

	/**플레이어의 점프력입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite)
	float JumpPower = 1000.f;

	/**플레이어의 이동속도입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadWrite, Meta = (ClampMin = 0.f))
	float MoveSpeed = 500.f;
	
	/**플레이어가 자석의 시간을 정지시킬 수 있는 최대 시간(초)입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadwrite)
	float MaxTimeStopSeconds = 10.f;

	/**플레이어가 벽을 탈 수 있는 최대 높이입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float ClimbableWallHeight = 300.f;

	/**플레이어가 대쉬를 하면 기본 스피드에서 증가할 배수입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float PlayerDashScale = 2.f;

	/**플레이어가 환풍구로 들어가는데 걸리는 시간입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat_Action, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float AirVentEnterSeconds = .8f;

	/**플레이어가 환풍구에서 나오는데 걸리는 시간입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat_Action, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float AirVentExitSeconds = .8f;

	/**플레이어가 환풍구에서 손을 짚는데 걸리는 시간(초)입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat_Action, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float AirVentEnterHandSeconds = .6f;

	/**플레이어가 벽을 타고 올라가는데 걸리는 시간(초)입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerStat_Action, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float ClimbWallSeconds = 0.3f;

	/**플레이어의 카메라에서 자성 비네팅 이펙트가 적용되는 시간(초)입니다.*/
	UPROPERTY(EditAnywhere, Category = PlayerCharacter, BlueprintReadwrite, Meta = (ClampMin = 0.f))
	float VignettingSeconds = 1.f;

private:
	/**************************************************
	* Component( Magnetic / MagneticMovmenet )
	* 자성 관련 컴포넌트들입니다.
	*/
	UPROPERTY(EditAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	UMagneticComponent* Magnetic;

	UPROPERTY(VisibleAnywhere, Category = Magnetic, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	UDefaultMagneticMovementComponent* MagMovement;


	/*************************************************
	* Component( Camera )
	* 카메라 관련 컴포넌트들입니다.
	*/
	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;


	/**************************************************
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
	UNiagaraComponent* MagneticVignettingEffectComp;

	UPROPERTY(VisibleAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	class UGauntletEffectComponent* GauntletEffectComp;

	UPROPERTY(VisibleAnywhere, Category = PlayerEffect, Meta = (AllowPrivateAccess = true))
	UNiagaraComponent* AbsorbEffectComp;

	/**
	*Sound Components
	*/
	UPROPERTY(VisibleAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	UAudioComponent* MoveSoundEffectComp;

	UPROPERTY(VisibleAnywhere, Category = PlayerSound, Meta = (AllowPrivateAccess = true))
	UAudioComponent* BreathSoundEffectComp;

	/**
	* Map Components...
	*/
	UPROPERTY(EditAnywhere, Category = CheckPoint, Meta = (AllowPrivateAccess = true))
	UGameCheckPointContainerComponent* CheckPointContainer;
};
#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include <Animation/AnimMontage.h>
#include "PlayerAnimInstance.generated.h"

UENUM()
enum class EHandType : uint8
{
	NONE, LEFT, RIGHT
};

UENUM()
enum class EPlayerBoneType
{
	NONE,
	LEFT_HAND		= 0b10000000,
	LEFT_POARM		= 0b01000000,
	LEFT_UPPERARM	= 0b00100000,
	LEFT_ARM		= 0b11100000,

	RIGHT_HAND		= 0b00010000,
	RIGHT_POARM		= 0b00001000,
	RIGHT_UPPERARM	= 0b00000100,
	RIGHT_ARM		= 0b00011100
};

UENUM()
enum class EPlayerAnimNotifyType : uint8
{
	NONE,
	SHOOT_START,
	SHOOT_END,
	GAUNTLET_EFFECT_HIDE,
	GAUNTLET_EFFECT_VISIBLE,
	RESET_START
};

UENUM()
enum class EPlayerAnimProgressType : uint8
{
	NONE,
	CLIMB_LOOK_UP,
	CLIMB_START

};

USTRUCT(BlueprintType)
struct FClimbMontageData
{
	GENERATED_BODY()

	FVector ClimbGoalLocation;
	FVector StickWallNormal;
	
	bool bApplyLook = false;
	FVector LookDir;
	FVector StickNormal;

	float progressTime = 0.f;
	float goalProgressTimeDiv = 1.f;

	UPROPERTY(VisibleAnywhere, Category = PlayerClimbData, BlueprintReadOnly)
	bool bApplyClimb = false;
};

USTRUCT(BlueprintType)
struct FGloveActionData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category=PlayerGloveActionData, BlueprintReadOnly)
	bool bApplyGloveAction = false;

	UPROPERTY(VisibleAnywhere, Category=PlayerGloveActionData, BlueprintReadOnly)
	FTransform HandTransform;

	UPROPERTY(VisibleAnywhere, Category = PlayerGloveActionData, BlueprintReadOnly)
	FTransform PoarmTransform;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerAnimEventDelegate, EPlayerAnimNotifyType, NotifyType);

constexpr const TCHAR* const PLAYER_SPINE1_BONE	= TEXT("Bip001-Spine1");
constexpr const TCHAR* const PLAYER_NECK_BONE	= TEXT("Bip001-Neck");
constexpr const TCHAR* const PLAYER_GUN_BONE	= TEXT("Bone001");

constexpr const TCHAR* const PLAYER_LCLAVICLE_BONE = TEXT("Bip001-L-Clavicle");
constexpr const TCHAR* const PLAYER_RCLAVICLE_BONE = TEXT("Bip001-R-Clavicle");

constexpr const TCHAR* const PLAYER_LUPPERARM_BONE = TEXT("Bip001-L-UpperArm");
constexpr const TCHAR* const PLAYER_RUPPERARM_BONE = TEXT("Bip001-R-UpperArm");

constexpr const TCHAR* const PLAYER_LPOARM_BONE = TEXT("Bip001-L-Forearm");
constexpr const TCHAR* const PLAYER_RPOARM_BONE = TEXT("Bip001-R-Forearm");

constexpr const TCHAR* const PLAYER_LHAND_BONE = TEXT("Bip001-L-Hand");
constexpr const TCHAR* const PLAYER_RHAND_BONE = TEXT("Bip001-R-Hand");

constexpr const float CLIMB_LOOKUP_TIME = 2.f;
constexpr const float CLA2HAND_LEN = 70.f;


class AGamePlayerCharacter;

/**
* GamePlayerCharacter의 모든 애니메이션들을 책임지는 클래스입니다.
*/
UCLASS()
class PROJECT_MF_API UPlayerAnimInstance final: public UAnimInstance
{
	GENERATED_BODY()

public:
	////////////////////////////////////////////////
	///											///
	///			  *Constructor*					///
	///											///
	///////////////////////////////////////////////
	UPlayerAnimInstance();


	////////////////////////////////////////////////
	///											///
	///			  *Public methods*				///
	///											///
	///////////////////////////////////////////////
	UPROPERTY(BlueprintAssignable, Blueprintcallable, Category = PlayerAnimInstance)
	FPlayerAnimEventDelegate OnPlayerAnimNotifyEvent;


	////////////////////////////////////////////////
	///											///
	///			  *Public methods*				///
	///											///
	///////////////////////////////////////////////

	void DrawDebugHitPoint(const FVector& HitLocation, const FVector& HitNormal, float LifeTime = -1.f) const;
	void SetFixedPlayerBoneTransform(EPlayerBoneType fixedTarget, bool apply);

	/*************************************************************************
	* 몽타주 애니메이션 재생 관련 함수들입니다.
	*/
	bool GetJumpMontageIsPlaying() const { return Montage_IsPlaying(JumpMontage); }
	void PlayJumpMontage(float startTime = 0.f, float speed = 1.f);

	bool GetShootMontageIsPlaying() const { return Montage_IsPlaying(ShootMontage); }
	void PlayShootMontage(float startTime = 0.f, float speed = 1.f);

	bool GetResetMontageIsPlaying() const { return Montage_IsPlaying(ResetMontage); }
	void PlayResetMontage(float startTime = 0.f, float speed = 1.f);

	bool GetGloveOffMontageIsPlaying() const { return Montage_IsPlaying(GloveOffMontage); }
	void PlayGloveOffMontage(float startTime = 0.f, float speed = 1.f);

	bool GetGloveOnMontageIsPlaying() const { return Montage_IsPlaying(GloveOnMontage); }
	void PlayGloveOnMontage(float startTime = 0.f, float speed = 1.f);

	bool GetGloveActonMontage() const { return Montage_IsPlaying(GloveActonMontage); }
	void PlayGloveActonMontage(float startTime = 0.f, float speed = 1.f);
	
	bool GetGloveAtMontage() const { return Montage_IsPlaying(GloveAtMontage); }
	void PlayGloveAtMotage(float startTime=0.f, float speed=1.f);

	bool GetClimbMontage() const { return Montage_IsPlaying(ClimbMontage); }
	void PlayClimbMontage(	FVector& StartLookDir,
							FVector& ClimbLocation,
							FVector& StickNormal,
							float startTime = 0.f,
							float speed = 1.f );


	////////////////////////////////////////////////
	///											///
	///			  *Private methods*				///
	///											///
	///////////////////////////////////////////////

private:
	void FoldArmTestByStandHand(EHandType type, const AGamePlayerCharacter* player);


	/**********************************************
	* UAnimInstance의 가상함수에 대한 재정의입니다.
	***/
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	/**************************************************************
	* 특정 몽타주 및 애니메이션 진행에서 쓰이는 함수들입니다.
	*/
	void ClimbMontageProgress(float DeltaTime);


	/***************************************************************
	* 애니메이션 실행중, 노티파이로 수신을 받게될 함수들입니다.
	*/
	UFUNCTION()
	void AnimNotify_ShootStart();

	UFUNCTION()
	void AnimNotify_ShootEnd();

	UFUNCTION()
	void AnimNotify_ResetStart();

	UFUNCTION()
	void AnimNotify_GauntletEffectForward();

	UFUNCTION()
	void AnimNotify_GauntletEffectBackward();

	UFUNCTION()
	void AnimNotify_StartLHandClimb();

	UFUNCTION()
	void AnimNotify_StartRHandClimb();

	UFUNCTION()
	void AnimNotify_ClimbRotLeft();

	UFUNCTION()
	void AnimNotify_ClimbRotRight();

	UFUNCTION()
	void AnimNotify_ClimbRotForward();

	UFUNCTION()
	void AnimNotify_ClimbRotDownRight();

	UFUNCTION()
	void AnimNotify_ClimbRotForward2();


	////////////////////////////////////////////////
	///											///
	///			*Fields and Components*			///
	///											///
	///////////////////////////////////////////////

	/*******************************************************************
	* 해당 AnimInstance가 참조하는 플레이어 및 관련 컴포넌트들의 참조값들입니다.
	*/
	TWeakObjectPtr<class AGamePlayerCharacter>		TargetPlayer;
	TWeakObjectPtr<class UCameraComponent>			TargetPlayerCamera;
	TWeakObjectPtr<class USkeletalMeshComponent>	TargetPlayerMesh;


	/***************************************************************
	* 특정 몽타주 및 애니메이션에서 쓰이는 정보들에 대한 필드입니다.
	*/
	EPlayerAnimProgressType ProgressType;

	UPROPERTY(VisibleAnywhere, Category=AnimProgressData, BlueprintReadOnly, Meta=(AllowPrivateAccess=true))
	FClimbMontageData ClimbData;

	UPROPERTY(VisibleAnywhere, Category = AnimProgressData, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGloveActionData GloveActionData;


	/*********************************************************
	* 이 애니메이션에서 사용할 몽타주 에셋들에 대한 필드들입니다.
	*/
	UPROPERTY()
	UAnimMontage* ShootMontage;

	UPROPERTY()
	UAnimMontage* ResetMontage;

	UPROPERTY()
	UAnimMontage* GloveOffMontage;

	UPROPERTY()
	UAnimMontage* GloveOnMontage;

	UPROPERTY()
	UAnimMontage* GloveActonMontage;

	UPROPERTY()
	UAnimMontage* GloveAtMontage;

	UPROPERTY(VisibleAnywhere, Category = PlayerAnimAsset, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ClimbMontage;

	UPROPERTY()
	UAnimMontage* JumpMontage;

	/*********************************************************
	* 각 팔들을 고정시키는데 사용되는 필드입니다.
	*/
	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bFixedLHand= false;

	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bFixedLPoarm = false;

	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bFixedLUpperArm = false;


	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bFixedRHand = false;

	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bFixedRPoarm = false;

	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bFixedRUpperArm = false;


	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform LUpperArm_FixedTransform;

	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform RUpperArm_FixedTransform;


	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform LPoArm_FixedTransform;

	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform RPoArm_FixedTransform;


	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform LHand_FixedTransform;

	UPROPERTY(EditAnywhere, Category = FixedBone, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform RHand_FixedTransform;


	/*******************************************************
	* 애니메이션 FSM에서 쓰이는 상태값들입니다.
	*/
	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	float CurrentSpeed = 0.f;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bApplyFold_LArm = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bIsPulled = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bRArmTransformFixed = false;

public:
	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	bool bPlayerCreep = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bIsJumping = false;

};

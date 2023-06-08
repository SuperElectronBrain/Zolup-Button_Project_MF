#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include <Animation/AnimMontage.h>
#include "PlayerAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FShootStartDelegate)
DECLARE_MULTICAST_DELEGATE(FResetStartDelegate)

/**플레이어 메시의 본 이름들에 대한 문자열입니다.*/
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

constexpr const float CLA2HAND_LEN = 70.f;

class AGamePlayerCharacter;
class UMagneticComponent;

UENUM()
enum class EHandType
{
	LEFT, RIGHT
};

/**
* GamePlayerCharacter의 모든 애니메이션들을 책임지는 클래스입니다.
*/
UCLASS()
class PROJECT_MF_API UPlayerAnimInstance final: public UAnimInstance
{
	GENERATED_BODY()

public:
	//////////////////////////
	///   Constructor   /////
	/////////////////////////
	UPlayerAnimInstance();


	/////////////////////////////////
	//////   Public Delegates   /////
	/////////////////////////////////
	FShootStartDelegate OnShootStartEvent;
	FResetStartDelegate OnResetStartEvent;

	/////////////////////////////
	////   Public methods  /////
	////////////////////////////

	bool GetAttackMontageIsPlaying() const { return Montage_IsPlaying(ShootMontage); }
	bool GetResetMontageIsPlaying() const { return Montage_IsPlaying(ResetMontage); }
	bool GetSelfResetMontageIsPlaying() const { return Montage_IsPlaying(GloveOffMontage); }
	bool GetSelfShootMontageIsPlaying() const { return Montage_IsPlaying(GloveOnMontage); }

	void PlayAttackMontage(float startTime = 0.f, float speed = 1.f);
	void PlayResetMontage(float startTime = 0.f, float speed = 1.f);
	void PlaySelfResetMontage(float startTime = 0.f, float speed = 1.f);
	void PlaySelfShootMontage(float startTime = 0.f, float speed = 1.f);
	void PlayGlovePulledUpMotage(float startTime = 0.f, float speed = 1.f);
	void PlayGloveStickMotage(float startTime=0.f, float speed=1.f);

	void SetHandFixedTransform(EHandType armType, bool apply);


	/////////////////////////////////
	/////   Override methods   //////
	////////////////////////////////
private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	////////////////////////////
	////  Private methods  ////
	///////////////////////////
	void DrawDebugHitPoint(const FVector& HitLocation, const FVector& HitNormal) const;

	void ApplyCreepyStandingHands(AGamePlayerCharacter* player);
	void FoldArmTestByStandHand(EHandType type, const AGamePlayerCharacter* player);

	UFUNCTION()
	void AnimNotify_ShootStart();

	UFUNCTION()
	void AnimNotify_ShootEnd();

	UFUNCTION()
	void AnimNotify_ResetStart();


	//////////////////////////////////
	/////  Fields and Components  ///
	/////////////////////////////////
	TWeakObjectPtr<AGamePlayerCharacter> _gameCharacter;

	/**
	* 이 애니메이션에서 사용할 몽타주 에셋들에 대한 필드들입니다.
	*/
	UPROPERTY(VisibleAnywhere, Category=PlayerAnimAsset, Meta=(AllowPrivateAccess=true))
	UAnimMontage* ShootMontage;

	UPROPERTY(VisibleAnywhere, Category = PlayerAnimAsset, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ResetMontage;

	UPROPERTY(VisibleAnywhere, Category = PlayerAnimAsset, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GloveOffMontage;

	UPROPERTY(VisibleAnywhere, Category = PlayerAnimAsset, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GloveOnMontage;

	UPROPERTY(VisibleAnywhere, Category = PlayerAnimAsset, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GloveActonMontage;

	UPROPERTY(VisibleAnywhere, Category = PlayerAnimAsset, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GloveAtMontage;

	/**
	* 왼쪽팔을 접거나, 고정시키는데 사용되는 필드입니다.
	*/
	UPROPERTY(EditAnywhere, Category = PlayerLArm, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform FoldLArmHandTransform;

	UPROPERTY(VisibleAnywhere, Category = PlayerLArm, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FVector _LArmJointLocation;

	UPROPERTY(EditAnywhere, Category = PlayerLArm, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FVector ForarmTouchLocation;

	UPROPERTY(EditAnywhere, Category = PlayerLArm, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FRotator ForarmTouchRotation;

	UPROPERTY(EditAnywhere, Category = PlayerLArm, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform _LUpperArmTransform;

	UPROPERTY(EditAnywhere, Category = PlayerLArm, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform _LForArmTransform;

	UPROPERTY(EditAnywhere, Category = PlayerLArm, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform _LHandTransform;

	UPROPERTY(EditAnywhere, Category = PlayerLArm, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bLArmTransformFixed = false;

	/**
	* 애니메이션 FSM에서 쓰이는 필드들입니다.
	* 
	*/
	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool	_bIsJumping = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	float	_CurrentSpeed = 0.f;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bApplyFold_LArm = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bIsPulled = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bRArmTransformFixed = false;

public:
	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	bool _bPlayerCreep = false;

};

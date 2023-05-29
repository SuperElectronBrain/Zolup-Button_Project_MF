#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include <Animation/AnimMontage.h>
#include "PlayerAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FShootStartDelegate)

/**플레이어 메시의 본 이름들에 대한 문자열입니다.*/
constexpr const TCHAR* const PLAYER_SPINE1_BONE = TEXT("Bip001-Spine1");
constexpr const TCHAR* const PLAYER_NECK_BONE = TEXT("Bip001-Neck");
constexpr const TCHAR* const PLAYER_GUN_BONE = TEXT("Bone001");

constexpr const TCHAR* const PLAYER_LCLAVICLE_BONE = TEXT("Bip001-L-Clavicle");
constexpr const TCHAR* const PLAYER_RCLAVICLE_BONE = TEXT("Bip001-R-Clavicle");

constexpr const TCHAR* const PLAYER_LUPPERARM_BONE = TEXT("Bip001-L-UpperArm");
constexpr const TCHAR* const PLAYER_RUPPERARM_BONE = TEXT("Bip001-R-UpperArm");

constexpr const TCHAR* const PLAYER_LPOARM_BONE = TEXT("Bip001-L-Forearm");
constexpr const TCHAR* const PLAYER_RPOARM_BONE = TEXT("Bip001-R-Forearm");

constexpr const TCHAR* const PLAYER_LHAND_BONE = TEXT("Bip001-L-Hand");
constexpr const TCHAR* const PLAYER_RHAND_BONE = TEXT("Bip001-R-Hand");

constexpr const float CLA2HAND_LEN = 40.f;

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


	/////////////////////////////
	////   Public methods  /////
	////////////////////////////
	bool GetAttackMontageIsPlaying() const { return Montage_IsPlaying(ShootMontage); }
	bool GetResetMontageIsPlaying() const { return Montage_IsPlaying(ResetMontage); }
	bool GetSelfResetMontageIsPlaying() const { return Montage_IsPlaying(GloveOffMontage); }
	bool GetSelfShootMontageIsPlaying() const { return Montage_IsPlaying(GloveOnMontage); }
	void PlayAttackMontage();
	void PlayResetMontage();
	void PlaySelfResetMontage();
	void PlaySelfShootMontage(float startTime = 0.f, float speed = 1.f);
	void PlayGlovePulledUpMotage();
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


	//////////////////////////////////
	/////  Fields and Components  ///
	/////////////////////////////////
	TWeakObjectPtr<AGamePlayerCharacter> _gameCharacter;
	TWeakObjectPtr<UMagneticComponent> _targetMagnetic;

	/**애니메이션 몽타주들에 관련된 필드입니다.*/
	UPROPERTY(VisibleAnywhere, Meta=(AllowPrivateAccess=true))
	UAnimMontage* ShootMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ResetMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GloveOffMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GloveOnMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GloveActonMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* GloveAtMontage;


	/**애니메이션에서 조건값 및 조절값으로 사용되는 필드값들입니다.*/
	UPROPERTY(VisibleAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform FoldLArmHandTransform;

	UPROPERTY(VisibleAnywhere, Category = Player, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FVector _LArmJointLocation;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool	_bIsJumping = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	float	_CurrentSpeed = 0.f;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bApplyFold_LArm = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bIsPulled = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bLArmTransformFixed = false;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bRArmTransformFixed = false;

public:
	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	bool _bPlayerCreep = false;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	FTransform _ArmLAddOffsetTransform;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	FTransform _ArmRAddOffsetTransform;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	FTransform _LUpperArmTransform;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	FTransform _LForArmTransform;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	FTransform _LHandTransform;

};

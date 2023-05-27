#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include <Animation/AnimMontage.h>
#include "PlayerAnimInstance.generated.h"

#define PLAYER_LCLAVICLE_BONE TEXT("Bip001-L-Clavicle")
#define PLAYER_RCLAVICLE_BONE TEXT("Bip001-R-Clavicle")
#define PLAYER_SPINE1_BONE TEXT("Bip001-Spine1")
#define PLAYER_LPOARM_BONE TEXT("Bip001-L-Forearm")
#define PLAYER_LHAND_BONE TEXT("Bip001-L-Hand")
#define PLAYER_RHAND_BONE TEXT("Bip001-R-Hand")
#define PLAYER_RPOARM_BONE TEXT("Bip001-R-Forearm")
#define PLAYER_NECK_BONE TEXT("Bip001-Neck")
#define PLAYER_GUN_BONE TEXT("Bone001")
#define PLAYER_LUPPERARM_BONE TEXT("Bip001-L-UpperArm")
#define PLAYER_RUPPERARM_BONE TEXT("Bip001-R-UpperArm")
#define CLA2HAND_LEN 40.f

DECLARE_MULTICAST_DELEGATE(FShootStartDelegate)

class UMagneticComponent;

UENUM()
enum class EHandType
{
	LEFT, RIGHT
};

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

	void SetHandFixedTransform(EHandType armType, bool apply, UMagneticComponent* magnet=nullptr);


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

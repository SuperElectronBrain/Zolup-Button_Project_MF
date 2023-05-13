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
	/////////////////
	//*Constructor*//
	/////////////////
	UPlayerAnimInstance();

	///////////////////
	//*Delegates*//
	///////////////////
	FShootStartDelegate OnShootStartEvent;

	/////////////////////
	///*Public Methods*//
	/////////////////////
	bool GetAttackMontageIsPlaying() const { return Montage_IsPlaying(AttackMontage); }
	bool GetResetMontageIsPlaying() const { return Montage_IsPlaying(ResetMontage); }
	bool GetSelfResetMontageIsPlaying() const { return Montage_IsPlaying(SelfResetMontage); }
	bool GetSelfShootMontageIsPlaying() const { return Montage_IsPlaying(SelfShootMontage); }
	void PlayAttackMontage();
	void PlayResetMontage();
	void PlaySelfResetMontage();
	void PlaySelfShootMontage(float startTime = 0.f, float speed = 1.f);
	void PlayGlovePulledUpMotage();
	void PlayGloveStickMotage(float startTime=0.f, float speed=1.f);

	void SetHandFixedTransform(EHandType armType, bool apply);

private:
	//////////////////////
	//*Override methods*//
	/////////////////////
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	///////////////////////
	///*Private mothods*///
	///////////////////////
	void ApplyCreepyStandingHands(AGamePlayerCharacter* player);
	void FoldArmTestByStandHand(EHandType type, const AGamePlayerCharacter* player);

	UFUNCTION()
	void AnimNotify_ShootStart();

	////////////////////////////
	///*fields and Components*//
	////////////////////////////
	TWeakObjectPtr<UMagneticComponent> _targetMagnetic;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool	_bIsJumping;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	float	_CurrentSpeed;

	UPROPERTY(VisibleAnywhere, Meta=(AllowPrivateAccess=true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ResetMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SelfResetMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SelfShootMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* PulledUpMontage;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	UAnimMontage* StickMotange;

	UPROPERTY(VisibleAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform FoldLArmHandTransform;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool bApplyFold_LArm;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bIsPulled;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bLArmRotFixed;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bRArmRotFixed;

	UPROPERTY(VisibleAnywhere, Category = Player, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FVector _LArmJointLocation;

public:
	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly)
	bool _bPlayerCreep;

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

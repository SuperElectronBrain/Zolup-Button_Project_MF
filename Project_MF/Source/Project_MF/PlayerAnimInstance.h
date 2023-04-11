// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include <Animation/AnimMontage.h>
#include "PlayerAnimInstance.generated.h"

#define PLAYER_SPINE1_BONE TEXT("Bip001-Spine1")
#define PLAYER_LPOARM_BONE TEXT("Bip001-L-Forearm")
#define PLAYER_LHAND_BONE TEXT("Bip001-L-Hand")
#define PLAYER_RHAND_BONE TEXT("Bip001-R-Hand")
#define PLAYER_RPOARM_BONE TEXT("Bip001-R-Forearm")
#define PLAYER_NECK_BONE TEXT("Bip001-Neck")

UENUM()
enum class EPutArmType
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
	void PlayGloveStickMotage();

	void SetHandLookDir(EPutArmType armType, bool apply, FVector dir = FVector::ZeroVector);

private:
	//////////////////////
	//*Override methods*//
	/////////////////////
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	///////////////////////
	///*Private mothods*///
	///////////////////////
	void ApplyStandingHand(EPutArmType armType, AGamePlayerCharacter* player, FTransform& outResult, bool& hitResult);


	////////////////////////////
	///*fields and Components*//
	////////////////////////////
	float  _currArmRatio, _currArmRatio2, _ArmPenetrateDiv;
	FVector _LArmReachDir, _RArmReachDir;
	bool _bUseLArmReachDir, _bUseRArmReachDir;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool	_bIsJumping;

	UPROPERTY(EditAnywhere, Category=Player, Meta=(AllowPrivateAccess=true), BlueprintReadOnly)
	float	_CurrentSpeed;

	UPROPERTY()
	UAnimMontage* AttackMontage;

	UPROPERTY()
	UAnimMontage* ResetMontage;

	UPROPERTY()
	UAnimMontage* SelfResetMontage;

	UPROPERTY()
	UAnimMontage* SelfShootMontage;

	UPROPERTY()
	UAnimMontage* PulledUpMontage;

	UPROPERTY()
	UAnimMontage* StickMotange;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FRotator _angle;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly, Meta = (AllowPrivateAccess = true, ClampMin=0.f, ClampMax=1.f))
	float _LArmPenetrateRatio;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly, Meta = (AllowPrivateAccess = true, ClampMin = 0.f, ClampMax = 1.f))
	float _RArmPenetrateRatio;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform _LArmLastTransform;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform _RArmLastTransform;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bLHandHitWall;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool _bRHandHitWall;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	float _LfadeInRatio;

public:
	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform _ArmLAddOffsetTransform;

	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform _HandLAddOffsetTransform;

};

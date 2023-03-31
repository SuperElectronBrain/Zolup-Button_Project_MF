// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include <Animation/AnimMontage.h>
#include "PlayerAnimInstance.generated.h"

UCLASS()
class PROJECT_MF_API UPlayerAnimInstance final: public UAnimInstance
{
	GENERATED_BODY()

public:
	/*Constructor*/
	UPlayerAnimInstance();

	/*Public Methods*/
	bool GetAttackMontageIsPlaying() const { return Montage_IsPlaying(AttackMontage); }
	void PlayAttackMontage();
	bool GetResetMontageIsPlaying() const { return Montage_IsPlaying(ResetMontage); }
	void PlayResetMontage();

public:
	/*Override methods*/
	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	FTransform _ArmLAddOffsetTransform;

private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/*fields and Components*/
	UPROPERTY(EditAnywhere, Category = Player, Meta = (AllowPrivateAccess = true), BlueprintReadOnly)
	bool	_bIsJumping;

	UPROPERTY(EditAnywhere, Category=Player, Meta=(AllowPrivateAccess=true), BlueprintReadOnly)
	float	_CurrentSpeed;

	UPROPERTY(VisibleAnywhere , Category = Montage, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, Category = Montage, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ResetMontage;

	UPROPERTY(EditAnywhere, Category = Player, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FRotator _angle;

};

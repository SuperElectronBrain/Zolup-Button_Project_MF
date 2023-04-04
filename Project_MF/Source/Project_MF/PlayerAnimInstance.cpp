// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GamePlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
:_bIsJumping(false)
{
	/*intialize Property*/
	_ArmLAddOffsetTransform = FTransform::Identity;

	/*CDO*/
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  ATTACK_MONTAGE(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerShootMontage.PlayerShootMontage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  RESET_MONTAGE(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerResetMontage.PlayerResetMontage"));
	
	/*Apply montage*/
	if (ATTACK_MONTAGE.Succeeded()) AttackMontage = ATTACK_MONTAGE.Object;
	if (RESET_MONTAGE.Succeeded())ResetMontage = RESET_MONTAGE.Object;
}

void UPlayerAnimInstance::PlayResetMontage()
{
	if (!Montage_IsPlaying(ResetMontage))
	{
		Montage_Play(ResetMontage, 1.3f);
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.5f);
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* player = TryGetPawnOwner();
	if (::IsValid(player))
	{
		AGamePlayerCharacter* character = Cast<AGamePlayerCharacter>(player);
		
		if (character!=nullptr)
		{
			_CurrentSpeed = character->GetVelocity().Size();
			_bIsJumping = character->GetMovementComponent()->Velocity.Z > 0.f;
			//_ArmLAddOffsetTransform = character->_ArmLAddTransform;
		}
	}
}



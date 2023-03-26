// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
:_bIsJumping(false)
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  ATTACK_MONTAGE(TEXT("/Game/Resource/ProtoHuman/Animation/NewAnimMontage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.f);
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* player = TryGetPawnOwner();
	if (::IsValid(player))
	{
		ACharacter* character = Cast<ACharacter>(player);
		
		if (character!=nullptr)
		{
			_CurrentSpeed = character->GetVelocity().Size();
			_bIsJumping = character->GetMovementComponent()->IsFalling();
		}
	}
}



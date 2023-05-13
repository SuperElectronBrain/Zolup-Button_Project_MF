// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GamePlayerCharacter.h"
#include "MagneticComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	/*intialize Property*/
	_ArmLAddOffsetTransform = FTransform::Identity;
	_targetMagnetic = nullptr;
	_bPlayerCreep = false;
	_bIsJumping = false;
	_bIsPulled = false;

	/*CDO*/
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  ATTACK_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animations/PlayerAttackMontage.PlayerAttackMontage")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  RESET_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animations/PlayerResetMontage.PlayerResetMontage")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	SELF_RESET_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animations/PlayerSelfResetMontage.PlayerSelfResetMontage")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	SELF_SHOOT_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animations/PlayerSelfShootMontage.PlayerSelfShootMontage")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  STICK_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animations/PlayerStickMontage.PlayerStickMontage")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PULLED_UP_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animations/PlayerGloveActonMontage.PlayerGloveActonMontage")
	);

	/*Apply montage*/
	if (ATTACK_MONTAGE.Succeeded()) AttackMontage = ATTACK_MONTAGE.Object;
	if (RESET_MONTAGE.Succeeded())	ResetMontage = RESET_MONTAGE.Object;
	if (SELF_RESET_MONTAGE.Succeeded())	SelfResetMontage = SELF_RESET_MONTAGE.Object;
	if (SELF_SHOOT_MONTAGE.Succeeded()) SelfShootMontage = SELF_SHOOT_MONTAGE.Object;
	if (PULLED_UP_MONTAGE.Succeeded()) PulledUpMontage = PULLED_UP_MONTAGE.Object;
	if (STICK_MONTAGE.Succeeded()) StickMotange = STICK_MONTAGE.Object;
}

void UPlayerAnimInstance::AnimNotify_ShootStart()
{
	OnShootStartEvent.Broadcast();
}

void UPlayerAnimInstance::PlayGlovePulledUpMotage()
{
	if (PulledUpMontage == nullptr) return;

	_ArmLAddOffsetTransform.SetLocation(FVector(-6.f, 2.f, 45.f));
	_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);

	Montage_Play(PulledUpMontage, 2.f);
}

void UPlayerAnimInstance::PlayGloveStickMotage(float startTime, float speed)
{
	if (StickMotange == nullptr || Montage_IsPlaying(StickMotange)) return;

	_ArmLAddOffsetTransform.SetLocation(FVector::ZeroVector);
	_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);
	Montage_Play(StickMotange, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::PlaySelfResetMontage()
{
	if (SelfResetMontage == nullptr) return;

	_ArmLAddOffsetTransform.SetLocation(FVector::ZeroVector);
	_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);
	Montage_Play(SelfResetMontage, 2.f);
}

void UPlayerAnimInstance::PlaySelfShootMontage(float startTime, float speed)
{
	if (SelfShootMontage == nullptr) return;

	_ArmLAddOffsetTransform.SetLocation(FVector::ZeroVector);
	_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);
	Montage_Play(SelfShootMontage, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::PlayResetMontage()
{
	if (ResetMontage == nullptr) return;

	if (!Montage_IsPlaying(ResetMontage))
	{
		_ArmLAddOffsetTransform.SetLocation(FVector::ZeroVector);
		_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);

		float startTime = (GetSelfShootMontageIsPlaying() ? .6f : .3f);
		Montage_Play(ResetMontage, .7f, EMontagePlayReturnType::MontageLength, startTime);
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (AttackMontage == nullptr) return;

	Montage_Play(AttackMontage, 1.5f);
}

void UPlayerAnimInstance::SetHandFixedTransform(EHandType armType, bool apply)
{
	switch (armType) {

	case(EHandType::LEFT):
		_bLArmRotFixed = apply;
		break;

	case(EHandType::RIGHT):
		_bRArmRotFixed = apply;
		break;
	}

	if (apply)
	{
		AGamePlayerCharacter* character = Cast<AGamePlayerCharacter>(TryGetPawnOwner());
		if (character)
		{
			_LUpperArmTransform = character->GetMesh()->GetSocketTransform(PLAYER_LUPPERARM_BONE);
			_LForArmTransform = character->GetMesh()->GetSocketTransform(PLAYER_LPOARM_BONE);
			_LHandTransform = character->GetMesh()->GetSocketTransform(PLAYER_LHAND_BONE);

		}
	}
	else _targetMagnetic.Reset();
}

void UPlayerAnimInstance::ApplyCreepyStandingHands(AGamePlayerCharacter* player)
{
	#pragma region Omission
	if (player == nullptr || !::IsValid(player)) return;
	FHitResult hit;
	FCollisionQueryParams params;
	FVector neckPos = player->GetMesh()->GetSocketLocation(PLAYER_NECK_BONE);

	FVector armPosL = player->GetMesh()->GetSocketLocation(PLAYER_LPOARM_BONE);
	FVector armPosR = player->GetMesh()->GetSocketLocation(PLAYER_LPOARM_BONE);

	FVector handPosL = player->GetMesh()->GetSocketLocation(PLAYER_LHAND_BONE);
	FVector handPosR = player->GetMesh()->GetSocketLocation(PLAYER_RHAND_BONE);

	FVector forward = player->GetPlayerForwardVector();
	FVector right = player->GetPlayerRightVector();
	FVector down = player->GetPlayerDownVector();
	FVector startL = neckPos + down * 30.f - right * 40.f + forward*130.f;
	FVector endL = startL + down * 100.f;
	FVector startR = neckPos + down * 30.f + right * 40.f + forward * 130.f;
	FVector endR = startR + down * 100.f;

	params.AddIgnoredActor(player);

	//왼손부터 짚을 곳을 구하고, 그에 따른 이동을 적용한다.
	bool ret = GetWorld()->LineTraceSingleByChannel(
		hit,
		startL,
		endL,
		ECollisionChannel::ECC_Visibility,
		params
	);

	if (ret &&  hit.Distance > 0)
	{
		//손을 짚었을 때의 회전값을 구한다.
		FVector rightCross = -FVector::CrossProduct(hit.Normal, FVector::DownVector);
		FVector upCross = -FVector::CrossProduct(hit.Normal, rightCross);
		FVector result = upCross + rightCross;

		FVector lastLocation = hit.Location;
		FRotator lastRotation = FRotationMatrix::MakeFromX(result).Rotator();

		//적용.
		_ArmLAddOffsetTransform.SetLocation((hit.Location - startL) - down * 30.f);
	}

	//오른손도 짚을 곳을 구하고, 그에 따른 이동을 적용한다.
	ret = GetWorld()->LineTraceSingleByChannel(
		hit,
		startR,
		endR,
		ECollisionChannel::ECC_Visibility,
		params
	);

	if (ret && hit.Distance > 0)
	{
		//손을 짚었을 때의 회전값을 구한다.
		FVector rightCross = -FVector::CrossProduct(hit.Normal, FVector::DownVector);
		FVector upCross = -FVector::CrossProduct(hit.Normal, rightCross);
		FVector result = upCross + rightCross;

		FVector lastLocation = hit.Location;
		FRotator lastRotation = FRotationMatrix::MakeFromX(result).Rotator();

		//적용.
		_ArmRAddOffsetTransform.SetLocation((hit.Location - startR) - down*45.f);
	}

	//디버그
	//DrawDebugLine(GetWorld(), startL, endL, FColor::Yellow, false, -1.f, 0U, 8.f);
	//DrawDebugLine(GetWorld(), hit.Location, hit.Location + hit.Normal * 110.f, FColor::Red, false, -1.f, 0U, 8.f);
	//DrawDebugLine(GetWorld(), hit.Location, hit.Location + result * 110.f, FColor::Blue, false, -1.f, 0U, 8.f);
	//DrawDebugLine(GetWorld(), hit.Location, hit.Location + rightCross * 110.f, FColor::Purple, false, -1.f, 0U, 8.f);
	//DrawDebugLine(GetWorld(), hit.Location, hit.Location + upCross * 110.f, FColor::Black, false, -1.f, 0U, 8.f);
	#pragma endregion
}

void UPlayerAnimInstance::FoldArmTestByStandHand(EHandType type, const AGamePlayerCharacter* player)
{
	//계산에 필요한 것들을 모조리 구한다.
	bool	isLeft = type == EHandType::LEFT;
	const USkeletalMeshComponent* const playerMesh = player->GetMesh();
	FVector handPos = playerMesh->GetSocketLocation(isLeft ? PLAYER_LHAND_BONE : PLAYER_RHAND_BONE);
	FVector forarmPos = playerMesh->GetSocketLocation(isLeft ? PLAYER_LPOARM_BONE : PLAYER_RPOARM_BONE);
	FVector claviclePos = playerMesh->GetSocketLocation(isLeft ? PLAYER_LCLAVICLE_BONE : PLAYER_RCLAVICLE_BONE);
	FVector forward = player->GetPlayerForwardVector();
	FVector right = player->GetPlayerRightVector();
	FVector down = player->GetPlayerDownVector();
	FVector forarmTohandDir = (forarmPos - claviclePos).GetSafeNormal();

	FVector start = player->GetActorLocation() + (right* -10.f) + (down*-50.f) + (forward*-10.f);
	FVector end = start + (forward * CLA2HAND_LEN);

	FHitResult result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	//만약 자성으로 인해 날라가고 있을 경우
	_bIsPulled = _targetMagnetic.IsValid();

	//Test Trace
	bool ret = GetWorld()->LineTraceSingleByChannel(
		result,
		start,
		end,
		ECollisionChannel::ECC_Visibility,
		params
	);

	//DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false, -1.f, 0U, 1.f);

	//충돌했을 경우
	if (ret && FVector::DotProduct(forward, result.Normal) < 0 && result.Distance > 0)
	{
		//팔이 접힐 때의 손의 위치를 지정한다.
		bApplyFold_LArm = true;
		FoldLArmHandTransform.SetLocation(result.Location +result.Normal * 0.5f);
		
		//손이 벽을 짚도록 한다.
		FVector rightCross = -FVector::CrossProduct(result.Normal, FVector::DownVector);
		FVector upCross = -FVector::CrossProduct(result.Normal, rightCross);
		FVector resultCross = upCross + rightCross;

		FoldLArmHandTransform.SetRotation(resultCross.Rotation().Quaternion());

		//충돌시의 디버그용 라인
		//DrawDebugLine(GetWorld(), result.Location, result.Location + result.Normal * 110.f, FColor::Red, false, -1.f, 0U, 1.f);
		//DrawDebugLine(GetWorld(), result.Location, result.Location + resultCross * 110.f, FColor::Blue, false, -1.f, 0U, 1.f);
		//DrawDebugLine(GetWorld(), result.Location, result.Location + rightCross * 110.f, FColor::Purple, false, -1.f, 0U, 1.f);
		//DrawDebugLine(GetWorld(), result.Location, result.Location + upCross * 110.f, FColor::Black, false, -1.f, 0U, 1.f);

		//접히는 방향
		_LArmJointLocation = claviclePos + (right*-100.f) + (down*30.f);

	}
	else bApplyFold_LArm = false;

	//DrawDebugLine(GetWorld(), start, _LArmJointLocation, FColor::Yellow, false, -1.f, 0U, 1.f);
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* player = TryGetPawnOwner();
	if (player && ::IsValid(player))
	{
		AGamePlayerCharacter* character = Cast<AGamePlayerCharacter>(player);

		if (character != nullptr)
		{
			_CurrentSpeed = character->GetVelocity().Size();
			_bIsJumping = character->GetMovementComponent()->Velocity.Z > 0.f;

			FoldArmTestByStandHand(EHandType::LEFT, character);
		}
	}
}

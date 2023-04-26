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
	_LHandPenetrate = 0.f;
	_bLHandHitWall = false;

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

void UPlayerAnimInstance::PlayGlovePulledUpMotage()
{
	if (PulledUpMontage == nullptr) return;

	//_ArmLAddOffsetTransform.SetLocation(FVector(-7.f, -7.f, -5.f));
	//_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);

	Montage_Play(PulledUpMontage, 2.f);
}

void UPlayerAnimInstance::PlayGloveStickMotage(float startTime, float speed)
{
	if (StickMotange == nullptr || Montage_IsPlaying(StickMotange)) return;

	Montage_Play(StickMotange, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::PlaySelfResetMontage()
{
	if (SelfResetMontage == nullptr) return;

	Montage_Play(SelfResetMontage, 2.f);
}

void UPlayerAnimInstance::PlaySelfShootMontage(float startTime, float speed)
{
	if (SelfShootMontage == nullptr) return;

	Montage_Play(SelfShootMontage, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::PlayResetMontage()
{
	if (ResetMontage == nullptr) return;

	if (!Montage_IsPlaying(ResetMontage))
	{
		float startTime = (GetSelfShootMontageIsPlaying() ? .6f : .3f);
		Montage_Play(ResetMontage, .7f, EMontagePlayReturnType::MontageLength, startTime);
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (AttackMontage == nullptr) return;

	Montage_Play(AttackMontage, 1.5f);
}

void UPlayerAnimInstance::SetHandLookMagnetic(EHandType armType, bool apply, UMagneticComponent* magnetic)
{
	bool magnetValid = (magnetic && ::IsValid(magnetic));

	switch (armType) {

	case(EHandType::LEFT):
		_targetMagnetic = magnetValid && apply ? magnetic : nullptr;
		break;

	case(EHandType::RIGHT):
		_targetMagnetic = magnetValid && apply ? magnetic : nullptr;
		break;
	}
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

bool UPlayerAnimInstance::ApplyStandingLeftHand(AGamePlayerCharacter* player)
{
	#pragma region Omission
	if (player == nullptr || !::IsValid(player)) return false;

	FHitResult hit;
	FCollisionQueryParams params;
	FVector neckPos = player->GetMesh()->GetSocketLocation(PLAYER_NECK_BONE);
	FVector armPos = player->GetMesh()->GetSocketLocation(PLAYER_LPOARM_BONE);
	FVector handPos = player->GetMesh()->GetSocketLocation(PLAYER_LHAND_BONE);
	FRotator armRotator = player->GetMesh()->GetSocketRotation(PLAYER_LPOARM_BONE);

	FVector forward = player->GetPlayerForwardVector();
	FVector right = player->GetPlayerRightVector();
	FVector down = player->GetPlayerDownVector();
	FVector start = neckPos + down * 30.f - right * 40.f;
	FVector end = start + forward * 200.f;
	FVector dir = (end - start).GetSafeNormal();

	params.AddIgnoredActor(player);

	//만약 자성으로 인해 날라가고 있을 경우
	if (_targetMagnetic && ::IsValid(_targetMagnetic))
	{
		dir = (_targetMagnetic->GetMagneticFieldLocation() - start).GetSafeNormal();
		end = start + dir * 380.f;

		//DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false, -1.f, 0U, 8.f);
		FRotator rotator = FRotationMatrix::MakeFromX(dir).Rotator();
		rotator.Yaw -= 90.f;

		_ArmLAddOffsetTransform.SetScale3D(FVector(1.f, 1.f, 1.f));
		_ArmLReplaceTransform.SetRotation(rotator.Quaternion());
		_ArmLAddOffsetTransform.SetLocation(down * 40.f);
		_bIsPulled = true;
		end = handPos;
	}
	else _bIsPulled = false;

	//손을 짚을 곳을 구한다.
	bool ret = GetWorld()->SweepSingleByChannel(
		hit,
		start,
		end,
		player->GetPlayerQuat(),
		ECollisionChannel::ECC_Visibility,
		FCollisionShape::MakeSphere(20.f),
		params
	);

	//디버그용
	//DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false, -1.f, 0U, 8.f);
	 
	if (ret == false || ret && FVector::DotProduct(dir, hit.Normal) >= 0 || ret && hit.Distance == 0)
	{
		_bLHandHitWall = false;
		return false;
	}

	_bLHandHitWall = true;

	//손을 짚었을 때의 회전값을 구한다.
	FVector rightCross = -FVector::CrossProduct(hit.Normal, FVector::DownVector);
	FVector upCross = -FVector::CrossProduct(hit.Normal, rightCross);
	FVector result = upCross + rightCross;

	//DrawDebugLine(GetWorld(), hit.Location, hit.Location + hit.Normal * 110.f, FColor::Red, false, -1.f, 0U, 8.f);
	//DrawDebugLine(GetWorld(), hit.Location, hit.Location + result * 110.f, FColor::Blue, false, -1.f, 0U, 8.f);
	//DrawDebugLine(GetWorld(), hit.Location, hit.Location + rightCross * 110.f, FColor::Purple, false, -1.f, 0U, 8.f);
	//DrawDebugLine(GetWorld(), hit.Location, hit.Location + upCross* 110.f, FColor::Black, false, -1.f, 0U, 8.f);

	//적용
	FVector lastLocation = hit.Location -hit.Normal * 15.f;
	FRotator lastRotation = FRotationMatrix::MakeFromX(result).Rotator();
	
	_LArmLastTransform.SetLocation(lastLocation);
	_LArmLastTransform.SetRotation((lastRotation).Quaternion());
	_LArmJointLocation = armPos + hit.Normal * 1000.f;

	return true;
	#pragma endregion
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

			//플레이어가 끌어당겨질 경우, 회전을 고정시킨다.
			int ret = Montage_IsPlaying(PulledUpMontage) || Montage_IsPlaying(StickMotange) || Montage_IsPlaying(SelfShootMontage);

			ApplyStandingLeftHand(character);

			if (_bPlayerCreep)
			{
				ApplyCreepyStandingHands(character);
			}

		}
	}
}

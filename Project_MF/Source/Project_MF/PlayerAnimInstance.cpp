// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GamePlayerCharacter.h"
#include "DrawDebugHelpers.h"

UPlayerAnimInstance::UPlayerAnimInstance()
:_bIsJumping(false)
{
	/*intialize Property*/
	_ArmLAddOffsetTransform = FTransform::Identity;
	_LArmPenetrateRatio = _RArmPenetrateRatio = _currArmRatio = _currArmRatio2  = 0.f;
	_ArmPenetrateDiv = 1.0f / 80.f;

	/*CDO*/
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  ATTACK_MONTAGE(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerShootMontage.PlayerShootMontage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  RESET_MONTAGE(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerResetMontage.PlayerResetMontage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	SELF_RESET_MONTAGE(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerSelfResetMontage.PlayerSelfResetMontage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	SELF_SHOOT_MONTAGE(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerSelfShootMontage.PlayerSelfShootMontage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	PULLED_UP_MONTAGE(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerGloveActonMontage.PlayerGloveActonMontage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  STICK_MONTAGE(TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerGloveAtMontage.PlayerGloveAtMontage"));

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

	_ArmLAddOffsetTransform.SetLocation(FVector(-7.f, -7.f, -5.f));
	_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);

	Montage_Play(PulledUpMontage, 2.f);
}

void UPlayerAnimInstance::PlayGloveStickMotage()
{
	if (StickMotange == nullptr) return;
	_ArmLAddOffsetTransform.SetLocation(FVector::ZeroVector);
	_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);

	Montage_Play(StickMotange, 2.f);
}

void UPlayerAnimInstance::PlaySelfResetMontage()
{
	if (SelfResetMontage==nullptr) return;
	_ArmLAddOffsetTransform.SetLocation(FVector::ZeroVector);
	_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);

	Montage_Play(SelfResetMontage, 2.f);
}

void UPlayerAnimInstance::PlaySelfShootMontage()
{
	if (SelfShootMontage == nullptr) return;

	_ArmLAddOffsetTransform.SetLocation(FVector::ZeroVector);
	_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);
	Montage_Play(SelfShootMontage, 1.f);
}

void UPlayerAnimInstance::PlayResetMontage()
{
	if (!Montage_IsPlaying(ResetMontage))
	{
		_ArmLAddOffsetTransform.SetLocation(FVector(0.f, 0.f, -5.f));
		_ArmLAddOffsetTransform.SetRotation(FQuat::Identity);

		float startTime = (GetSelfShootMontageIsPlaying() ? .6f : .3f);
		Montage_Play(ResetMontage, .95f, EMontagePlayReturnType::MontageLength, startTime);
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.5f);
}

void UPlayerAnimInstance::ApplyStandingHand(EPutArmType armType, AGamePlayerCharacter* player, FTransform& outResult, bool& hitResult)
{
	if (player == nullptr || !::IsValid(player)) return;

	//계산에 필요한 요소들을 모두 구한다.
	FHitResult hit;
	FCollisionQueryParams params;
	FName handName = (armType == EPutArmType::LEFT ? PLAYER_LHAND_BONE : PLAYER_RHAND_BONE);
	FName armName = (armType == EPutArmType::LEFT ? PLAYER_LPOARM_BONE : PLAYER_RPOARM_BONE);
	FVector handPos = player->GetMesh()->GetSocketLocation(handName);
	FVector armPos = player->GetMesh()->GetSocketLocation(armName);
	FVector handDir = (handPos - armPos);
	FVector handNormal = handDir.GetSafeNormal();
	FVector lookDir = player->GetPlayerForwardVector();
	float arm2handDist = handDir.Size();

	//손을 짚을 곳을 구한다.
	bool ret = GetWorld()->LineTraceSingleByChannel(
		hit,
		armPos,
		armPos + handNormal*110.f,
		ECollisionChannel::ECC_Visibility,
		params
	);

	if (ret == false)
	{
		hitResult = false;
		return;
	}

	//디버그용 라인
	FVector right = -FVector::CrossProduct(hit.Normal, FVector::DownVector);
	FVector up = -FVector::CrossProduct(hit.Normal, right);
	FVector result = right + up;
	DrawDebugLine(GetWorld(), hit.Location, hit.Location + hit.Normal * 110.f, FColor::Red, false, -1.f, 0U, 8.f);
	DrawDebugLine(GetWorld(), hit.Location, hit.Location + result * 110.f, FColor::Blue, false, -1.f, 0U, 8.f);

	UE_LOG(LogTemp, Warning, TEXT("up: %s"), *result.ToString())

	//짚을 곳을 찾았을 경우
	FRotator lastRotation = FRotationMatrix::MakeFromX(result).Rotator();

	outResult.SetLocation(hit.Location);
	outResult.SetRotation((lastRotation).Quaternion());
	hitResult = true;

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* player = TryGetPawnOwner();
	if (player && ::IsValid(player))
	{
		AGamePlayerCharacter* character = Cast<AGamePlayerCharacter>(player);
		
		if (character!=nullptr)
		{
			_CurrentSpeed = character->GetVelocity().Size();
			_bIsJumping = character->GetMovementComponent()->Velocity.Z > 0.f;

			//팔이 충돌한 장소에 따라서 자연스럽게 굽히게 만든다.
			ApplyStandingHand(EPutArmType::LEFT, character, _LArmLastTransform, _bLHandHitWall);
			//ApplyStandingHand(EPutArmType::RIGHT, character, _RArmLastTransform, _bRHandHitWall);
		}
	}
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GamePlayerCharacter.h"
#include "MagneticComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	/*CDO - Montage*/
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SHOOT_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animation2/PlayerMontage_Shoot.PlayerMontage_Shoot")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  RESET_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animation2/PlayerMontage_Reset.PlayerMontage_Reset")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	GLOVE_OFF_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animation2/PlayerMontage_GloveOff.PlayerMontage_GloveOff")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	GLOVE_ON_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animation2/PlayerMontage_GloveOn.PlayerMontage_GloveOn")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>  GLOVE_AT_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animation2/PlayerMontage_GloveAt.PlayerMontage_GloveAt")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GLOVE_ACTON_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animation2/PlayerMontage_GloveActon.PlayerMontage_GloveActon")
	);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PARKOUR_MONTAGE(
		TEXT("/Game/PlayerCharacter/Animation2/PlayerMontage_Parkour02.PlayerMontage_Parkour02")
	);

	/*Montage initialize*/
	if (SHOOT_MONTAGE.Succeeded()) ShootMontage = SHOOT_MONTAGE.Object;
	if (RESET_MONTAGE.Succeeded())	ResetMontage = RESET_MONTAGE.Object;
	if (GLOVE_OFF_MONTAGE.Succeeded())	GloveOffMontage = GLOVE_OFF_MONTAGE.Object;
	if (GLOVE_ON_MONTAGE.Succeeded()) GloveOnMontage = GLOVE_ON_MONTAGE.Object;
	if (GLOVE_ACTON_MONTAGE.Succeeded()) GloveActonMontage = GLOVE_ACTON_MONTAGE.Object;
	if (GLOVE_AT_MONTAGE.Succeeded()) GloveAtMontage = GLOVE_AT_MONTAGE.Object;
	if (PARKOUR_MONTAGE.Succeeded()) ClimbMontage = PARKOUR_MONTAGE.Object;
}

void UPlayerAnimInstance::AnimNotify_StartLHandClimb()
{
	SetFixedPlayerBoneTransform(EPlayerBoneType::LEFT_ARM, false);
}

void UPlayerAnimInstance::AnimNotify_StartRHandClimb()
{
	if (TargetPlayer.IsValid() == false) return;

	if (ClimbData.bApplyClimb && TargetPlayer.IsValid())
	{
		float playerHeight = TargetPlayer->GetPlayerHeight() * .9f;
		FVector finalLocation = TargetPlayer->GetActorLocation();
		finalLocation.Z = ClimbData.ClimbGoalLocation.Z - playerHeight;
		TargetPlayer->SetActorLocation(finalLocation);
	}
}

void UPlayerAnimInstance::AnimNotify_GauntletEffectForward()
{
	UE_LOG(LogTemp, Warning, TEXT("(Anim)VISIBLE"))
	OnPlayerAnimNotifyEvent.Broadcast(EPlayerAnimNotifyType::GAUNTLET_EFFECT_VISIBLE);
}

void UPlayerAnimInstance::AnimNotify_GauntletEffectBackward()
{
	UE_LOG(LogTemp, Warning, TEXT("(Anim)HIDE"))
	OnPlayerAnimNotifyEvent.Broadcast(EPlayerAnimNotifyType::GAUNTLET_EFFECT_HIDE);
}

void UPlayerAnimInstance::AnimNotify_ShootStart()
{
	OnPlayerAnimNotifyEvent.Broadcast(EPlayerAnimNotifyType::SHOOT_START);
}

void UPlayerAnimInstance::AnimNotify_ShootEnd()
{
	OnPlayerAnimNotifyEvent.Broadcast(EPlayerAnimNotifyType::SHOOT_END);
}

void UPlayerAnimInstance::AnimNotify_ResetStart()
{
	OnPlayerAnimNotifyEvent.Broadcast(EPlayerAnimNotifyType::RESET_START);
}

void UPlayerAnimInstance::PlayGloveActonMontage(float startTime, float speed)
{
	if (GloveActonMontage == nullptr) return;
	Montage_Play(GloveActonMontage, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::PlayGloveAtMotage(float startTime, float speed)
{
	if (GloveAtMontage == nullptr || Montage_IsPlaying(GloveAtMontage)) return;
	Montage_Play(GloveAtMontage, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::PlayGloveOffMontage(float startTime, float speed)
{
	if (GloveOffMontage == nullptr) return;
	Montage_Play(GloveOffMontage, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::PlayGloveOnMontage(float startTime, float speed)
{
	if (GloveOnMontage == nullptr) return;
	Montage_Play(GloveOnMontage, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::PlayResetMontage(float startTime, float speed)
{
	if (ResetMontage == nullptr) return;

	if (!Montage_IsPlaying(ResetMontage))
	{
		startTime = (GetGloveOffMontageIsPlaying() ? .6f : .3f);
		Montage_Play(ResetMontage, .7f, EMontagePlayReturnType::MontageLength, startTime);
	}
}

void UPlayerAnimInstance::PlayShootMontage(float startTime, float speed)
{
	if (ShootMontage == nullptr) return;

	Montage_Play(ShootMontage, speed, EMontagePlayReturnType::MontageLength, startTime);
}

void UPlayerAnimInstance::AnimNotify_ClimbRotLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("1) 왼쪽 회전"))
	/**
	* 왼쪽으로 20도, 정도 카메라의 회전을 기울인다.
	*/
	//ClimbData.LookDir.Z -= 10.f;
}

void UPlayerAnimInstance::AnimNotify_ClimbRotRight()
{
	UE_LOG(LogTemp, Warning, TEXT("2) 오른쪽 회전"))
	/**
	* 왼쪽으로 20도, 정도 카메라의 회전을 기울인다.
	*/
	//ClimbData.LookDir.Z += 20.f;
}

void UPlayerAnimInstance::AnimNotify_ClimbRotForward()
{
	UE_LOG(LogTemp, Warning, TEXT("3) 정방향"))
	/**
	* 정방향을 본다.
	*/
	//ClimbData.LookDir = -ClimbData.StickNormal;
}

void UPlayerAnimInstance::AnimNotify_ClimbRotDownRight()
{
	UE_LOG(LogTemp, Warning, TEXT("4) 아래 우측"))
	/**
	* 아래를 본다.
	*/
	//FVector rightCross = -FVector::CrossProduct(ClimbData.StickNormal, FVector::DownVector);
	//ClimbData.LookDir = -ClimbData.StickNormal + FVector::DownVector - rightCross;
}

void UPlayerAnimInstance::AnimNotify_ClimbRotForward2()
{
	UE_LOG(LogTemp, Warning, TEXT("5) 마무리"))
	/**
	* 정방향을 본다.
	*/
	ClimbData.LookDir = -ClimbData.StickNormal;
}

void UPlayerAnimInstance::PlayClimbMontage(	FVector& StartLookDir,
											FVector& ClimbLocation,
											FVector& StickNormal,
											float startTime,
											float speed )
{
	if (ClimbMontage == nullptr) return;

	if (Montage_IsPlaying(ClimbMontage)==false)
	{
		StopAllMontages(0.f);
		ClimbData.bApplyClimb = true;
		//ClimbData.bApplyLook = true;
		ClimbData.LookDir = StartLookDir;
		ClimbData.ClimbGoalLocation = ClimbLocation;
		ClimbData.StickNormal = StickNormal;
		ClimbData.progressTime = 0.f;
		ProgressType = EPlayerAnimProgressType::CLIMB_LOOK_UP;
		ClimbData.progressTime = 1.f / CLIMB_LOOKUP_TIME;

		if (TargetPlayerCamera.IsValid())
		{
			TargetPlayerCamera->bUsePawnControlRotation = false;
		}

		UE_LOG(LogTemp, Warning, TEXT("goal: %s"), *ClimbData.ClimbGoalLocation.ToString())
	}
}

void UPlayerAnimInstance::ClimbMontageProgress(float DeltaTime)
{
	if (!TargetPlayer.IsValid() || !TargetPlayerCamera.IsValid() || !TargetPlayerMesh.IsValid() ) 
			return;

	/**카메라의 회전값 조정.*/
	if (ClimbData.bApplyLook)
	{
		FVector playerLocation = TargetPlayer->GetActorLocation();
		FRotator curr = TargetPlayerCamera->GetComponentRotation();
		FRotator goal = ClimbData.LookDir.Rotation();

		FRotator result = FMath::Lerp(curr, goal, DeltaTime * 10.f);
		result.Roll = 0.f;
		TargetPlayerCamera->SetWorldRotation(result);
	}

	/**카메라의 위치를 조정한다.*/
	FVector neckPos = TargetPlayerMesh->GetSocketLocation(PLAYER_NECK_BONE);
	FVector camPos = TargetPlayerCamera->GetComponentLocation();
	FVector goalPos = neckPos + FVector::UpVector * 7.f;
	TargetPlayerCamera->SetWorldLocation(FMath::Lerp(camPos, goalPos, DeltaTime*10.f));

	float progressRatio = ClimbData.progressTime * ClimbData.goalProgressTimeDiv;

	switch (ProgressType) {

		case(EPlayerAnimProgressType::CLIMB_LOOK_UP):
		{
			/**카메라가 오를 벽을 보도록 한다.*/
			FVector playerLocation = TargetPlayer->GetActorLocation();
			FRotator curr = TargetPlayerCamera->GetComponentRotation();
			FRotator goal = (-ClimbData.StickNormal).Rotation();

			FRotator result = FMath::Lerp(curr, goal, DeltaTime * 10.f);
			result.Roll = 0.f;
			TargetPlayerCamera->SetWorldRotation(result);

			if (progressRatio>=1.f)
			{
				ProgressType = EPlayerAnimProgressType::CLIMB_START;
				ClimbData.progressTime = 0.f;
				ClimbData.bApplyLook = true;
				if(ClimbMontage) Montage_Play(ClimbMontage);
			}
			break;
		}



	}

	ClimbData.progressTime += DeltaTime;

}

void UPlayerAnimInstance::DrawDebugHitPoint(const FVector& HitLocation, const FVector& HitNormal, float LifeTime) const
{
	#if WITH_EDITOR 
	{
		FVector rightCross = -FVector::CrossProduct(HitNormal, FVector::DownVector);
		FVector upCross = -FVector::CrossProduct(HitNormal, rightCross);
		FVector resultCross = upCross + rightCross;

		DrawDebugLine(GetWorld(), HitLocation, HitLocation + HitNormal * 110.f, FColor::Red, false, LifeTime, 0U, 1.f);
		DrawDebugLine(GetWorld(), HitLocation, HitLocation + resultCross * 110.f, FColor::Blue, false, LifeTime, 0U, 1.f);
		DrawDebugLine(GetWorld(), HitLocation, HitLocation + rightCross * 110.f, FColor::Purple, false, LifeTime, 0U, 1.f);
		DrawDebugLine(GetWorld(), HitLocation, HitLocation + upCross * 110.f, FColor::Black, false, LifeTime, 0U, 1.f);

	}
	#endif
}

void UPlayerAnimInstance::SetFixedPlayerBoneTransform(EPlayerBoneType fixedTarget, bool apply)
{
	#pragma region Omission
	int params = (int32)fixedTarget;

	if (TargetPlayerMesh.IsValid() == false) return;

	/**************************************************
	* 왼쪽팔에 대한 고정.
	*/
	if ((params & (int)EPlayerBoneType::LEFT_HAND) >= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("왼손 적용!!"))
		bFixedLHand = apply;
		LHand_FixedTransform = TargetPlayerMesh->GetSocketTransform(PLAYER_LHAND_BONE);
	}

	if ((params & (int)EPlayerBoneType::LEFT_POARM)>=1)
	{
		UE_LOG(LogTemp, Warning, TEXT("왼포암 적용!!"))
		bFixedLPoarm = apply;
		LPoArm_FixedTransform = TargetPlayerMesh->GetSocketTransform(PLAYER_LPOARM_BONE);
	}

	if ((params & (int)EPlayerBoneType::LEFT_UPPERARM)>=1)
	{
		UE_LOG(LogTemp, Warning, TEXT("왼업퍼암 적용!!"))
		bFixedLUpperArm = apply;
		LUpperArm_FixedTransform = TargetPlayerMesh->GetSocketTransform(PLAYER_LUPPERARM_BONE);
	}


	/************************************************
	* 오른팔에 대한 고정.
	*/
	if ((params & (int)EPlayerBoneType::RIGHT_HAND)>=1)
	{
		bFixedRHand = apply;
		RHand_FixedTransform = TargetPlayerMesh->GetSocketTransform(PLAYER_RHAND_BONE);
	}

	if ((params & (int)EPlayerBoneType::RIGHT_POARM)>=1)
	{
		bFixedRPoarm = apply;
		RPoArm_FixedTransform = TargetPlayerMesh->GetSocketTransform(PLAYER_RPOARM_BONE);
	}

	if ((params & (int)EPlayerBoneType::RIGHT_UPPERARM)>=1)
	{
		bFixedRUpperArm = apply;
		RUpperArm_FixedTransform = TargetPlayerMesh->GetSocketTransform(PLAYER_RUPPERARM_BONE);
	}
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

	FVector start = player->GetActorLocation() + (right* -20.f) + (down*-70.f) + (forward*-10.f);
	FVector end = start + (forward * CLA2HAND_LEN);

	FHitResult result;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	//레이캐스트로 앞에 장애물이 있는지 검사한다.
	bool ret = GetWorld()->LineTraceSingleByChannel(
		result,
		start,
		end,
		ECollisionChannel::ECC_Visibility,
		params
	);

	//충돌했을 경우
	if (ret && FVector::DotProduct(forward, result.Normal) < 0 && result.Distance > 0)
	{
		//팔이 접힐 때의 손의 위치를 지정한다.
		bApplyFold_LArm = true;
		
		//손이 벽을 짚도록 한다.
		FVector rightCross = -FVector::CrossProduct(result.Normal, FVector::DownVector);
		FVector upCross = -FVector::CrossProduct(result.Normal, rightCross);
		FVector resultCross = upCross + rightCross;

		FVector handLocation = result.Location + (result.Normal * 1.f);
		FQuat handQuat = resultCross.Rotation().Quaternion();

		FVector poarmLocation = result.Location + (result.Normal * 20.f) + (upCross * -8.f) + (rightCross * -.15f);
		FQuat poarmQuat = (handLocation - poarmLocation).Rotation().Quaternion();

		GloveActionData.HandTransform.SetRotation(handQuat);
		GloveActionData.HandTransform.SetLocation(handLocation);

		GloveActionData.PoarmTransform.SetLocation(poarmLocation);
		GloveActionData.PoarmTransform.SetRotation(poarmQuat);
	}
	else bApplyFold_LArm = false;
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	/*********************************************************
	* 플레이어의 참조 및 플레이어의 일부 컴포넌트들의 참조를 가져온다.
	*/
	TargetPlayer = Cast<AGamePlayerCharacter>(TryGetPawnOwner());
	if (TargetPlayer.IsValid())
	{
		TargetPlayerMesh = TargetPlayer->GetMesh();
		TargetPlayer->GetPlayerCameraComponent(TargetPlayerCamera);
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (TargetPlayer.IsValid() == false) return;

	/*유효한 플레이어의 상태를 갱신한다.*/
	CurrentSpeed = TargetPlayer->GetVelocity().Size();
	bIsJumping = FMath::Abs(TargetPlayer->GetMovementComponent()->Velocity.Z) >= 0.05f;
	bIsPulled = (Montage_IsPlaying(GloveAtMontage) || Montage_IsPlaying(GloveActonMontage));

	/**각종 진행용 함수 실행.*/
	if (ClimbData.bApplyClimb) ClimbMontageProgress(DeltaSeconds);

	if (bIsPulled) FoldArmTestByStandHand(EHandType::LEFT, TargetPlayer.Get());
	else bApplyFold_LArm = false;
}

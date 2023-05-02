// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "PlayerUICanvasWidget.h"
#include "MagneticComponent.h"
#include "GameMapSectionComponent.h"
#include "DefaultMagneticMovementComponent.h"
#include "particles/PxParticleSystem.h"
#include "GameCheckPointContainerComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "CustomGameInstance.h"
#include "GameUIHandler.h"
#include "UIBlackScreenWidget.h"
#include "UIStopTimerWidget.h"
#include "Components/WidgetComponent.h"
#include "PlayerAirVent.h"
#include "DrawDebugHelpers.h"

AGamePlayerCharacter::AGamePlayerCharacter()
{
	#pragma region Omission
	//Intialized Properts and Fields
	PrimaryActorTick.bCanEverTick = true;
	ShootLength = 10000.f;
	JumpPower = 1600.f;
	CameraRotationSpeed = 420.f;
	MoveSpeed = 1450.f;
	_bCanJump = false;
	_bShootMine = false;
	_GivenIndex = _OldGivenIndex = 0;
	_StickTo = nullptr;
	_ArmPenetrateDiv = 1.0f / 90.f;
	ShootExtend.Set(2.f, 2.f, 2.f);
	_stiffen = 0.f;
	PlayerMode = EPlayerMode::STANDING;
	_goalLook = _currLook = FVector::ZeroVector;
	_timeStopCurrTime = 0.f;
	MaxTimeStopSeconds = 10.f;
	_goalTimeDiv = _currTime = 0.f;
	AirVentEnterSeconds = .8f;
	_startPos = _endPos = _cPos1 = FVector::ZeroVector;
	AirVentEnterHandSeconds = .6f;

	//CDO
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	PLAYER_MESH(
		TEXT("/Game/PlayerCharacter/Meshs/PlayerArmMeshNew.PlayerArmMeshNew")
	);
	static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> ANIM_BLUEPRINT(
		TEXT("/Game/PlayerCharacter/Animations/PlayerAnimBlueprint")
	);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SHOOT_EFFECT_SYSTEM(
		TEXT("/Game/Effect/Gun/Gun_effect_shoot_s_fix.Gun_effect_shoot_s_fix")
	);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> MAGNETIC_EFFECT_SYSTEM(
		TEXT("/Game/Effect/Gun/Gun_effect_defalt_s_fix.Gun_effect_defalt_s_fix")
	);
	static ConstructorHelpers::FClassFinder<UUserWidget> STOPTIMER_WIDGET(
		TEXT("/Game/UI/UIStopTimerWidget")
	);

	/*SpringArm*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	SpringArm->TargetArmLength = 10.f;
	SpringArm->SetRelativeLocationAndRotation(FVector(.0f, .0f, 280.f), FRotator::ZeroRotator);

	/*Camera*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -1.3f), FRotator::ZeroRotator);

	/*CapsuleComponents*/
	GetCapsuleComponent()->SetCapsuleRadius(60.4f);/*default: 80.f*/
	GetCapsuleComponent()->SetCapsuleHalfHeight(278.6f);/*default: 197.f*/

	/*Player Mesh*/
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	PlayerMesh->SetupAttachment(SpringArm);
	if (PLAYER_MESH.Succeeded())
	{
		PlayerMesh->SetSkeletalMesh(PLAYER_MESH.Object);
		PlayerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayerMesh->SetRelativeLocationAndRotation(FVector(0.f, -14.f, -495.f), FRotator::MakeFromEuler(FVector(0.f, 0.f, -80.f)));
		PlayerMesh->SetRelativeScale3D(FVector(4.f, 4.f, 4.f));
		PlayerMesh->bCastDynamicShadow = false;
		PlayerMesh->SetCastShadow(false);
	}

	//Applyblueprint
	if (ANIM_BLUEPRINT.Succeeded())
	{
		PlayerMesh->SetAnimInstanceClass(ANIM_BLUEPRINT.Class);
	}

	/*CheckPoint*/
	CheckPointContainer = CreateDefaultSubobject<UGameCheckPointContainerComponent>(TEXT("CHECK_POINT_CONTAINER"));

	/*CharacterMovement*/
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->JumpZVelocity = JumpPower;
	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->bJustTeleported = false;
	GetCharacterMovement()->GravityScale = 4.f;
	GetCharacterMovement()->FallingLateralFriction = 2.f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	/*Magnetic*/
	Magnetic = CreateDefaultSubobject<UMagneticComponent>(TEXT("MAGNETIC"));
	MagMovement = CreateDefaultSubobject<UDefaultMagneticMovementComponent>(TEXT("DEFAULT_MAG_MOVEMENT"));
	Magnetic->SetupAttachment(GetCapsuleComponent());
	Magnetic->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	Magnetic->SetMagneticFieldRadius(300.f);
	Magnetic->SetWeight(1.f, true);

	/*Shoot Effect*/
	if (SHOOT_EFFECT_SYSTEM.Succeeded()) ShootEffect = SHOOT_EFFECT_SYSTEM.Object;
	if (MAGNETIC_EFFECT_SYSTEM.Succeeded()) MagneticEffect = MAGNETIC_EFFECT_SYSTEM.Object;
	
	/*StopTimer Widget*/
	TimerWidgetA = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponentA"));
	TimerWidgetB = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponentB"));
	if (STOPTIMER_WIDGET.Succeeded())
	{
		TimerWidgetA->SetupAttachment(RootComponent);
		TimerWidgetA->SetRelativeLocation(FVector(0.f, 0.f, 300.f));
		TimerWidgetA->SetWidgetSpace(EWidgetSpace::Screen);
		TimerWidgetA->SetWidgetClass(STOPTIMER_WIDGET.Class);
		TimerWidgetA->SetDrawSize(FVector2D(300.f, 300.f));
		TimerWidgetA->SetVisibility(false);

		TimerWidgetB->SetupAttachment(RootComponent);
		TimerWidgetB->SetRelativeLocation(FVector(0.f, 0.f, 300.f));
		TimerWidgetB->SetWidgetSpace(EWidgetSpace::Screen);
		TimerWidgetB->SetWidgetClass(STOPTIMER_WIDGET.Class);
		TimerWidgetB->SetDrawSize(FVector2D(300.f, 300.f));
		TimerWidgetB->SetVisibility(false);
	}

	#pragma endregion
}

void AGamePlayerCharacter::SetPlayerMode(EPlayerMode mode)
{
	PlayerMode = mode;

	switch (mode)
	{
		case(EPlayerMode::STANDING): {
			GetCapsuleComponent()->SetCapsuleRadius(160.4f);
			GetCapsuleComponent()->SetCapsuleHalfHeight(278.6f);
			SpringArm->TargetArmLength = 10.f;
			SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 280.f));
			if (PlayerAnim) PlayerAnim->_bPlayerCreep = false;
			GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
			break;
		}

		case(EPlayerMode::CREEPY):{
			GetCapsuleComponent()->SetCapsuleRadius(80.f);
			GetCapsuleComponent()->SetCapsuleHalfHeight(80.f);
			SpringArm->TargetArmLength = 10.f;
			SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
			if (PlayerAnim) PlayerAnim->_bPlayerCreep = true;
			GetCharacterMovement()->MaxWalkSpeed = 100.f;
			break;
		}
		
	}
}

void AGamePlayerCharacter::SetPlayerRotator(FRotator& newValue)
{
	Controller->SetControlRotation(newValue);
}

FRotator AGamePlayerCharacter::GetPlayerCameraQuat() const
{
	return GetControlRotation();
}

FVector AGamePlayerCharacter::GetPlayerForwardVector() const
{
	if (Controller == nullptr) return FVector::ZeroVector;

	const FRotator rotation = Controller->GetControlRotation();
	const FVector dir = FRotationMatrix(rotation).GetUnitAxis(EAxis::X);

	return dir;
}

FVector AGamePlayerCharacter::GetPlayerDownVector() const
{
	if (Controller == nullptr) return FVector::ZeroVector;

	const FRotator rotation = Controller->GetControlRotation();
	const FVector dir = FRotationMatrix(rotation).GetUnitAxis(EAxis::Z);

	return -dir;
}

FVector AGamePlayerCharacter::GetPlayerRightVector() const
{
	if (Controller == nullptr) return FVector::ZeroVector;

	const FRotator rotation = Controller->GetControlRotation();
	const FVector dir = FRotationMatrix(rotation).GetUnitAxis(EAxis::Y);

	return dir;
}

void AGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	#pragma region Omission
	/*Magnetic*/
	if (Magnetic)
	{
		Magnetic->OnMagneticEvent.AddUObject(this, &AGamePlayerCharacter::OnMagnetic);
		Magnetic->OffMagneticEvent.AddUObject(this, &AGamePlayerCharacter::OffMagnetic);
		Magnetic->MagnetMoveHitEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveHit);
		Magnetic->MagnetMoveStartEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveStart);
		//Magnetic->MagnetMoveEndEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveEnd);
	}

	//게임 인스턴스 참조
	_Instance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());

	//애님 인스턴스 참조
	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	//UI띄우기
	if (_Instance.IsValid())
	{
		TWeakObjectPtr<UPlayerUICanvasWidget> playerUI;
		TWeakObjectPtr<UUIBlackScreenWidget> blackScreen;

		//Player UI
		_Instance->GetUIManager()->GetPlayerUICanvasWidget(playerUI);
		if (playerUI.IsValid())
		{
			playerUI->AddToViewport();
			playerUI->SetAnimColor(FColor(255, 255, 255, 150));
		}

		//BlackScreen 뷰포트에 추가 및 페이드 아웃->인
		_Instance->GetUIManager()->GetUIBlackScreenWidget(blackScreen);
		if (blackScreen.IsValid())
		{
			blackScreen->AddToViewport();
			blackScreen->SetAlpha(0.f);
		}

		//FadeChange 이벤트 추가.
		_fadeHandle = _Instance->GetUIManager()->OnUIFadeChange.AddUObject(this, &AGamePlayerCharacter::FadeChange);
	}

	/*시간정지 위젯 참조 구하기*/
	if (TimerWidgetA) TimerWidgetInsA = Cast<UUIStopTimerWidget>(TimerWidgetA->GetWidget());
	if (TimerWidgetB) TimerWidgetInsB = Cast<UUIStopTimerWidget>(TimerWidgetB->GetWidget());

	/*캡슐 콜라이더 회전 방지*/
	UCapsuleComponent* capsule = GetCapsuleComponent();
	if (capsule)
	{
		capsule->BodyInstance.bLockXRotation = true;
		capsule->BodyInstance.bLockYRotation = true;
		capsule->BodyInstance.bLockZRotation = true;
	}

	//자성 이펙트 추가.
	//if (MagneticEffect)
	//{
	//	MagneticEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
	//		MagneticEffect, 
	//		GetMesh(), 
	//		TEXT("MagneticSocket"), 
	//		FVector(-10.f, 0.f, 0.f),
	//		FRotator::ZeroRotator,
	//		EAttachLocation::SnapToTargetIncludingScale,
	//		false
	//	);

	//	MagneticEffectComp->SetRelativeScale3D(FVector(4.f, 4.f, 4.f));
	//}

	//발사 이펙트 추가.
	if (ShootEffect && false)
	{
		ShootEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			ShootEffect,
			GetMesh(),
			TEXT("ShootSocket"),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			FVector(50.f, 50.f, 50.f),
			EAttachLocation::KeepRelativeOffset,
			true, 
			ENCPoolMethod::None
		);
	}

	#pragma endregion
}

void AGamePlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (_Instance.IsValid())
	{
		_Instance->GetUIManager()->OnUIFadeChange.Remove(_fadeHandle);
	}
}

void AGamePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//경직 적용
	if (_stiffen > 0.f)
	{
		_stiffen -= DeltaTime;
		if (_stiffen <= 0.f) _stiffen = 0.f;
	}

	//타임스탑 적용
	if (_timeStopCurrTime > 0.f)
	{
		_timeStopCurrTime -= DeltaTime;
		float value = MaxTimeStopSeconds - _timeStopCurrTime;
		if (TimerWidgetInsA) TimerWidgetInsA->SetCurrTime(value);
		if (TimerWidgetInsB) TimerWidgetInsB->SetCurrTime(value);

		if (_timeStopCurrTime <= 0.f)
		{
			_timeStopCurrTime = 0.f;
			UnApplyTimeStop();
		}
	}

	//점프키를 꾹 누르면 점프
	if (_bCanJump && _stiffen == 0.f)
	{
		Jump();
	}

	//기어다닐 때의 모션 적용.
	CreepyProgress(DeltaTime);
}

void AGamePlayerCharacter::SetCreepyMode(APlayerAirVent* airvent)
{
	if (airvent == nullptr || !::IsValid(airvent)) return;

	#pragma region Omission
	_EnterAirVent = airvent;
	_currTime = 0.f;
	_stiffen = -1.f;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCapsuleRadius(80.f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(94.f);
	SpringArm->TargetArmLength = 10.f;
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
	SetActorLocation(GetActorLocation() + FVector::UpVector * 280.f);

	FVector airventPos = airvent->GetFinalEnterLocation();
	FVector playerPos = GetActorLocation();
	float xGap = FMath::Abs((airventPos - playerPos).X);
	float yGap = FMath::Abs((airventPos - playerPos).Y);
	float height = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	_goalTimeDiv = 1.f / AirVentEnterSeconds;

	FVector verticalDir = (playerPos - airventPos).GetSafeNormal();
	PlayerMode = EPlayerMode::AIRVENT_ENTER_DOWN;
	_startPos = playerPos;
	_cPos1 = playerPos - (airvent->GetActorForwardVector() * (300.f - xGap));
	_endPos = airventPos - (airvent->GetActorForwardVector() * 300.f);

	#pragma endregion
}

FVector AGamePlayerCharacter::GetBezirCurve2(const FVector& startPos, const FVector& controlPos, const FVector& endPos, const float& timeRatio) const
{
	FVector ab = startPos + (controlPos - startPos) * timeRatio;
	FVector bc = controlPos + (endPos - controlPos) * timeRatio;
	FVector abbc = ab + (bc - ab) * timeRatio;

	return abbc;
}

void AGamePlayerCharacter::CreepyProgress(float DeltaTime)
{
	#pragma region Omission

	//환풍구 참조가 유효하지 않다면 탈출.
	if (_EnterAirVent.IsValid() == false)
	{
		_EnterAirVent.Reset();
		return;
	}

	//계산에 필요한 변수들.
	int32 curveNum = _curveLists.Num();
	float progressRatio = _currTime * _goalTimeDiv;

	//환풍구 들어가기 전 애니메이션
	switch (PlayerMode){

		//////*위쪽에 있는 환풍구에 들어갈 경우*///////
		case(EPlayerMode::AIRVENT_ENTER_UP):
		{

			break;
		}

		//////*비슷한 위치 또는 아래쪽에 있는 환풍구에 들어갈 경우*///////
		case(EPlayerMode::AIRVENT_ENTER_DOWN):
		{
			//좌표 이동
			if (progressRatio < 1.f)
				SetActorLocation(GetBezirCurve2(_startPos, _cPos1, _endPos, progressRatio));

			//카메라 시점 고정
			FRotator controlRot = GetControlRotation();
			FRotator rotator(0.f, (_EnterAirVent->GetActorLocation() - GetActorLocation()).Rotation().Yaw, 0.f);
			GetController()->SetControlRotation(controlRot + (rotator - controlRot) * .025f);

			//마무리 작업
			if (progressRatio >= 1.f)
			{
				FVector airventLocation = _EnterAirVent->GetActorLocation();
				FVector handLStandingLocation = _EnterAirVent->GetStandingHandLocation(EStandingHandType::DOWN_LEFT);
				FRotator handLStandingRot = _EnterAirVent->GetStandingHandRotation(EStandingHandType::DOWN_LEFT);
				FVector airventForward = _EnterAirVent->GetActorForwardVector();
				FVector airventRight = _EnterAirVent->GetActorRightVector();

				PlayerMode = EPlayerMode::AIRVENT_ENTER_LHAND;
				_currTime = 0.f;
				_goalTimeDiv = 1.f / AirVentEnterHandSeconds;
				_startPos = GetActorLocation();
				_endPos = _startPos + (_EnterAirVent->GetFinalEnterLocation() - _startPos)*.5f;
				_cPos1 = _startPos + (_EnterAirVent->GetFinalEnterLocation() - _startPos) * .25f - airventRight*20.f;
			}

			_currTime += DeltaTime;
			break;
		}

		//////*왼손부터 환풍구에 집어넣는다.*//////
		case(EPlayerMode::AIRVENT_ENTER_LHAND):
		{
			//카메라 시점 고정
			FRotator controlRot = GetControlRotation();
			FVector airventRight = _EnterAirVent->GetActorRightVector();
			FVector airventUp = _EnterAirVent->GetActorUpVector();
			FVector lookPos = _EnterAirVent->GetFinalEnterLocation() - airventRight * 60.f-airventUp*100.f;
			FRotator rotator = (lookPos - GetActorLocation()).Rotation();
			GetController()->SetControlRotation(controlRot + (rotator - controlRot) * .05f);

			//적용
			if (progressRatio <= 1.f)
			{
				SetActorLocation(GetBezirCurve2(_startPos, _cPos1, _endPos, progressRatio));
			}

			if (PlayerAnim && PlayerAnim->GetSelfShootMontageIsPlaying()==false)
			{
				FVector handLStandingLocation;
				FRotator handLStandingRot;

				_EnterAirVent->GetStandingHandInfo(EStandingHandType::DOWN_LEFT, handLStandingLocation, handLStandingRot);

				PlayerAnim->PlaySelfShootMontage(20.f);
				PlayerAnim->SetLHandStanding(handLStandingLocation, handLStandingRot, true, 0.3f);
			}

			//마무리 작업
			if (progressRatio>=.7f)
			{
				FVector airventForward = _EnterAirVent->GetActorForwardVector();
				FVector airventPos = _EnterAirVent->GetActorLocation();
				FVector handLStandingLocation;
				FRotator handLStandingRot;

				_EnterAirVent->GetStandingHandInfo(EStandingHandType::DOWN_RIGHT, handLStandingLocation, handLStandingRot);
				if(PlayerAnim) PlayerAnim->SetRHandStanding(handLStandingLocation, handLStandingRot, true, 0.8f);

				PlayerMode = EPlayerMode::AIRVENT_ENTER_RHAND;
				_currTime = 0.f;
				_goalTimeDiv = 1.f / AirVentEnterHandSeconds;
				_startPos = GetActorLocation();
				_endPos = _startPos + (airventPos - _startPos) * 1.5f;
				_cPos1 = _startPos + (_endPos - _startPos)*.5f + airventRight * 30.f;
			}

			//if (progressRatio>=.5f && progressRatio <= .55f)_currTime += DeltaTime * .1f;
			_currTime += DeltaTime;
			break;
		}

		//////*오른손을 환풍구에 집어넣는다.*//////
		case(EPlayerMode::AIRVENT_ENTER_RHAND):
		{
			//카메라 시점 고정
			FRotator controlRot = GetControlRotation();
			FVector airventRight = _EnterAirVent->GetActorRightVector();
			FVector airventUp = _EnterAirVent->GetActorUpVector();
			FVector lookPos = _EnterAirVent->GetFinalEnterLocation() + airventRight * 60.f + airventUp*10.f;
			FRotator rotator = (lookPos - GetActorLocation()).Rotation();
			GetController()->SetControlRotation(controlRot + (rotator - controlRot) * .03f);

			SetActorLocation(GetBezirCurve2(_startPos, _cPos1, _endPos, progressRatio));

			//마무리 작업
			if (progressRatio >= .7f)
			{
				FVector airventForward = _EnterAirVent->GetActorForwardVector();
				FVector airventPos = _EnterAirVent->GetActorLocation();
				_startPos = GetActorLocation();
				_endPos = _startPos + airventForward * 100.f;
				_cPos1 = _startPos + (_endPos - _startPos) * .5f + airventRight * 30.f;
				PlayerMode = EPlayerMode::AIRVENT_ENTER_FINAL;
				_currTime = 0.f;
				_goalTimeDiv = 1.f / AirVentEnterHandSeconds;
			}

			_currTime += DeltaTime;
			break;
		}

		//////*마무리 작업.*//////
		case(EPlayerMode::AIRVENT_ENTER_FINAL):
		{
			//카메라 시점 고정
			FRotator controlRot = GetControlRotation();
			FVector airventRight = _EnterAirVent->GetActorRightVector();
			FVector airventUp = _EnterAirVent->GetActorUpVector();
			FVector airventForward = _EnterAirVent->GetActorForwardVector();
			FVector lookPos = _EnterAirVent->GetFinalEnterLocation() + airventForward * 10.f;
			FRotator rotator = airventForward.Rotation();
			GetController()->SetControlRotation(controlRot + (rotator - controlRot) * .015f);

			if(progressRatio<=1.f)
			SetActorLocation(GetBezirCurve2(_startPos, _cPos1, _endPos, progressRatio));

			//마무리 작업
			if (progressRatio >= 1.5f)
			{
				PlayerMode = EPlayerMode::CREEPY;
				GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				PlayerAnim->StopAllMontages(0.8f);
				//PlayerAnim->SetLHandStanding(FVector::ZeroVector, FRotator::ZeroRotator, false);
				//PlayerAnim->SetRHandStanding(FVector::ZeroVector, FRotator::ZeroRotator, false);
				PlayerAnim->_bPlayerCreep = true;

				_stiffen = 0.f;
			}

			_currTime += DeltaTime;
			break;
		}
	
	}

	#pragma endregion
}

void AGamePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	#pragma region Omission
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(
		TEXT("UpDown"), this, &AGamePlayerCharacter::MoveUpDown
	);

	PlayerInputComponent->BindAxis(
		TEXT("LeftRight"), this, &AGamePlayerCharacter::MoveRightLeft
	);

	PlayerInputComponent->BindAxis(
		TEXT("Turn"), this, &AGamePlayerCharacter::Turn
	);

	PlayerInputComponent->BindAxis(
		TEXT("LookUp"), this, &AGamePlayerCharacter::LookUp
	);

	PlayerInputComponent->BindAction(
		TEXT("Jump"), EInputEvent::IE_Pressed, this, &AGamePlayerCharacter::JumpStart
	);

	PlayerInputComponent->BindAction(
		TEXT("StageRestart"), EInputEvent::IE_Pressed, this, &AGamePlayerCharacter::StageRestart
	);

	PlayerInputComponent->BindAction(
		TEXT("Jump"), EInputEvent::IE_Released, this, &AGamePlayerCharacter::JumpEnd
	);

	PlayerInputComponent->BindAction(
		TEXT("Reset"), EInputEvent::IE_Pressed, this, &AGamePlayerCharacter::ResetMagnetic
	);

	PlayerInputComponent->BindAction(
		TEXT("ShootMine"), EInputEvent::IE_Pressed, this, &AGamePlayerCharacter::OnShootMine
	);

	PlayerInputComponent->BindAction(
		TEXT("ShootMine"), EInputEvent::IE_Released, this, &AGamePlayerCharacter::OffShootMine
	);

	PlayerInputComponent->BindAction(
		TEXT("Shoot_N"), EInputEvent::IE_Pressed, this, &AGamePlayerCharacter::ShootMagnetic_N
	);

	PlayerInputComponent->BindAction(
		TEXT("Shoot_S"), EInputEvent::IE_Pressed, this, &AGamePlayerCharacter::ShootMagnetic_S
	);

	PlayerInputComponent->BindAction(
		TEXT("TimeStop"), EInputEvent::IE_Pressed, this, &AGamePlayerCharacter::ApplyTimeStop
	);

#pragma endregion
}

#if WITH_EDITOR
void AGamePlayerCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent)
{
	const FString& changed = PropertyChangeEvent.GetPropertyName().ToString();

	if (changed == "JumpPower")
	{
		GetCharacterMovement()->JumpZVelocity = JumpPower;
	}
	else if (changed == "MoveSpeed")
	{
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	}
}
#endif

void AGamePlayerCharacter::LookUp(float value)
{
	if (_stiffen != 0.f) return;

	//기어다니는 상태일 경우 각도 제한
	if (PlayerMode==EPlayerMode::CREEPY)
	{
		FVector forward = GetActorForwardVector();
		FVector up = GetActorUpVector();
		FVector right = GetActorRightVector();
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		FHitResult result;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);

		bool ret = GetWorld()->LineTraceSingleByChannel(
			result,
			GetActorLocation(),
			GetActorLocation() - (up * value * 250.f),
			ECollisionChannel::ECC_Visibility,
			params
		);

		if (ret) return;
	}

	FRotator currRot = GetControlRotation();

	currRot.Pitch -= CameraRotationSpeed * value * GetWorld()->GetDeltaSeconds();
	GetController()->SetControlRotation(currRot);
}

void AGamePlayerCharacter::Turn(float value)
{
	if (_stiffen != 0.f) return;

	//기어다니는 상태일 경우 각도 제한
	if (PlayerMode == EPlayerMode::CREEPY)
	{
		FVector forward = GetActorForwardVector();
		FVector right = GetActorRightVector();
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		FHitResult result;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);

		bool ret = GetWorld()->LineTraceSingleByChannel(
			result,
			GetActorLocation(),
			GetActorLocation() + (right * value * 250.f),
			ECollisionChannel::ECC_Visibility,
			params
		);

		if (ret) return;
	}

	FRotator currRot = GetControlRotation();

	currRot.Yaw += CameraRotationSpeed * value * GetWorld()->GetDeltaSeconds();
	GetController()->SetControlRotation(currRot);
}

void AGamePlayerCharacter::MoveUpDown(float value)
{
	if (_stiffen != 0.f) return;
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector dir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(dir, value);
}
void AGamePlayerCharacter::MoveRightLeft(float value)
{
	if (_stiffen != 0.f) return;
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector dir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(dir, value);
}

void AGamePlayerCharacter::OnShootMine()
{
	if (_stiffen != 0.f) return;
	_bShootMine = true;
}

void AGamePlayerCharacter::OffShootMine()
{
	if (_stiffen != 0.f) return;
	_bShootMine = false;
}

void AGamePlayerCharacter::JumpStart()
{
	if (_stiffen != 0.f) return;
	_bCanJump = true;
}
void AGamePlayerCharacter::JumpEnd()
{
	if (_stiffen != 0.f) return;
	_bCanJump = false;
}

void AGamePlayerCharacter::FadeChange(bool isDark, int id)
{
	switch (id){
		/*섹션 페이드 아웃*/
		case(PLAYER_FADE_ID):
		{
			if (isDark == false) break;
			_CurrSection->SetSection(ESectionSettingType::SECTION_RESET_BEGIN_PLAY);
			break;
		}

		/*스톱타이머 UI 페이드 아웃*/
		case(STOPTIMER_FADE_ID):
		{
			if (isDark) break;
			if (TimerWidgetA && TimerWidgetA->IsVisible())
			{
				TimerWidgetA->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
				TimerWidgetA->SetVisibility(false);
			}

			if (TimerWidgetB && TimerWidgetB->IsVisible())
			{
				TimerWidgetB->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
				TimerWidgetB->SetVisibility(false);
			}

			break;
		}

	}
}

void AGamePlayerCharacter::StageRestart()
{
	#pragma region Omission

	//재시작 테스트
	//static bool apply = false;
	//GetWorldSettings()->SetTimeDilation(!apply?0.05f:1.f);
	//apply = !apply;
	//return;

	if (_stiffen != 0.f) return;
	TArray<UPrimitiveComponent*> overlaps;
	GetCapsuleComponent()->GetOverlappingComponents(overlaps);

	int32 count = overlaps.Num();
	for (auto p : overlaps)
	{
		_CurrSection = Cast<UGameMapSectionComponent>(p);
		if (_CurrSection.IsValid())
		{
			//Player UI를 받아온다.
			TWeakObjectPtr<UUIBlackScreenWidget> blackScreen;
			if (_Instance.IsValid())
			{
				_Instance->GetUIManager()->GetUIBlackScreenWidget(blackScreen);

				//페이드 인->아웃 실행.
				if (blackScreen.IsValid())
				{
					_Instance->GetUIManager()->PlayFadeInOut(
						EFadeType::WHITE_TO_DARK_TO_WHITE,
						blackScreen.Get(),
						2.f,
						2.f,
						1.f,
						0.f,
						0.f,
						1.f,
						PLAYER_FADE_ID,
						FLinearColor::Black,
						FLinearColor::Black
					);
				}
			}
			return;
		}
	}
	#pragma endregion
}

void AGamePlayerCharacter::ApplyTimeStop()
{
	if (_stiffen != 0.f || _timeStopCurrTime>0.f) return;

	#pragma region Omission

	//모든 페이드 아웃을 제거한다.
	if(_Instance.IsValid())
	{
		_Instance->GetUIManager()->StopFadeInOut(STOPTIMER_FADE_ID);
	}

	if (IsGivenInvalid(0))
	{
		//유효한 자석이라면 타임스탑 구조체에 추가한다.
		UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(_GivenMagnets[0]->GetAttachmentRoot());
		UPrimitiveComponent* attachPrimitive = _GivenMagnets[0]->GetAttachmentPrimitive();

		if (primitive && attachPrimitive)
		{
			//페이드 아웃 적용
			if (_Instance.IsValid())
			{
				FTimeStopMagnetInfo& info = _TimeStopMagnets[0];
				info.Magnetic = _GivenMagnets[0];
				info.DefaultCanMovement = info.Magnetic->bAllowMagneticMovement;
				info.DefaultApplyPhysics = primitive->IsSimulatingPhysics();

				TimerWidgetA->SetVisibility(true);
				TimerWidgetA->SetRelativeLocation(FVector(10.f, 0.f, 30.f));
				TimerWidgetA->AttachToComponent(attachPrimitive, FAttachmentTransformRules::KeepRelativeTransform);

				//페이드 아웃 적용.
				_Instance->GetUIManager()->PlayFadeInOut(
					EFadeType::WHITE_TO_DARK,
					TimerWidgetInsA,
					1.f,
					0.f,
					1.f,
					0.f,
					0.f,
					0.f,
					STOPTIMER_FADE_ID,
					FLinearColor::White,
					FLinearColor::White
				);

				primitive->SetSimulatePhysics(false);
				info.Magnetic->bAllowMagneticMovement = false;
			}
		}
	}

	if (IsGivenInvalid(1))
	{
		//유효한 자석이라면 타임스탑 구조체에 추가한다.
		UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(_GivenMagnets[1]->GetAttachmentRoot());
		UPrimitiveComponent* attachPrimitive = _GivenMagnets[1]->GetAttachmentPrimitive();

		if (primitive && attachPrimitive)
		{
			//페이드 아웃 적용
			if (_Instance.IsValid())
			{
				FTimeStopMagnetInfo& info = _TimeStopMagnets[1];
				info.Magnetic = _GivenMagnets[1];
				info.DefaultCanMovement = info.Magnetic->bAllowMagneticMovement;
				info.DefaultApplyPhysics = primitive->IsSimulatingPhysics();

				TimerWidgetB->SetVisibility(true);
				TimerWidgetB->SetRelativeLocation(FVector(10.f, 0.f, 30.f));
				TimerWidgetB->AttachToComponent(attachPrimitive, FAttachmentTransformRules::KeepRelativeTransform);

				_Instance->GetUIManager()->PlayFadeInOut(
					EFadeType::WHITE_TO_DARK,
					TimerWidgetInsB,
					1.f,
					0.f,
					1.f,
					0.f,
					0.f,
					0.f,
					STOPTIMER_FADE_ID,
					FLinearColor::White,
					FLinearColor::White
				);

				primitive->SetSimulatePhysics(false);
				info.Magnetic->bAllowMagneticMovement = false;
			}
		}
	}

	_timeStopCurrTime = MaxTimeStopSeconds;

	#pragma endregion
}

void AGamePlayerCharacter::UnApplyTimeStop()
{
	#pragma region Omission

	if (PlayerAnim) PlayerAnim->PlayResetMontage();

	//페이드 이벤트 종료
	if (_Instance.IsValid())
	{
		_Instance->GetUIManager()->StopFadeInOut(STOPTIMER_FADE_ID);
	}

	//첫번째 타임스탑 자석이 유효할 경우
	if (_TimeStopMagnets[0].Magnetic.IsValid())
	{
		//기본값으로 복원.
		FTimeStopMagnetInfo& info = _TimeStopMagnets[0];
		info.Magnetic->bAllowMagneticMovement = info.DefaultCanMovement;
		if (UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(info.Magnetic->GetAttachmentRoot()))
		{
			primitive->SetSimulatePhysics(info.DefaultApplyPhysics);
			primitive->SetEnableGravity(info.Magnetic->GetDefaultEnabledGravity());
		}

		//페이드 아웃 적용
		if (_Instance.IsValid())
		{
			_Instance->GetUIManager()->PlayFadeInOut(
				EFadeType::DARK_TO_WHITE,
				TimerWidgetInsA,
				0.f,
				1.f,
				1.f,
				0.f,
				0.f,
				0.f,
				STOPTIMER_FADE_ID,
				FLinearColor::White,
				FLinearColor::White
			);
		}

		info.Magnetic.Reset();
	}

	//두번째 타임스탑 자석이 유효할 경우
	if (_TimeStopMagnets[1].Magnetic.IsValid())
	{
		//기본값으로 복원.
		FTimeStopMagnetInfo& info = _TimeStopMagnets[1];
		info.Magnetic->bAllowMagneticMovement = info.DefaultCanMovement;
		if (UPrimitiveComponent* primitive = Cast<UPrimitiveComponent>(info.Magnetic->GetAttachmentRoot()))
		{
			primitive->SetSimulatePhysics(info.DefaultApplyPhysics);
			primitive->SetEnableGravity(info.Magnetic->GetDefaultEnabledGravity());
		}

		//페이드 아웃 적용
		if (_Instance.IsValid())
		{
			_Instance->GetUIManager()->PlayFadeInOut(
				EFadeType::DARK_TO_WHITE,
				TimerWidgetInsB,
				0.f,
				1.f,
				1.f,
				0.f,
				0.f,
				0.f,
				STOPTIMER_FADE_ID,
				FLinearColor::White,
				FLinearColor::White
			);
		}

		info.Magnetic.Reset();
	}
	#pragma endregion
}

void AGamePlayerCharacter::ResetMagnetic()
{
	if (_stiffen != 0.f) return;
	
	//UI 초기화
	TWeakObjectPtr<UPlayerUICanvasWidget> playerUI;
	if (_Instance.IsValid())
	{
		_Instance->GetUIManager()->GetPlayerUICanvasWidget(playerUI);
		if (playerUI.IsValid())
		{
			playerUI->GetMagneticInfoWidget()->ClearInfo();
		}
	}

	PlayerAnim->PlayResetMontage();
	GetMovementComponent()->SetActive(true);

	if (_StickTo != nullptr)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		_StickTo = nullptr;
	}

	if (IsGivenInvalid(0)) _GivenMagnets[0]->SetCurrentMagnetic(EMagneticType::NONE);
	if (IsGivenInvalid(1)) _GivenMagnets[1]->SetCurrentMagnetic(EMagneticType::NONE);

	ClearGivens();
}

void AGamePlayerCharacter::ShootMagnetic_N()
{
	if (_stiffen != 0.f) return;
	if (PlayerAnim && PlayerAnim->GetAttackMontageIsPlaying()) return;

	if (_bShootMine)
	{
		ShootMine(EMagneticType::N);
		return;
	}

	Shoot(EMagneticType::N);
}

void AGamePlayerCharacter::ShootMagnetic_S()
{
	if (_stiffen != 0.f) return;
	if (PlayerAnim && PlayerAnim->GetAttackMontageIsPlaying()) return;

	if (_bShootMine)
	{
		ShootMine(EMagneticType::S);
		return;
	}

	Shoot(EMagneticType::S);
}

void AGamePlayerCharacter::Shoot(EMagneticType shootType)
{
	if (_stiffen != 0.f) return;
	#pragma region Omission

	//몽타주 실행
	if(PlayerAnim) PlayerAnim->PlayAttackMontage();

	//이펙트 실행
	if (ShootEffectComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("location: %s"), *ShootEffectComp->GetComponentLocation().ToString())
		ShootEffectComp->ResetSystem();
		ShootEffectComp->Activate();
	}


	//if (ShootEffect)
	//{
	//	FVector forward = GetPlayerForwardVector();
	//	FVector right = GetPlayerRightVector();
	//	FVector down = GetPlayerDownVector();

	//	FVector neckPos = GetMesh()->GetSocketLocation(PLAYER_NECK_BONE);
	//	FVector gunPos = GetMesh()->GetSocketLocation(PLAYER_GUN_BONE);

	//	UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	//		GetWorld(),
	//		ShootEffect,
	//		neckPos + forward * 40.f+right*22.f+down*20.f,
	//		GetControlRotation(),
	//		FVector(5.f, 5.f, 5.f)
	//	);

	//	effect->SetVectorParameter(TEXT("Look"), forward);
	//}

	//발사 위치 구하기
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc == nullptr) return;

	int32 sSizeX, sSizeY;
	pc->GetViewportSize(sSizeX, sSizeY);

	FVector center(sSizeX * .5f, sSizeY * .5f, .0f);
	FVector worldLocation;
	FVector worldDir;
	pc->DeprojectScreenPositionToWorld(center.X, center.Y, worldLocation, worldDir);

	//발사 및 감지
	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	FVector start = worldLocation;
	FVector end = worldLocation + worldDir * ShootLength;
	if (GetWorld()->SweepSingleByChannel(
		hit, start, end, FQuat::Identity, ECollisionChannel::ECC_Visibility,
		FCollisionShape::MakeBox(ShootExtend), params))
	{
		UMeshComponent* hitComponent = Cast<UMeshComponent>(hit.GetComponent());

		if (hitComponent != nullptr && ::IsValid(hitComponent))
		{
			TArray<USceneComponent*> childrens;
			hitComponent->GetChildrenComponents(false, childrens);

			for (int i = childrens.Num() - 1; i >= 0; i--)
			{
				UMagneticComponent* mag = Cast<UMagneticComponent>(childrens[i]);
				if (mag && ::IsValid(mag))
				{
					GivenTestMagnet(mag, shootType);
					return;
				}
			}
		}
	}
#pragma endregion
}

void AGamePlayerCharacter::ShootMine(EMagneticType shootType)
{
	if (_stiffen != 0.f) return;
	GivenTestMagnet(Magnetic, shootType);
}

void AGamePlayerCharacter::GivenTestMagnet(UMagneticComponent* newMagnet, EMagneticType givenType)
{
	#pragma region Omission
	if (newMagnet == nullptr || !::IsValid(newMagnet)) return;

	newMagnet->SetCurrentMagnetic(givenType);

	bool alreadyGiven = IsAlreadyGiven(newMagnet);
	bool isFulledGiven = IsFulledGiven();

	TWeakObjectPtr<UPlayerUICanvasWidget> playerUI;
	if (_Instance.IsValid())
	{
		_Instance->GetUIManager()->GetPlayerUICanvasWidget(playerUI);
	}

	//이미 기존의 리스트에 존재할 경우
	if (alreadyGiven == false)
	{
		//UI를 갱신하고 마무리짓는다.
		if (playerUI.IsValid())
		{
			playerUI->GetMagneticInfoWidget()->SetInfo(_GivenMagnets[0], _GivenMagnets[1]);
		}

		return;
	}

	if (alreadyGiven)
	{
		//리스트가 가득찼다면 
		//기존에 있던 요소에서 가장 오래된 것을 제거하고, 새 것으로 교체한다.
		if (isFulledGiven) {

			UMagneticComponent* old = _GivenMagnets[_oldGivenIndex];

			if (old != nullptr && ::IsValid(old))
				old->SetCurrentMagnetic(EMagneticType::NONE);

			_GivenMagnets[_oldGivenIndex] = newMagnet;
		}
		//리스트가 가득차지 않았다면 빈칸에 채워넣는다.
		else
		{
			for (int i = 0; i < 2; i++)
			{
				if (_GivenMagnets[i] != nullptr) continue;
				_GivenMagnets[i] = newMagnet;
				if (_givenIndex == 0) _oldGivenIndex = i;
				_givenIndex++;
				break;
			}
		}

		if (playerUI.IsValid())
		{
			playerUI->GetMagneticInfoWidget()->SetInfo(_GivenMagnets[0], _GivenMagnets[1]);
		}
	}
#pragma endregion
}

bool AGamePlayerCharacter::IsGivenInvalid(int index) const
{
	return _GivenMagnets[index] && ::IsValid(_GivenMagnets[index]);
}

bool AGamePlayerCharacter::IsAlreadyGiven(UMagneticComponent* element) const
{
	if (element == nullptr || !::IsValid(element)) return false;
	return !(_GivenMagnets[0] == element || _GivenMagnets[1] == element);

	return false;
}

void AGamePlayerCharacter::RemoveGiven(UMagneticComponent* remove)
{
	if (remove == nullptr || !::IsValid(remove)) return;

	if (_GivenMagnets[0] == remove)
	{
		_GivenMagnets[0]->SetCurrentMagnetic(EMagneticType::NONE);
		_GivenMagnets[0] = nullptr;
		_givenIndex--;
		if (_GivenMagnets[1] != nullptr) _oldGivenIndex = 1;
	}
	else if (_GivenMagnets[1] == remove)
	{
		_GivenMagnets[1]->SetCurrentMagnetic(EMagneticType::NONE);
		_GivenMagnets[1] = nullptr;
		_givenIndex--;
		if (_GivenMagnets[0] != nullptr) _oldGivenIndex = 0;
	}

	TWeakObjectPtr<UPlayerUICanvasWidget> playerUI;
	if (_Instance.IsValid())
	{
		_Instance->GetUIManager()->GetPlayerUICanvasWidget(playerUI);
		if (playerUI.IsValid())
		{
			playerUI->GetMagneticInfoWidget()->ClearInfo();
			playerUI->GetMagneticInfoWidget()->SetInfo(_GivenMagnets[0], _GivenMagnets[1]);
		}
	}
}

void AGamePlayerCharacter::OnMagnetic(EMagneticType type, UMagneticComponent* magnet)
{
	if (type != EMagneticType::NONE && PlayerAnim) PlayerAnim->PlaySelfShootMontage(.3f, .85f);
}

void AGamePlayerCharacter::OffMagnetic(EMagneticType prevType, UMagneticComponent* magnet)
{
	if (PlayerAnim)
	{
		if (PlayerAnim->GetResetMontageIsPlaying() == false)
			PlayerAnim->PlaySelfResetMontage();

		PlayerAnim->SetHandLookMagnetic(EHandType::LEFT, false);
	}
	
	//RemoveGiven(Magnetic);
}

void AGamePlayerCharacter::MagnetMoveStart(EMagnetMoveType moveType, UMagneticComponent* magnet)
{
	if (_StickTo.IsValid())
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		_StickTo.Reset();
	}

	switch (moveType) {

	case(EMagnetMoveType::DRAWN_IN):
		PlayerAnim->PlayGlovePulledUpMotage();
		PlayerAnim->SetHandLookMagnetic(EHandType::LEFT, true, magnet);
		GetMovementComponent()->SetActive(false);
		break;

	case(EMagnetMoveType::PUSHED_OUT):
		GetMovementComponent()->SetActive(true);
		break;
	}
}

void AGamePlayerCharacter::MagnetMoveEnd(EMagnetMoveType moveType, UMagneticComponent* magnet)
{

}

void AGamePlayerCharacter::MagnetMoveHit(AActor* hit, UMagneticComponent* magnet)
{
	if (hit == nullptr) return;

	if (Magnetic->GetCurrentMagnetic() != EMagneticType::NONE)
	{
		_StickTo.Reset();
		_StickTo = hit;
		AttachToActor(hit, FAttachmentTransformRules::KeepWorldTransform);
		PlayerAnim->PlayGloveStickMotage();
	}
}
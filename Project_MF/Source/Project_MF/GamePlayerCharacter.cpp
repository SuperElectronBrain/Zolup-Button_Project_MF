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

	//CDO
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	PLAYER_MESH(
		TEXT("/Game/PlayerCharacter/Meshs/PlayerArmMeshNew.PlayerArmMeshNew")
	);
	static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> ANIM_BLUEPRINT(
		TEXT("/Game/PlayerCharacter/Animation/PlayerAnimBlueprint")
	);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_CANVAS(
		TEXT("/Game/UI/PlayerUI_Canvas")
	);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SHOOT_EFFECT_SYSTEM(
		TEXT("/Game/Effect/Gun/Gun_effect_shoot_n.Gun_effect_shoot_n")
	);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> MAGNETIC_EFFECT_SYSTEM(
		TEXT("/Game/Effect/Gun/Gun_effect_defalt_n.Gun_effect_defalt_n")
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
	Camera->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 8.5f), FRotator::ZeroRotator);

	/*CapsuleComponents*/
	GetCapsuleComponent()->SetCapsuleRadius(160.4f);/*default: 80.f*/
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

	/*Player UI*/
	if (UI_CANVAS.Succeeded())
	{
		PlayUIClass = UI_CANVAS.Class;
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
	
	#pragma endregion
}

void AGamePlayerCharacter::SetPlayerMode(EPlayerMode mode)
{
	PlayerMode = mode;
	UNiagaraFunctionLibrary;

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

	/*Magnetic*/
	if (Magnetic)
	{
		Magnetic->OnMagneticEvent.AddUObject(this, &AGamePlayerCharacter::OnMagnetic);
		Magnetic->OffMagneticEvent.AddUObject(this, &AGamePlayerCharacter::OffMagnetic);
		Magnetic->MagnetMoveStartEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveStart);
		//Magnetic->MagnetMoveEndEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveEnd);
		Magnetic->MagnetMoveHitEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveHit);
	}
	
	//카메라 페이드 아웃
	APlayerController* c = Cast<APlayerController>(GetController());
	if (c)
	{
		APlayerCameraManager* cm = c->PlayerCameraManager;
		cm->StartCameraFade(1.f, 0.f, 1.f, FLinearColor::Black);
	}


	//애님 인스턴스 참조
	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	//UI띄우기
	PlayUIInstance = Cast<UPlayerUICanvasWidget>(CreateWidget(GetWorld(), PlayUIClass));

	if (PlayUIInstance != nullptr)
	{
		PlayUIInstance->AddToViewport();
		PlayUIInstance->SetAnimColor(FColor(255, 255, 255, 150));
	}

	//캡슐 콜라이더 수정
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

	////발사 이펙트 추가.
	//if (ShootEffect)
	//{
	//	ShootEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
	//		ShootEffect,
	//		GetMesh(),
	//		TEXT("ShootSocket"),
	//		FVector(30.f, 0.f, 0.f),
	//		FRotator::ZeroRotator,
	//		FVector(50.f, 50.f, 50.f),
	//		EAttachLocation::SnapToTargetIncludingScale,
	//		false, 
	//		ENCPoolMethod::None
	//	);
	//}
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

	//점프키를 꾹 누르면 점프
	if (_bCanJump && _stiffen == 0.f)
	{
		Jump();
	}

	//기어다닐 때의 카메라 변화
	if (PlayerMode==EPlayerMode::CREEPY)
	{
		
	}
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

	FRotator currRot = GetControlRotation();

	currRot.Pitch -= CameraRotationSpeed * value * GetWorld()->GetDeltaSeconds();
	GetController()->SetControlRotation(currRot);
}

void AGamePlayerCharacter::Turn(float value)
{
	if (_stiffen != 0.f) return;
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

void AGamePlayerCharacter::FadeWait(UGameMapSectionComponent* section)
{
	section->SetSection(ESectionSettingType::SECTION_RESET_BEGIN_PLAY);
	APlayerCameraManager* c = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	if (c) c->StartCameraFade(1.f, 0.f, 1.f, FLinearColor::Black, false, true);
}

void AGamePlayerCharacter::StageRestart()
{
	if (_stiffen != 0.f) return;
	TArray<UPrimitiveComponent*> overlaps;
	GetCapsuleComponent()->GetOverlappingComponents(overlaps);

	int32 count = overlaps.Num();
	for (auto p : overlaps)
	{
		UGameMapSectionComponent* section = Cast<UGameMapSectionComponent>(p);
		if (section && ::IsValid(section))
		{
			APlayerCameraManager* c = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
			if (c) c->StartCameraFade(0.f, 1.f, 1.f, FLinearColor::Black, false, true);

			FTimerHandle handle;
			FTimerDelegate callback = FTimerDelegate::CreateUObject(
				this,
				&AGamePlayerCharacter::FadeWait,
				section
			);

			GetWorld()->GetTimerManager().SetTimer(
				handle,
				callback,
				2.f,
				false
			);
			return;
		}
	}
}

void AGamePlayerCharacter::ResetMagnetic()
{
	if (_stiffen != 0.f) return;
	//UI 초기화
	PlayUIInstance->GetMagneticInfoWidget()->ClearInfo();
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
	if (ShootEffect)
	{
		FVector forward = GetPlayerForwardVector();
		FVector right = GetPlayerRightVector();
		FVector down = GetPlayerDownVector();

		FVector neckPos = GetMesh()->GetSocketLocation(PLAYER_NECK_BONE);
		FVector gunPos = GetMesh()->GetSocketLocation(PLAYER_GUN_BONE);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ShootEffect,
			neckPos + forward * 40.f+right*22.f+down*20.f,
			GetControlRotation(),
			FVector(5.f, 5.f, 5.f)
		);

	}

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
	newMagnet->SetCurrentMagnetic(givenType);

	bool alreadyGiven = IsAlreadyGiven(newMagnet);
	bool isFulledGiven = IsFulledGiven();

	//이미 기존의 리스트에 존재할 경우
	if (alreadyGiven == false)
	{
		//UI를 갱신하고 마무리짓는다.
		PlayUIInstance->GetMagneticInfoWidget()->SetInfo(_GivenMagnets[0], _GivenMagnets[1]);
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

		PlayUIInstance->GetMagneticInfoWidget()->SetInfo(_GivenMagnets[0], _GivenMagnets[1]);
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

	PlayUIInstance->GetMagneticInfoWidget()->ClearInfo();
	PlayUIInstance->GetMagneticInfoWidget()->SetInfo(_GivenMagnets[0], _GivenMagnets[1]);
}

void AGamePlayerCharacter::OnMagnetic(EMagneticType type, UMagneticComponent* magnet)
{
	if (type != EMagneticType::NONE) PlayerAnim->PlaySelfShootMontage(.3f, .85f);
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
	if (_StickTo != nullptr)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		_StickTo = nullptr;
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
		_StickTo = hit;
		AttachToActor(hit, FAttachmentTransformRules::KeepWorldTransform);
		PlayerAnim->PlayGloveStickMotage();
	}
}
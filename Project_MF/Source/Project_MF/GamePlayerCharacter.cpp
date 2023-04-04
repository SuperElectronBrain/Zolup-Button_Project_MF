// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "PlayerUICanvasWidget.h"
#include "MagneticComponent.h"
#include "DefaultMagneticMovementComponent.h"

AGamePlayerCharacter::AGamePlayerCharacter()
{
	#pragma region Summary
	//Intialized Properts and Fields
	PrimaryActorTick.bCanEverTick = true;
	ShootLength = 10000.f;
	ShootExtend.Set(2.f, 2.f, 2.f);
	JumpPower = 1600.f;
	CameraRotationSpeed = 420.f;
	MoveSpeed = 460.f;
	_bCanJump = false;
	_bShootMine = false;
	_GivenIndex = _OldGivenIndex = 0;
	_StickTo = nullptr;

	//CDO
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	PLAYER_MESH(
		TEXT("/Game/Resource/PlayerCharacter/Meshs/Character_arm.Character_arm")
	);
	static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> ANIM_BLUEPRINT(
		TEXT("/Game/Resource/PlayerCharacter/Animations/PlayerCharacterBlueprint")
	);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_CANVAS(
		TEXT("/Game/UI/PlayerUI_Canvas")
	);

	/*SpringArm*/
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	SpringArm->TargetArmLength = 10.f;
	SpringArm->SetRelativeLocationAndRotation(FVector(.0f, .0f, 40.f), FRotator::ZeroRotator);

	/*Camera*/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	/*CapsuleComponents*/
	GetCapsuleComponent()->SetCapsuleRadius(30.f);

	/*Player Mesh*/
	USkeletalMeshComponent* PlayerMesh = GetMesh();
	PlayerMesh->SetupAttachment(SpringArm);
	if (PLAYER_MESH.Succeeded())
	{
		PlayerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlayerMesh->SetRelativeLocationAndRotation(FVector(4.f, -2.f, -112.f), FRotator::MakeFromEuler(FVector(0.f, 0.f, 295.f)));
		PlayerMesh->SetSkeletalMesh(PLAYER_MESH.Object);
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
	Magnetic->SetMagneticFieldRadius(300.f);
	Magnetic->SetFixedWeight(1.f);

	#pragma endregion
}

void AGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*Magnetic*/
	if (Magnetic)
	{
		Magnetic->OnMagneticEvent.AddUObject(this, &AGamePlayerCharacter::OnMagnetic);
		//Magnetic->OffMagneticEvent.AddUObject(this, &AGamePlayerCharacter::OffMagnetic);
		Magnetic->MagnetMoveStartEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveStart);
		Magnetic->MagnetMoveEndEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveEnd);
		Magnetic->MagnetMoveHitEvent.AddUObject(this, &AGamePlayerCharacter::MagnetMoveHit);
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

	//왼쪽팔 본의 위치를 수정한다.
	PlayerAnim->_ArmLAddOffsetTransform.SetLocation(FVector(-7.f, 7.f, -12.f));
	PlayerAnim->_ArmLAddOffsetTransform.SetRotation(FQuat(FRotator::MakeFromEuler(FVector(0.f, 0.f, -39.f))));
}

void AGamePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//점프키를 꾹 누르면 점프
	if (_bCanJump)
	{
		Jump();
		UDefaultMagneticMovementComponent;
	}
}

void AGamePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	#pragma region Summary
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
	FRotator currRot = GetControlRotation();

	currRot.Pitch -= CameraRotationSpeed * value * GetWorld()->GetDeltaSeconds();
	GetController()->SetControlRotation(currRot);
}

void AGamePlayerCharacter::Turn(float value)
{
	FRotator currRot = GetControlRotation();

	currRot.Yaw += CameraRotationSpeed * value * GetWorld()->GetDeltaSeconds();
	GetController()->SetControlRotation(currRot);
}

void AGamePlayerCharacter::MoveUpDown(float value)
{
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector dir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(dir, value);
}
void AGamePlayerCharacter::MoveRightLeft(float value)
{
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector dir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(dir, value);
}

void AGamePlayerCharacter::OnShootMine()
{
	_bShootMine = true;
}

void AGamePlayerCharacter::OffShootMine()
{
	_bShootMine = false;
}

void AGamePlayerCharacter::JumpStart()
{
	_bCanJump = true;
}
void AGamePlayerCharacter::JumpEnd()
{
	_bCanJump = false;
}

void AGamePlayerCharacter::ResetMagnetic()
{
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
	if (PlayerAnim->GetAttackMontageIsPlaying()) return;

	if (_bShootMine)
	{
		ShootMine(EMagneticType::N);
		return;
	}

	Shoot(EMagneticType::N);
}

void AGamePlayerCharacter::ShootMagnetic_S()
{
	if (PlayerAnim->GetAttackMontageIsPlaying()) return;

	if (_bShootMine)
	{
		ShootMine(EMagneticType::S);
		return;
	}

	Shoot(EMagneticType::S);
}

void AGamePlayerCharacter::Shoot(EMagneticType shootType)
{
	#pragma region Summary

	//몽타주 실행
	PlayerAnim->PlayAttackMontage();

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
			
			for (int i=childrens.Num()-1; i>=0 ; i--)
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
	GivenTestMagnet(Magnetic, shootType);
}

void AGamePlayerCharacter::GivenTestMagnet(UMagneticComponent* newMagnet, EMagneticType givenType)
{
	#pragma region Summary
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
		UE_LOG(LogTemp, Warning, TEXT("가득참: %d(%d)"), _givenIndex, isFulledGiven)

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

void AGamePlayerCharacter::OnMagnetic(EMagneticType type)
{
	//UE_LOG(LogTemp, Warning, TEXT("자성이 부여됨!!!"))
}

void AGamePlayerCharacter::OffMagnetic(EMagneticType prevType)
{
	//UE_LOG(LogTemp, Warning, TEXT("자성이 사라짐!!!"))
}

void AGamePlayerCharacter::MagnetMoveStart(EMagnetMoveType moveType)
{
	//UE_LOG(LogTemp, Warning, TEXT("자성 움직임 시작!!!"))

	if (_StickTo != nullptr)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		_StickTo = nullptr;
	}

	switch (moveType) {

	case(EMagnetMoveType::DRAWN_IN):
		GetMovementComponent()->SetActive(false);
		break;

	case(EMagnetMoveType::PUSHED_OUT):
		GetMovementComponent()->SetActive(true);
		break;
	}
}

void AGamePlayerCharacter::MagnetMoveEnd(EMagnetMoveType moveType)
{
	//UE_LOG(LogTemp, Warning, TEXT("자성 움직임 끝!!!"))
}

void AGamePlayerCharacter::MagnetMoveHit(AActor* hit)
{
	if (hit == nullptr) return;

	//UE_LOG(LogTemp, Warning, TEXT("자석에 붙음!!"))
		if (Magnetic->GetCurrentMagnetic() != EMagneticType::NONE)
		{
			_StickTo = hit;
			AttachToActor(hit, FAttachmentTransformRules::KeepWorldTransform);

			//플레이어 자성 초기화
			RemoveGiven(Magnetic);
		}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "PlayerUICanvasWidget.h"
#include "MagneticComponent.h"
#include "DefaultMagneticMovementComponent.h"
#include "DrawDebugHelpers.h"

APlayerCharacter::APlayerCharacter()
{
	#pragma region Summary
	//setting
	PrimaryActorTick.bCanEverTick = true;
	ReloadType = EMagneticType::NONE;
	ShootLength = 10000.f;
	ShootExtend.Set(20.f, 20.f, 20.f);
	JumpPower = 1600.f;
	CameraRotationSpeed = 420.f;
	MoveSpeed = 460.f;
	_bCanJump = false;
	_bShootMine = false;
	_givenIndex = _oldGivenIndex = 0;
	_StickTo = nullptr;

	_GivenMagnets[0] = _GivenMagnets[1] = nullptr;

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

	//CreateComponents
	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PLAYER_MESH"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Magnetic = CreateDefaultSubobject<UMagneticComponent>(TEXT("MAGNETIC"));
	MagMovement = CreateDefaultSubobject<UDefaultMagneticMovementComponent>(TEXT("DEFAULT_MAG_MOVEMENT"));

	//Attachment Components
	SpringArm->SetupAttachment(GetCapsuleComponent());
	PlayerMesh->SetupAttachment(SpringArm);
	Camera->SetupAttachment(SpringArm);
	Magnetic->SetupAttachment(GetCapsuleComponent());

	///Intialize Components
	/*Capsule*/
	GetCapsuleComponent()->SetCapsuleRadius(30.f);

	/*SpringArm And Camera*/
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	SpringArm->TargetArmLength = _zoomInLength = 10.f;
	SpringArm->SetRelativeLocationAndRotation(FVector(.0f, .0f, 40.f), FRotator::ZeroRotator);

	/*Apply Mesh*/
	if (PLAYER_MESH.Succeeded())
	{
		PlayerMesh->SetRelativeLocationAndRotation(FVector(1.f, 6.31f, -120.f), FRotator(0.f, -90.f, 0.f));
		PlayerMesh->SetSkeletalMesh(PLAYER_MESH.Object);
		PlayerMesh->bCastDynamicShadow = false;
		PlayerMesh->SetCastShadow(false);
		PlayerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	/*Apply blueprint*/
	if (ANIM_BLUEPRINT.Succeeded())
	{
		PlayerMesh->SetAnimInstanceClass(ANIM_BLUEPRINT.Class);
	}

	/*Apply Canvas*/
	if (UI_CANVAS.Succeeded())
	{
		PlayUIClass = UI_CANVAS.Class;
	}

	//CharacterMovement
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->JumpZVelocity = JumpPower;
	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->bJustTeleported = false;
	GetCharacterMovement()->GravityScale = 4.f;
	GetCharacterMovement()->FallingLateralFriction = 2.f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

	//Magnetic
	Magnetic->SetMagneticFieldRadius(300.f);
	Magnetic->SetFixedWeight(1.f);
	#pragma endregion
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UE_LOG(LogTemp, Warning, TEXT("빙의됨!!!"))
}

bool APlayerCharacter::IsGivenInvalid(int index) const
{
	return _GivenMagnets[index] && ::IsValid(_GivenMagnets[index]);
}

bool APlayerCharacter::IsAlreadyGiven(UMagneticComponent* element) const
{
	if (element == nullptr || !::IsValid(element)) return false;
	return !( _GivenMagnets[0]==element || _GivenMagnets[1]==element);

	return false;
}

#if WITH_EDITOR
void APlayerCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent)
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

void APlayerCharacter::LookUp(float value)
{
	FRotator currRot = GetControlRotation();

	currRot.Pitch -= CameraRotationSpeed * value * GetWorld()->GetDeltaSeconds();
	GetController()->SetControlRotation(currRot);
}

void APlayerCharacter::Turn(float value)
{
	FRotator currRot = GetControlRotation();

	currRot.Yaw += CameraRotationSpeed * value * GetWorld()->GetDeltaSeconds();
	GetController()->SetControlRotation(currRot);
}

void APlayerCharacter::OnMagnetic(EMagneticType type)
{
	UE_LOG(LogTemp, Warning, TEXT("자성이 부여됨!!!"))
}

void APlayerCharacter::OffMagnetic(EMagneticType prevType)
{
	UE_LOG(LogTemp, Warning, TEXT("자성이 사라짐!!!"))
}

void APlayerCharacter::MagnetMoveStart(EMagnetMoveType moveType)
{
	UE_LOG(LogTemp, Warning, TEXT("자성 움직임 시작!!!"))
	_zoomInLength = 15.f;

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

void APlayerCharacter::MagnetMoveEnd(EMagnetMoveType moveType)
{
	UE_LOG(LogTemp, Warning, TEXT("자성 움직임 끝!!!"))
	_zoomInLength = 10.f;
}

void APlayerCharacter::MagnetMoveHit(AActor* hit)
{
	if (hit == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("자석에 붙음!!"))
	if (Magnetic->GetCurrentMagnetic() != EMagneticType::NONE)
	{
		_StickTo = hit;
		AttachToActor(hit, FAttachmentTransformRules::KeepWorldTransform);

		//플레이어 자성 초기화
		RemoveGiven(Magnetic);
	}
}

void APlayerCharacter::RemoveGiven(UMagneticComponent* remove)
{
	if (remove == nullptr || !::IsValid(remove)) return;

	if (_GivenMagnets[0]==remove)
	{
		_GivenMagnets[0]->SetCurrentMagnetic(EMagneticType::NONE);
		_GivenMagnets[0] = nullptr;
		_givenIndex--;
		if (_GivenMagnets[1]!=nullptr) _oldGivenIndex = 1;
	}
	else if (_GivenMagnets[1]==remove)
	{
		_GivenMagnets[1]->SetCurrentMagnetic(EMagneticType::NONE);
		_GivenMagnets[1] = nullptr;
		_givenIndex--;
		if (_GivenMagnets[0] != nullptr) _oldGivenIndex = 0;
	}

	PlayUIInstance->GetMagneticInfoWidget()->ClearInfo();
	PlayUIInstance->GetMagneticInfoWidget()->SetInfo(_GivenMagnets[0], _GivenMagnets[1]);
}

void APlayerCharacter::MoveUpDown(float value)
{
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector dir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(dir, value);
}
void APlayerCharacter::MoveRightLeft(float value)
{
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector dir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(dir, value);
}

void APlayerCharacter::GivenTestMagnet(UMagneticComponent* newMagnet, EMagneticType givenType)
{
	newMagnet->SetCurrentMagnetic(givenType);

	bool alreadyGiven = IsAlreadyGiven(newMagnet);
	bool isFulledGiven = IsFulledGiven();

	//이미 기존의 리스트에 존재할 경우
	if (alreadyGiven==false)
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
				if(_givenIndex==0) _oldGivenIndex = i;
				_givenIndex++;
				break;
			}
		}

		PlayUIInstance->GetMagneticInfoWidget()->SetInfo(_GivenMagnets[0], _GivenMagnets[1]);
	}
}

void APlayerCharacter::Shoot(EMagneticType shootType)
{
	#pragma region Summary

	//몽타주 실행
	PlayerAnim->PlayAttackMontage();

	//발사 위치 구하기
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc==nullptr) return;

	int32 sSizeX, sSizeY;
	pc->GetViewportSize(sSizeX, sSizeY);

	FVector center(sSizeX*.5f, sSizeY*.5f, .0f);
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
		FCollisionShape::MakeBox(ShootExtend), params ))
	{
		AActor* hitActor = hit.GetActor();
		UPrimitiveComponent* hitComponent = hit.GetComponent();

		if (hitComponent !=nullptr && ::IsValid(hitComponent))
		{
			UMagneticComponent* mag = Cast<UMagneticComponent>(hitComponent->GetAttachParent());
			if (mag!=nullptr)
			{
				//이미 가지고 있는 자석인지 확인한다.
				GivenTestMagnet(mag, shootType);
			}
		}
		//else if (hitActor!=nullptr && ::IsValid(hitActor))
		//{
		//	UMagneticComponent* mag = hitActor->FindComponentByClass<UMagneticComponent>();
		//	if (mag != nullptr)
		//	{
		//		//이미 가지고 있는 자석인지 확인한다.
		//		GivenTestMagnet(mag, shootType);
		//	}
		//}
	}
	#pragma endregion
}

void APlayerCharacter::ShootMine(EMagneticType shootType)
{
	GivenTestMagnet(Magnetic, shootType);
}

void APlayerCharacter::ShootMagnetic_N()
{
	if (PlayerAnim->GetAttackMontageIsPlaying()) return;

	if (_bShootMine)
	{
		ShootMine(EMagneticType::N);
		return;
	}

	Shoot(EMagneticType::N);
}

void APlayerCharacter::ShootMagnetic_S()
{
	if (PlayerAnim->GetAttackMontageIsPlaying()) return;

	if (_bShootMine)
	{
		ShootMine(EMagneticType::S);
		return;
	}

	Shoot(EMagneticType::S);
}

void APlayerCharacter::OnShootMine()
{
	_bShootMine = true;
}

void APlayerCharacter::OffShootMine()
{
	_bShootMine = false;
}

void APlayerCharacter::JumpStart()
{
	_bCanJump = true;
}
void APlayerCharacter::JumpEnd()
{
	_bCanJump = false;
}

void APlayerCharacter::ResetMagnetic()
{
	//UI 초기화
	PlayUIInstance->GetMagneticInfoWidget()->ClearInfo();
	PlayerAnim->PlayResetMontage();
	GetMovementComponent()->SetActive(true);

	if (_StickTo!=nullptr)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		_StickTo = nullptr;
	}

	if (IsGivenInvalid(0)) _GivenMagnets[0]->SetCurrentMagnetic(EMagneticType::NONE);
	if (IsGivenInvalid(1)) _GivenMagnets[1]->SetCurrentMagnetic(EMagneticType::NONE);

	ClearGivens();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//총을 플레이어의 손 소켓에 장착.
	PlayerMesh->SetRelativeLocationAndRotation(FVector(1.f, 6.31f, -120.f), FRotator(0.f, 0.f, -90.f));

	//이벤트 적용
	Magnetic->OnMagneticEvent.AddUObject(this, &APlayerCharacter::OnMagnetic);
	Magnetic->OffMagneticEvent.AddUObject(this, &APlayerCharacter::OffMagnetic);
	Magnetic->MagnetMoveStartEvent.AddUObject(this, &APlayerCharacter::MagnetMoveStart);
	Magnetic->MagnetMoveEndEvent.AddUObject(this, &APlayerCharacter::MagnetMoveEnd);
	Magnetic->MagnetMoveHitEvent.AddUObject(this, &APlayerCharacter::MagnetMoveHit);
	//Magnetic->AddNoActiveMovement(GetCharacterMovement());

	//애님 인스턴스 참조
	PlayerAnim = Cast<UPlayerAnimInstance>(PlayerMesh->GetAnimInstance());

	//UI띄우기
	PlayUIInstance = Cast<UPlayerUICanvasWidget>(CreateWidget(GetWorld(), PlayUIClass));

	if (PlayUIInstance != nullptr)
	{
		PlayUIInstance->AddToViewport();
		PlayUIInstance->SetAnimColor(FColor(255, 255, 255, 150));
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO: 임시방편으로 해둔 위치 회전 재설정
	//PlayerMesh->SetRelativeLocationAndRotation(FVector(1.f, 6.31f, -120.f), FRotator(0.f, -90.f, 0.f));

	if (_bCanJump)
	{
		Jump();
	}
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	#pragma region Summary
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(
		TEXT("UpDown"), this, &APlayerCharacter::MoveUpDown
	);

	PlayerInputComponent->BindAxis(
		TEXT("LeftRight"), this, &APlayerCharacter::MoveRightLeft
	);

	PlayerInputComponent->BindAxis(
		TEXT("Turn"), this, &APlayerCharacter::Turn
	);

	PlayerInputComponent->BindAxis(
		TEXT("LookUp"), this, &APlayerCharacter::LookUp
	);

	PlayerInputComponent->BindAction(
		TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::JumpStart
	);

	PlayerInputComponent->BindAction(
		TEXT("Jump"), EInputEvent::IE_Released, this, &APlayerCharacter::JumpEnd
	);

	PlayerInputComponent->BindAction(
		TEXT("Reset"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ResetMagnetic
	);

	PlayerInputComponent->BindAction(
		TEXT("ShootMine"), EInputEvent::IE_Pressed, this, &APlayerCharacter::OnShootMine
	);

	PlayerInputComponent->BindAction(
		TEXT("ShootMine"), EInputEvent::IE_Released, this, &APlayerCharacter::OffShootMine
	);

	PlayerInputComponent->BindAction(
		TEXT("Shoot_N"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ShootMagnetic_N
	);

	PlayerInputComponent->BindAction(
		TEXT("Shoot_S"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ShootMagnetic_S
	);

	#pragma endregion
}


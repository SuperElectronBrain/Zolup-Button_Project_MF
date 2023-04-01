// Fill out your copyright notice in the Description page of Project Settings.


#include "MagneticComponent.h"
#include "Components/SceneComponent.h"
#include <GameFramework/FloatingPawnMovement.h>
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Kismet/GameplayStatics.h"
#include "MagneticMovementComponent.h"

UMagneticComponent::UMagneticComponent()
{
	#pragma region Summary
	PrimaryComponentTick.bCanEverTick = true;
	CurrMagnetic = EMagneticType::NONE;
	EternalHaveMagnetic = false;
	_RotCounter = FMath::DegreesToRadians(360.f / MAGNETIC_FIELD_PRECISION);
	_applyRadius = _goalRadius = 0.f;
	bShowMagneticField = true;
	bCanChangeMagnetic = true;
	MaxHaveMagneticSeconds = 20.f;
	CurrHaveMagneticSeconds = 0.f;
	MagneticFieldRadius = 5.f;
	FinalMagneticFieldRadius = 0.f;
	_applyMovement = false;
	_bUsedFixedWeight = false;
	_blastUsedGravity = false;

	/*CDO*/
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FIELD_MESH(
		TEXT("/Engine/BasicShapes/Cylinder.Cylinder")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> INTERFACE(
		TEXT("/Game/Resource/Effects/Glow.glow")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FIELD(
		TEXT("/Game/Resource/Magnetic/NewMaterial.NewMaterial")
	);

	/*FieldSpline*/
	FieldSpline = CreateDefaultSubobject<USplineComponent>(TEXT("FIELD_SPLINE"));
	FieldSpline->SetupAttachment(this);
	FieldSpline->ClearSplinePoints(true);
	FieldSpline->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/*FieldCollision*/
	FieldCollision = CreateDefaultSubobject<USphereComponent>(TEXT("FIELD_COLLISION"));
	FieldCollision->SetupAttachment(this);
	FieldCollision->SetSphereRadius(0.f);
	FieldCollision->SetGenerateOverlapEvents(true);
	FieldCollision->SetCollisionObjectType(MAGNETIC_COLLISION_OBJECTTYPE);
	FieldCollision->SetCollisionProfileName(TEXT(MAGNETIC_COLLISION_PROFILE));
	FieldCollision->SetVisibility(true, true);

	/*Meshes*/
	if (FIELD_MESH.Succeeded()) MagneticFieldMesh = FIELD_MESH.Object;
	if (FIELD.Succeeded()) MagneticFieldMaterial = FIELD.Object;
	if (INTERFACE.Succeeded()) MagneticApplyMaterial = INTERFACE.Object;
	#pragma endregion
}

void UMagneticComponent::SetEternalHaveMagnetic(bool value)
{
	EternalHaveMagnetic = value;
}

void UMagneticComponent::AddNoActiveMovement(UMovementComponent* element)
{
	if (element == nullptr || !::IsValid(element) || _NoActiveMovements.Contains(element))
		return;

	_NoActiveMovements.Add(element);
}
void UMagneticComponent::RemoveNoActiveMovmeent(UMovementComponent* element)
{
	if (element == nullptr || !::IsValid(element) || !_NoActiveMovements.Contains(element))
		return;

	_NoActiveMovements.Remove(element);
}

bool UMagneticComponent::CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const
{
	return true;
}

void UMagneticComponent::SettingMagnetWeightAndFieldRange()
{

	if (!_bUsedFixedWeight)
	{
		if (GetAttachParent() != nullptr)
		{
			const FBox& Box = GetAttachParent()->Bounds.GetBox();
			Weight = (Box.Max - Box.Min).Size();
		}
	}

	FinalMagneticFieldRadius = Weight * MagneticFieldRadius;
	FieldCollision->SetSphereRadius(FinalMagneticFieldRadius);
}

void UMagneticComponent::SetParentMaterials(EMagneticType type)
{
	FVector color = GetMagneticColorVector(type);
	UMeshComponent* mesh = Cast<UMeshComponent>(GetAttachParent());

	if (mesh!=nullptr && ::IsValid(mesh))
	{
		//parent의 자석이 보관이 안되어있다면 보관.
		if (_parentOriMaterial == nullptr)
		{
			UMaterialInterface* temp = mesh->GetMaterial(0);
			if (temp)
			{
				_parentOriMaterial = temp;
			}
		}

		//자성이 부여되었을 때,
		if (type!=EMagneticType::NONE)
		{
			mesh->SetMaterial(0, MagneticApplyMaterial);
			mesh->SetVectorParameterValueOnMaterials(TEXT("emissivecolor"), color);
			return;
		}

		//자성이 해제되었을 때,
		mesh->SetMaterial(0, _parentOriMaterial);
		_parentOriMaterial = nullptr;
	}
}

void UMagneticComponent::OnRegister()
{
	Super::OnRegister();

	SettingMagnetWeightAndFieldRange();
}

void UMagneticComponent::SetMagneticFieldRadius(float newValue)
{
	if (newValue < 0.f) return;

	MagneticFieldRadius = newValue;
	SettingMagnetWeightAndFieldRange();
}

#if WITH_EDITOR
void UMagneticComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	#pragma region Summary
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FString& changed = PropertyChangedEvent.GetPropertyName().ToString();

	if (changed == "MagneticFieldRadius")
	{
		SettingMagnetWeightAndFieldRange();
	}
	else if (changed == "bShowMagneticField")
	{
		SettingMagnetWeightAndFieldRange();
	}
	else if (changed=="CurrMagnetic")
	{
		EMagneticType temp = CurrMagnetic;
		CurrMagnetic = EMagneticType::NONE;
		SetCurrentMagnetic(temp);
	}
	#pragma endregion
}
#endif

FLinearColor UMagneticComponent::GetMagneticLinearColor(EMagneticType type)
{
	#pragma region Summary
	FLinearColor result;

	switch (type) {

	case(EMagneticType::S):
		result.R = 0.f;
		result.G = 0.f;
		result.B = 1.f;
		result.A = 1.f;
		break;

	case(EMagneticType::N):
		result.R = 1.f;
		result.G = 0.f;
		result.B = 0.f;
		result.A = 1.f;
		break;

	default:
		result.R = 1.f;
		result.G = 1.f;
		result.B = 1.f;
		result.A = 1.f;
	}

	return result;
	#pragma endregion
}

FColor UMagneticComponent::GetMagneticColor(EMagneticType type)
{
	#pragma region Summary
	FColor result;

	switch (type) {

	case(EMagneticType::S):
		result.R = 0;
		result.G = 0;
		result.B = 255;
		result.A = 255;
		break;

	case(EMagneticType::N):
		result.R = 255;
		result.G = 0;
		result.B = 0;
		result.A = 255;
		break;

	default:
		result.R = 255;
		result.G = 255;
		result.B = 255;
		result.A = 255;
	}

	return result;
	#pragma endregion
}

FVector UMagneticComponent::GetMagneticColorVector(EMagneticType type)
{
	#pragma region Summary
	FVector result;

	switch (type) {

	case(EMagneticType::S):
		result.X = 0.f;
		result.Y = 0.f;
		result.Z = 1.f;
		break;

	case(EMagneticType::N):
		result.X = 1.f;
		result.Y = 0.f;
		result.Z = 0.f;
		break;

	default:
		result.X = 1.f;
		result.Y = 1.f;
		result.Z = 1.f;
	}

	return result;
#pragma endregion
}

// Called when the game starts
void UMagneticComponent::BeginPlay()
{
	Super::BeginPlay();

	//물리가 적용되어 있다면 그에 대한 설정을 한다.
	_parent = Cast<UPrimitiveComponent>(GetAttachParent());
	if (_parent && ::IsValid(_parent))
	{
		if(_bUsedFixedWeight == false) _parent->SetMassOverrideInKg(NAME_None, 10000.f);
		_blastUsedGravity = _parent->IsGravityEnabled();
	}

	SettingMagnetWeightAndFieldRange();
}

void UMagneticComponent::DestroyComponent(bool bPromoteChilderen)
{
	Super::DestroyComponent(bPromoteChilderen);

	if (FieldSpline)
	{
		FieldSpline->DestroyComponent();
	}

	if (FieldCollision)
	{
		FieldCollision->DestroyComponent();
	}
}

void UMagneticComponent::SetCurrentMagnetic(EMagneticType newType)
{
	#pragma region Summary
	if (!bCanChangeMagnetic) return;

	//현재 붙어있는 MagneticMovementComponent를 가져온다.
	if (_movement==nullptr || ( _movement!=nullptr&& !::IsValid(_movement)) )
	{
		_movement = GetOwner()->FindComponentByClass<UMagneticMovementComponent>();

		if (_movement)
		{
			_movement->SetUpdatedComponent(GetOwner()->GetRootComponent());
		}
	}

	//같은 극이 부여되면 자성을 잃게 된다.
	if (newType==CurrMagnetic)
	{
		CurrMagnetic = EMagneticType::NONE;
	}
	else CurrMagnetic = newType;

	//자성 변화에 대한 변화
	if (CurrMagnetic == EMagneticType::NONE)
	{
		CurrHaveMagneticSeconds = 0.f;
		_goalRadius = 0.f;
		if (_parent && _parent->IsSimulatingPhysics()) _parent->SetEnableGravity(_blastUsedGravity);

		//만약 이동중에 자성이 변경되었다면, 이동이 끝임을 수신하고 무시했던 MovementComponent들을 활성화시킨다.
		if (_movement && _applyMovement)
		{
			MagnetMoveEndEvent.Broadcast(_lastMoveType);
			SetNoActiveMovementsActive(true);
			_lastMoveType = EMagnetMoveType::NONE;
			_applyMovement = false;
		}

		OffMagneticEvent.Broadcast(newType);
	}
	else
	{
		CurrHaveMagneticSeconds = MaxHaveMagneticSeconds;
		_applyRadius = 0.1f;
		ClearMagneticField();
		FieldCollision->SetSphereRadius(Weight*MagneticFieldRadius);
		_goalRadius = FieldCollision->GetScaledSphereRadius();
		_fieldColor = GetMagneticColorVector(newType);
		OnMagneticEvent.Broadcast(newType);
	}

	SetParentMaterials(CurrMagnetic);
	#pragma endregion
}

void UMagneticComponent::UpdateMagneticField()
{
	#pragma region Summary

	FieldSpline->ClearSplinePoints(true);

	//원이 되도록 회전.
	if(GetAttachParent() == nullptr)
	{
		return;
	}
	FVector size = GetAttachParent()->GetComponentScale();
	float rot = .0f;
	FVector mov;

	//라인을 먼저 그린다.
	FVector center = FieldCollision->GetComponentLocation();
	for (int32 i = 0; i <= MAGNETIC_FIELD_PRECISION; i++)
	{
		FVector point(	FMath::Cos(rot) * _applyRadius,
						FMath::Sin(rot) * _applyRadius, .0f );

		rot += _RotCounter;

		FieldSpline->AddSplinePointAtIndex(center + point, i, ESplineCoordinateSpace::World);
	}

	int32 count = FieldSpline->GetNumberOfSplinePoints() - 1;

	//현재 처음으로 적용되는 것이라면 SplineMeshComponent를 생성.
	int32 FieldMeshCount = FieldMeshs.Num();
	FVector color = GetMagneticColorVector(CurrMagnetic);
	if (FieldMeshCount ==0)
	{
		//필요한 Mesh들을 생성.
		for (int32 i = 0; i < count; i++)
		{
			USplineMeshComponent* splineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
			splineMeshComponent->SetStaticMesh(MagneticFieldMesh);
			splineMeshComponent->SetCastShadow(false);
			splineMeshComponent->SetCastInsetShadow(false);
			splineMeshComponent->SetForwardAxis(ESplineMeshAxis::Z);
			splineMeshComponent->SetMobility(EComponentMobility::Movable);
			splineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			splineMeshComponent->RegisterComponentWithWorld(GetWorld());
			splineMeshComponent->AttachToComponent(FieldSpline, FAttachmentTransformRules::KeepRelativeTransform);
			splineMeshComponent->SetStartScale(FVector2D(UKismetSystemLibrary::MakeLiteralFloat(.07f), UKismetSystemLibrary::MakeLiteralFloat(.07f)));
			splineMeshComponent->SetEndScale(FVector2D(UKismetSystemLibrary::MakeLiteralFloat(.07f), UKismetSystemLibrary::MakeLiteralFloat(.07f)));
			splineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			//머터리얼 적용
			if (MagneticFieldMaterial)
			{
				splineMeshComponent->SetMaterial(0, MagneticFieldMaterial);
				splineMeshComponent->SetVectorParameterValueOnMaterials(TEXT("color"), color);
			}
			FieldMeshs.Add(splineMeshComponent);
		}
	}

	//그려져 있는 라인에 따라서 메시를 연결시킨다.
	FieldMeshCount = FieldMeshs.Num();
	for (int32 i=0; i<count && i<FieldMeshCount ; i++)
	{
		if (i>=FieldMeshCount || FieldMeshs[i]==nullptr || !::IsValid(FieldMeshs[i])) break;
		const FVector startPoint = FieldSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FVector startTangent = FieldSpline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FVector endPoint = FieldSpline->GetLocationAtSplinePoint(i+1, ESplineCoordinateSpace::Local);
		const FVector endTangent = FieldSpline->GetTangentAtSplinePoint(i+1, ESplineCoordinateSpace::Local);
		FieldMeshs[i]->SetStartAndEnd(startPoint, startTangent, endPoint, endTangent, true);
	}
	#pragma endregion
}

void UMagneticComponent::ClearMagneticField()
{
	#pragma region Summary
	FieldSpline->ClearSplinePoints(true);

	if (FieldMeshs.Num() > 0)
	{
		int32 count = FieldMeshs.Num();
		for (int32 i = 0; i < count; i++) {

			if (FieldMeshs[i])
			{
				//부모로부터 분리 후, 삭제
				FieldMeshs[i]->DestroyComponent();
			}
		}

		//초기화.
		FieldMeshs.Empty();
	}
	#pragma endregion
}

void UMagneticComponent::SetNoActiveMovementsActive(bool value)
{
	int predictCount = _NoActiveMovements.Num();
	if (_NoActiveMovements.Num() > 0)
	{
		for (int32 i = 0; i < predictCount; i++)
		{
			//유효하지 않은 무브먼트라면 제거하고 넘어간다.
			if (_NoActiveMovements[i] == nullptr || !::IsValid(_NoActiveMovements[i])) {
				_NoActiveMovements.RemoveAt(i--);
				continue;
			}

			_NoActiveMovements[i]->SetActive(value);
		}
	}
}

// Called every frame
void UMagneticComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	#pragma region Summary
	//자성을 유지할 수 있는 시간이 넘으면 자성을 잃게 된다.
	if (!EternalHaveMagnetic && CurrMagnetic != EMagneticType::NONE && CurrHaveMagneticSeconds > 0.f)
	{
		CurrHaveMagneticSeconds -= DeltaTime;
		if (CurrHaveMagneticSeconds<=0.f)
		{
			CurrHaveMagneticSeconds = 0.f;
			_goalRadius = 0.f;
			SetCurrentMagnetic(EMagneticType::NONE);
		}
	}

	//자기장 애니메이션
	if (bShowMagneticField && _applyRadius>0.f)	{
		_applyRadius = _applyRadius + .1f * (_goalRadius- _applyRadius);

		if (CurrMagnetic == EMagneticType::NONE && _applyRadius<=0.09f )
		{
			_applyRadius = 0.f;
			ClearMagneticField();
		}
		else UpdateMagneticField();
	}

	//자성이 부여되어 있지 않고, 부착된 MagneticMovement 컴포넌트가 없다면 움직일 이유가 없으니 스킵.
	if (CurrMagnetic == EMagneticType::NONE || _movement==nullptr || _movement!=nullptr&&!::IsValid(_movement))
	{
		return;
	}

	//또한 CollisionProfile의 지정으로, MagneticField를 가지는 컴포넌트만 충돌을 발생시키기에 동일 클래스의 USphereComponent만 충돌판정을 한다.
	//현재 자기장 범위와 겹쳐있는 자기장을 가진 자석들에 대해서 영향을 받는다.
	TArray<UPrimitiveComponent*> overlapList;
	float maxWeight = 0.f;
	bool applyLogic = false;
	AActor* finalHit = nullptr;
	FieldCollision->GetOverlappingComponents(overlapList);

	for (auto p : overlapList)
	{
		//해당 자석과 부착된 엑터가 같거나, USphereComponent가 아닐 경우 스킵.
		if (p->GetOwner() == GetOwner() || p->GetClass() != USphereComponent::StaticClass()) continue;
		UMagneticComponent* magnet = Cast<UMagneticComponent>(p->GetAttachParent());

		//만약 MagneticComponent가 유효하지 않거나, 유효한데 자석이 없다면 스킵.
		if (magnet == nullptr || !::IsValid(magnet) || magnet->CurrMagnetic == EMagneticType::NONE) 
				continue;

		//해당 자석의 무게가 더 크다면 자석 이동 로직을 적용한다.
		if (magnet->Weight <= Weight) continue;

		//이동할 타입을 결정하고, 처음 이동을 시작하는 것이라면 아래의 로직을 적용.
		EMagnetMoveType moveType = (magnet->CurrMagnetic == CurrMagnetic ? EMagnetMoveType::PUSHED_OUT : EMagnetMoveType::DRAWN_IN);
		if (_applyMovement == false || _lastMoveType!=moveType)
		{
			MagnetMoveStartEvent.Broadcast(moveType);
			_movement->StartMovement(moveType);
			SetNoActiveMovementsActive(moveType==EMagnetMoveType::PUSHED_OUT?true:false);
		}
		_applyMovement = true;
		applyLogic = true;

		//부딫힌 것이 자석이라면
		AActor* hit = _movement->ApplyUpdatedComponentMovement(moveType, this, magnet, DeltaTime);
		if (hit==magnet->GetOwner())
		{
			finalHit = hit;
		}

		if (maxWeight<magnet->Weight)
		{
			maxWeight = magnet->Weight;
			_lastMoveType = moveType;
		}
	}

	//더 이상의 자성 움직임이 없을 경우, 그에 대한 로직 처리.
	if (applyLogic==false && _applyMovement)
	{
		_applyMovement = false;
		_movement->EndMovement(_lastMoveType);
		_lastMoveType = EMagnetMoveType::NONE;
		MagnetMoveEndEvent.Broadcast(_lastMoveType);
		SetNoActiveMovementsActive(true);

		if (_parent && _parent->IsSimulatingPhysics()) _parent->SetEnableGravity(_blastUsedGravity);
		return;
	}
	else if (applyLogic && finalHit!=nullptr && ::IsValid(finalHit))
	{
		MagnetMoveHitEvent.Broadcast(finalHit);
	}
	#pragma endregion
}


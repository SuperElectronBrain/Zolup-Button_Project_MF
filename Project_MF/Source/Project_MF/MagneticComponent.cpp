// Fill out your copyright notice in the Description page of Project Settings.


#include "MagneticComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "MagneticMovementComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"

UMagneticComponent::UMagneticComponent()
{
	#pragma region Summary
	PrimaryComponentTick.bCanEverTick = true;
	CurrMagnetic = EMagneticType::NONE;
	EternalHaveMagnetic = false;
	_RotCounter = FMath::DegreesToRadians(360.f / MAGNETIC_FIELD_PRECISION);
	_applyRadius = _goalRadius = 0.f;
	bShowMagneticField = true;
	MagneticFieldRadiusScale = 5.f;
	bCanChangeMagnetic = true;
	MaxHaveMagneticSeconds = 20.f;
	CurrHaveMagneticSeconds = 0.f;
	FinalMagneticFieldRadius = 0.f;
	_applyMovement = false;
	bUsedFixedWeight = false;
	_blastUsedGravity = false;
	RGB = FColor::White;
	MaxEnchantableCount = 0;
	CurrEnchantCount = 0;
	_parent = nullptr;
	_parentMesh = nullptr;
	_material = nullptr;
	bAllowMagneticMovement = true;
	bMagneticMaterialApplyAttachMesh = true;
	_currMagMaterialApplyRatio =  _goalMagMaterialApplyRatio = 1.f;

	/*CDO*/
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FIELD_MESH(
		TEXT("/Engine/BasicShapes/Cylinder.Cylinder")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> INTERFACE(
		TEXT("/Game/Effect/Magnetic/Magnet_glow_ver3.Magnet_glow_ver3")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FIELD(
		TEXT("/Game/Resource/Magnetic/NewMaterial.NewMaterial")
	);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FIELD_EFFECT(
		TEXT("/Game/Effect/Magnetic/Ring/Magnet_ring_n.Magnet_ring_n")
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
	FieldCollision->ShapeColor = FColor::Magenta;

	/*Meshes or Materials*/
	if (FIELD_MESH.Succeeded()) MagneticFieldMesh = FIELD_MESH.Object;
	if (FIELD.Succeeded()) MagneticFieldMaterial = FIELD.Object;
	if (INTERFACE.Succeeded()) MagneticApplyMaterial = INTERFACE.Object;
	if (FIELD_EFFECT.Succeeded()) MagneticFieldEffect = FIELD_EFFECT.Object;
	#pragma endregion
}

void UMagneticComponent::InitParentAndMaterial()
{
	bool parentMeshValid = _parentMesh && ::IsValid(_parentMesh);

	//parent의 MeshComponent 캐싱.
	if (parentMeshValid==false || _parentMesh != GetAttachParent())
	{
		if (parentMeshValid) _parentMesh->SetMaterial(0, nullptr);
		_parentMesh = Cast<UMeshComponent>(GetAttachParent());
	}

	//머터리얼이 없다면 생성.
	if (_material == nullptr)
	{
		_material = UMaterialInstanceDynamic::Create(MagneticApplyMaterial, this);
	}

	//머터리얼의 기본값을 세팅 및 parentMesh에게 적용.
	if (bMagneticMaterialApplyAttachMesh && _parentMesh && ::IsValid(_parentMesh) && _material)
	{
		if (_material) _material->SetTextureParameterValue(TEXT("DefaultTex"), Texture);
		_material->SetVectorParameterValue(TEXT("DefaultColor"), FVector(RGB.R, RGB.G, RGB.B));
		_material->SetVectorParameterValue(TEXT("Emissivecolor"), GetMagneticColorVector(EMagneticType::NONE));
		_material->SetVectorParameterValue(TEXT("base"), GetMagneticColorVector(EMagneticType::NONE));
		_material->SetScalarParameterValue(TEXT("applyRatio"), 1.f);
		if (_parentMesh->GetMaterial(0) != _material) _parentMesh->SetMaterial(0, _material);
	}

	//Parent의 PrimitiveComponent 캐싱.
	if (_parent == nullptr || _parent != GetAttachParent())
		_parent = Cast<UPrimitiveComponent>(GetAttachParent());
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

bool UMagneticComponent::CanAttachAsChild(const USceneComponent* ChildComponent, FName SocketName) const
{
	return (ChildComponent == FieldCollision || ChildComponent == FieldSpline);
}

void UMagneticComponent::SettingMagnetWeightAndFieldRange()
{
	if (!bUsedFixedWeight)
	{
		if (_parent && ::IsValid(_parent))
		{
			const FBox& Box = GetAttachParent()->Bounds.GetBox();
			Weight = (Box.Max - Box.Min).Size() + (CurrEnchantCount * EnchantWeight);
		}
		else Weight = 0.f;
	}

	if (FieldCollision && ::IsValid(FieldCollision) && FieldCollision->GetAttachParent()==this)
	{
		FieldCollision->SetSphereRadius(Weight * MagneticFieldRadiusScale + (CurrEnchantCount * EnchantRange));
		_goalRadius = FinalMagneticFieldRadius = FieldCollision->GetScaledSphereRadius();
	}

	//Weight = 0;
	//FieldCollision->SetSphereRadius(0.f);
	//_goalRadius = FinalMagneticFieldRadius = 0.f;
}

void UMagneticComponent::SetParentMaterial(EMagneticType type)
{
	FVector color = GetMagneticColorVector(type);

	if (_material != nullptr && ::IsValid(_material))
	{
		_material->SetVectorParameterValue(TEXT("Emissivecolor"), color);
		_material->SetVectorParameterValue(TEXT("base"), color);
		_goalMagMaterialApplyRatio = type == EMagneticType::NONE ? 1.f : 0.f;
	}
}

void UMagneticComponent::OnAttachmentChanged()
{
	Super::OnAttachmentChanged();

	USceneComponent* parent = GetAttachParent();

	if (parent)
	{
		SetRelativeLocation(FVector::ZeroVector);
		InitParentAndMaterial();
		SettingMagnetWeightAndFieldRange();
	}
}

void UMagneticComponent::SetMagneticFieldRadius(float newValue)
{
	if (newValue < 0.f) return;

	MagneticFieldRadiusScale = newValue;
	SettingMagnetWeightAndFieldRange();
}

#if WITH_EDITOR
void UMagneticComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	#pragma region Summary
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FString& changed = PropertyChangedEvent.GetPropertyName().ToString();

	if (changed == "MagneticFieldRadius" || changed == "MagneticFieldRadiusScale")
	{
		SettingMagnetWeightAndFieldRange();
	}
	else if (changed == "bShowMagneticField")
	{
		SettingMagnetWeightAndFieldRange();
	}
	else if (changed == "CurrMagnetic")
	{
		EMagneticType temp = CurrMagnetic;
		CurrMagnetic = EMagneticType::NONE;
		SetCurrentMagnetic(temp);
	}
	else if (changed == "RGB" || changed == "Texture" || changed=="R" || changed=="G" || changed=="B")
	{
		InitParentAndMaterial();
	}
	else if (changed == "bShowMagneticFieldSphereInGame")
	{
		FieldCollision->SetHiddenInGame(!bShowMagneticFieldSphereInGame);
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
		result.Z = 15.f;
		break;

	case(EMagneticType::N):
		result.X = 15.f;
		result.Y = 0.f;
		result.Z = 0.f;
		break;

	default:
		result.X = 0.f;
		result.Y = 0.f;
		result.Z = 0.f;
	}

	return result;
	#pragma endregion
}

// Called when the game starts
void UMagneticComponent::BeginPlay()
{
	Super::BeginPlay();

	/*부착된 부모 컴포넌트 및 다이나믹 머터리얼을 초기화.*/
	InitParentAndMaterial();

	/*물리가 적용되어 있다면 그에 대한 설정을 한다.*/
	if (_parent && ::IsValid(_parent))
	{
		_blastUsedGravity = _parent->IsGravityEnabled();
		_parent->SetMobility(EComponentMobility::Movable);
		GetAttachmentRoot()->SetMobility(EComponentMobility::Movable);
		//if (_bUsedFixedWeight == false) _parent->SetMassOverrideInKg(NAME_None, 10000.f);
	}

	/*무게 및 자기장 크기 초기화*/
	SettingMagnetWeightAndFieldRange();

	if (CurrMagnetic!=EMagneticType::NONE)
	{
		EMagneticType type = CurrMagnetic;
		CurrMagnetic = EMagneticType::NONE;
		SetCurrentMagnetic(type);
	}

	/*자성 필드 컴포넌트가 생성되어있지 않다면 생성한다.*/
	if (MagneticFieldEffectComp == nullptr && MagneticFieldEffect)
	{
		MagneticFieldEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			MagneticFieldEffect,
			this,
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			false,
			false
		);
	}
}

void UMagneticComponent::DestroyComponent(bool bPromoteChilderen)
{
	Super::DestroyComponent(bPromoteChilderen);

	if (_parentMesh && ::IsValid(_parentMesh))
	{
		_parentMesh->SetMaterial(0, nullptr);
	}

	if (FieldSpline)
	{
		FieldSpline->DestroyComponent();
	}

	if (FieldCollision)
	{
		FieldCollision->DestroyComponent();
	}
}

void UMagneticComponent::SetEnchantInfo(int32 maxEnchantCount, float enchantWeight, float enchantRange)
{
	if (maxEnchantCount < 0) return;

	MaxEnchantableCount = maxEnchantCount;
	if (enchantWeight >= 0.f) EnchantWeight = enchantWeight;
	if (enchantRange >= 0.f) EnchantRange = enchantRange;

	//현재 부여된 값이 새롭게 부여된 값보다 크다면...
	if (CurrEnchantCount > MaxEnchantableCount)
	{
		CurrEnchantCount = MaxEnchantableCount;
	}

	SettingMagnetWeightAndFieldRange();

	//자성이 활성화된 상태라면
	if (CurrMagnetic != EMagneticType::NONE)
	{
		_goalRadius = FieldCollision->GetScaledSphereRadius();
	}
}

void UMagneticComponent::SetCurrentMagnetic(EMagneticType newType)
{
	#pragma region Summary
	//자성이 바뀔 수 없으면 스킵하지만, 같은 자성이라면 부여가 가능하도록 한다.
	if (!bCanChangeMagnetic)
	{
		if (CurrMagnetic != newType) return;
	}

	//현재 엑터에 붙어있는 MagneticMovementComponent의 참조를 가져온다.
	if (_movement == nullptr || (_movement != nullptr && !::IsValid(_movement)))
	{
		_movement = GetOwner()->FindComponentByClass<UMagneticMovementComponent>();
		if (_movement)
		{
			_movement->SetUpdatedComponent(GetOwner()->GetRootComponent());
		}
	}

	bool sameMagnetic = CurrMagnetic == newType;
	bool changeMagnetic = CurrMagnetic != newType;
	bool addMagCount = true;

	//자성이 초기화되었을 경우.
	if (newType == EMagneticType::NONE)
	{
		changeMagnetic = true;
		CurrEnchantCount = 0;
		CurrMagnetic = EMagneticType::NONE;
	}
	else if (CurrMagnetic != EMagneticType::NONE && CurrEnchantCount <= MaxEnchantableCount && MaxEnchantableCount > 0)
	{
		//같은 극이 부여되었고, 부여가능횟수를 초과해서 부여했을 경우 0로 초기화.
		if (sameMagnetic && CurrEnchantCount + 1 > MaxEnchantableCount)
		{
			CurrEnchantCount = 0;
			addMagCount = false;
		}
		else if (sameMagnetic == false)
		{
			//다른극이 소유극이 0개일 때 부여되면 자성이 바뀐다.
			if (CurrEnchantCount == 0)
			{
				CurrMagnetic = newType;
				CurrEnchantCount = 0;
				changeMagnetic = true;
				addMagCount = false;
			}
			//다른극이 부여극이 0개 초과일 때 부여되면 자성이 초기화된다.
			else if (CurrEnchantCount > 0)
			{
				CurrEnchantCount = 0;
				CurrMagnetic = EMagneticType::NONE;
				addMagCount = false;
			}
		}

		if (addMagCount) CurrEnchantCount++;
	}
	else
	{
		if (CurrMagnetic == newType)
		{
			CurrMagnetic = EMagneticType::NONE;
		}
		else CurrMagnetic = newType;
	}

	//자성 사라지거나, 부여되었을 때의 변화
	if (CurrMagnetic == EMagneticType::NONE)
	{
		CurrHaveMagneticSeconds = 0.f;
		CurrEnchantCount = 0;
		_goalRadius = 0.f;

		//Simulate physics 적용중이였다면, 중력 적용을 원상복귀 시킨다.
		if (_parent && _parent->IsSimulatingPhysics()) _parent->SetEnableGravity(_blastUsedGravity);

		//만약 이동중에 자성이 변경되었다면, 이동이 끝임을 수신하고 무시했던 MovementComponent들을 활성화.
		if (_movement && _applyMovement)
		{
			MagnetMoveEndEvent.Broadcast(_lastMoveType, this);
			SetNoActiveMovementsActive(true);
			_lastMoveType = EMagnetMoveType::NONE;
			_applyMovement = false;
		}

		OffMagneticEvent.Broadcast(newType, this);
	}
	else
	{
		CurrHaveMagneticSeconds = MaxHaveMagneticSeconds;
		if (changeMagnetic) _applyRadius = .1f;

		SettingMagnetWeightAndFieldRange();

		_fieldColor = GetMagneticColorVector(newType);
		UpdateFieldMeshsColor(newType);
		OnMagneticEvent.Broadcast(newType, this);
	}

	SetParentMaterial(CurrMagnetic);
	#pragma endregion
}

void UMagneticComponent::UpdateFieldMeshsColor(EMagneticType type)
{
	if (FieldMeshs.Num() > 0)
	{
		FVector color = GetMagneticColorVector(type);

		for (auto mesh : FieldMeshs)
		{
			mesh->SetVectorParameterValueOnMaterials(TEXT("color"), color);
		}

	}
}

void UMagneticComponent::UpdateMagneticField()
{
	#pragma region Summary
	if (_parent == nullptr && !::IsValid(_parent))
	{
		return;
	}

	//if (MagneticFieldEffectComp)
	//{
	//	if (MagneticFieldEffectComp->IsActive() == false) MagneticFieldEffectComp->ActivateSystem(true);
	//	MagneticFieldEffectComp->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	//}

	//return;

	FieldSpline->ClearSplinePoints(true);

	//원이 되도록 회전.
	FVector size = GetAttachParent()->GetComponentScale();
	float rot = .0f;
	FVector mov;

	//라인을 먼저 그린다.
	FVector center = FieldCollision->GetComponentLocation();
	for (int32 i = 0; i <= MAGNETIC_FIELD_PRECISION; i++)
	{
		FVector point(FMath::Cos(rot) * _applyRadius,
			FMath::Sin(rot) * _applyRadius, .0f);

		rot += _RotCounter;

		FieldSpline->AddSplinePointAtIndex(center + point, i, ESplineCoordinateSpace::World);
	}

	int32 count = FieldSpline->GetNumberOfSplinePoints() - 1;

	//현재 처음으로 적용되는 것이라면 SplineMeshComponent를 생성.
	int32 FieldMeshCount = FieldMeshs.Num();
	FVector color = GetMagneticColorVector(CurrMagnetic);
	if (FieldMeshCount == 0)
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
	for (int32 i = 0; i < count && i < FieldMeshCount; i++)
	{
		if (i >= FieldMeshCount || FieldMeshs[i] == nullptr || !::IsValid(FieldMeshs[i])) break;
		const FVector startPoint = FieldSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FVector startTangent = FieldSpline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FVector endPoint = FieldSpline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		const FVector endTangent = FieldSpline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
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
		if (CurrHaveMagneticSeconds <= 0.f)
		{
			CurrHaveMagneticSeconds = 0.f;
			_goalRadius = 0.f;
			SetCurrentMagnetic(EMagneticType::NONE);
		}
	}

	//자기장 애니메이션
	if (bShowMagneticField && _applyRadius > 0.f) {
		_applyRadius = _applyRadius + .03f * (_goalRadius - _applyRadius);

		if (CurrMagnetic == EMagneticType::NONE && _applyRadius <= 0.09f)
		{
			_applyRadius = 0.f;
			ClearMagneticField();
		}
		else UpdateMagneticField();
	}

	//자성 머터리얼 자연스러운 적용
	if (_material && _currMagMaterialApplyRatio!=_goalMagMaterialApplyRatio)
	{
		//greater
		if (_goalMagMaterialApplyRatio>_currMagMaterialApplyRatio)
		{
			_currMagMaterialApplyRatio +=  DeltaTime;

			if (_currMagMaterialApplyRatio >= _goalMagMaterialApplyRatio)
				_currMagMaterialApplyRatio = _goalMagMaterialApplyRatio;
		}
		//less
		else if (_goalMagMaterialApplyRatio < _currMagMaterialApplyRatio)
		{
			_currMagMaterialApplyRatio -= DeltaTime;

			if (_currMagMaterialApplyRatio <= _goalMagMaterialApplyRatio)
				_currMagMaterialApplyRatio = _goalMagMaterialApplyRatio;
		}

		_material->SetScalarParameterValue(TEXT("applyRatio"), _currMagMaterialApplyRatio);
	}

	//자성이 부여되어 있지 않고, 부착된 MagneticMovement 컴포넌트가 없다면 움직일 이유가 없으니 스킵.
	if (bAllowMagneticMovement == false || CurrMagnetic == EMagneticType::NONE || _movement == nullptr || _movement != nullptr && !::IsValid(_movement))
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
		if (_applyMovement == false || _lastMoveType != moveType)
		{
			MagnetMoveStartEvent.Broadcast(moveType, magnet);
			_movement->StartMovement(moveType, this, magnet);
			SetNoActiveMovementsActive(moveType == EMagnetMoveType::PUSHED_OUT ? true : false);
		}
		_applyMovement = true;
		applyLogic = true;
		CurrHaveMagneticSeconds = MaxHaveMagneticSeconds;

		//부딫힌 것이 자석이라면
		AActor* hit = _movement->ApplyUpdatedComponentMovement(moveType, this, magnet, DeltaTime);
		if (hit == magnet->GetOwner())
		{
			finalHit = hit;
		}

		if (maxWeight < magnet->Weight)
		{
			maxWeight = magnet->Weight;
			_lastMoveType = moveType;
		}
	}

	//더 이상의 자성 움직임이 없을 경우, 그에 대한 로직 처리.
	if (applyLogic == false && _applyMovement)
	{
		_applyMovement = false;
		_movement->EndMovement(_lastMoveType, this);
		_lastMoveType = EMagnetMoveType::NONE;
		MagnetMoveEndEvent.Broadcast(_lastMoveType, this);
		SetNoActiveMovementsActive(true);

		if (_parent && _parent->IsSimulatingPhysics()) _parent->SetEnableGravity(_blastUsedGravity);
		return;
	}
	else if (applyLogic && finalHit != nullptr && ::IsValid(finalHit))
	{
		MagnetMoveHitEvent.Broadcast(finalHit, this);
	}
	#pragma endregion
}

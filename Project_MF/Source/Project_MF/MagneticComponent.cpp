#include "MagneticComponent.h"
#include "MagneticMovementComponent.h"
#include "MagneticFieldEffectComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"

UMagneticComponent::UMagneticComponent()
{
	#pragma region Summary
	PrimaryComponentTick.bCanEverTick = true;
	_lastMoveType = EMagnetMoveType::NONE;

	/*****************************************************
	* CDO( Material + Effect )
	* 이 컴포넌트에서 사용할 자성부여 머터리얼과 자기장 이펙트를 가져옵니다.
	*****************************************************/
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GRANT_MATERIAL(
		TEXT("/Game/Effect/Magnetic/Glow/Glow_ver5.Glow_ver7")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FIELD_SCOPE_MATERIAL(
		TEXT("/Game/Effect/Magnetic/Field/magnet_scope_m.magnet_scope_m")
	);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FIELD_EFFECT(
		TEXT("/Game/Effect/Magnetic/Field/magnet_scope_grow_big_nia.magnet_scope_grow_big_nia")
	);

	if (GRANT_MATERIAL.Succeeded()) MagneticApplyMaterial = GRANT_MATERIAL.Object;
	if (FIELD_SCOPE_MATERIAL.Succeeded()) FieldScopeMaterial = FIELD_SCOPE_MATERIAL.Object;


	/**********************************************************
	* Component( Sphere )
	* 자기장 역할을 할 구체 컴포넌트를 초기화합니다.
	**********************************************************/
	FieldCollision = CreateDefaultSubobject<USphereComponent>(TEXT("FIELD_COLLISION"));
	FieldCollision->SetupAttachment(this);
	FieldCollision->SetSphereRadius(0.f);
	FieldCollision->SetGenerateOverlapEvents(true);
	FieldCollision->SetCollisionObjectType(MAGNETIC_COLLISION_OBJECTTYPE);
	FieldCollision->SetCollisionProfileName(MAGNETIC_COLLISION_PROFILE);
	FieldCollision->SetVisibility(true, true);
	FieldCollision->ShapeColor = FColor::Magenta;
	

	/************************************************************
	* Component( MagneticFieldEffect )
	* 자기장 이펙트 컴포넌트를 초기화합니다.
	*************************************************************/
	FieldEffectComp = CreateDefaultSubobject<UMagneticFieldEffectComponent>(TEXT("FIELD_EFFECT"));
	FieldEffectComp->SetUsingAbsoluteScale(true);
	FieldEffectComp->SetupAttachment(FieldCollision);

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
	
	if (_parentMesh && MagneticApplyMaterial)
	{
		//머터리얼이 없다면 생성한다.
		if (_material == nullptr)
			_material = UMaterialInstanceDynamic::Create(MagneticApplyMaterial, this);

		//머터리얼이 생성되어 있을 경우
		if (_material)
		{
			//메시에 적용이 안되어 있다면 적용한다.
			if (_parentMesh->GetMaterial(0) != _material)
				_parentMesh->SetMaterial(0, _material);

			//기본값을 세팅한다.
			_material->SetVectorParameterValue(TEXT("Emissivecolor"),FVector(GetMagneticEffectColor(EMagneticType::NONE, EMagneticEffectColorType::GRANT_EFFECT)));
			_material->SetScalarParameterValue(TEXT("glow_alpha"), 0.f);
		}
	}

	
	//Parent의 PrimitiveComponent 캐싱.
	if (_parent == nullptr || _parent != GetAttachParent())
		_parent = Cast<UPrimitiveComponent>(GetAttachParent());
}

bool UMagneticComponent::CanAttachAsChild(const USceneComponent* ChildComponent, FName SocketName) const
{
	return true;
	return (ChildComponent == FieldCollision || ChildComponent == FieldEffectComp);
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
		FinalMagneticFieldRadius = FieldCollision->GetScaledSphereRadius();
		_magActivate = false;
	}
}

void UMagneticComponent::SetParentMaterial(EMagneticType type)
{
	if (_material == nullptr) return;
	bool isN			= type == EMagneticType::N;
	FVector color		= (isN ? FVector(5.f, 0.f, 0.049996f) : FVector(0.014019f, 0.f, 70.f));
	float surface_alpha = (isN ? 0.07f : 5.f);

	if (_material != nullptr && ::IsValid(_material) && type!=EMagneticType::NONE)
	{
		_material->SetVectorParameterValue(TEXT("EmissiveColor"), color);
		_material->SetScalarParameterValue(TEXT("surface_alpha"), surface_alpha);
	}

	_goalMagMaterialApplyRatio  =  type==EMagneticType::NONE ? 0.f : 1.f;
}

void UMagneticComponent::SetWeight(float value, bool usedFixedWeight) 
{ 
	if (value > 0.f) 
	{ 
		Weight = value; 
		bUsedFixedWeight = usedFixedWeight; 
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

void UMagneticComponent::SetMagneticFieldRadiusScale(float newValue)
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
	else if (changed=="MagneticApplyMaterial")
	{
		if (_parentMesh)
			_parentMesh->SetMaterial(0, nullptr);

		_material->MarkAsGarbage();
		_material = nullptr;

		InitParentAndMaterial();
	}
	else if (changed == "RGB" || changed == "Texture" || changed=="R" || changed=="G" || changed=="B")
	{
		InitParentAndMaterial();
	}
	else if (changed == "bShowMagneticFieldSphereInGame")
	{
		FieldCollision->SetHiddenInGame(!bShowMagneticFieldSphereInGame);
	}
	else if (changed=="bMagneticMaterialApplyAttachMesh" && _parentMesh)
	{
		if (bMagneticMaterialApplyAttachMesh==false)
		{
			_parentMesh->SetMaterial(0, nullptr);
		}
		else _parentMesh->SetMaterial(0, _material);
	}
	#pragma endregion
}
#endif

FLinearColor UMagneticComponent::GetMagneticEffectColor(EMagneticType type, EMagneticEffectColorType effect)
{
	if (type == EMagneticType::NONE) return FLinearColor::White;
	bool isN = type == EMagneticType::N;

	switch (effect) {
		/*자성 고리 이펙트*/
		case(EMagneticEffectColorType::RING_EFFECT):
			return (isN? FLinearColor(10.f, 0.243241, 0.f,1.f):FLinearColor(0.f, 1.99f, 20.f , 1.f));
		
		/*총의 자성 이펙트*/
		case(EMagneticEffectColorType::GUN_EFFECT_LAZER):
			return (isN ? FLinearColor(20.f, 0.f, 0.574217f,1.f) : FLinearColor(0.f, 0.70209f, 20.f, 1.f));

		case(EMagneticEffectColorType::GUN_EFFECT_SPARK_MIN):
			return (isN ? FLinearColor(10.f, 0.f, 0.287108f, 1.f) : FLinearColor(0.f, 4.245329f, 10.f,1.f));
	
		case(EMagneticEffectColorType::GUN_EFFECT_SPARK_MAX):
			return (isN ? FLinearColor(10.f, 0.42364f, 0.f,1.f) : FLinearColor(0.f, 0.351045f, 10.f, 1.f));

		/*총 발사 이펙트*/
		case(EMagneticEffectColorType::GUN_SHOOT_EFFECT_MIN):
			return (isN ? FLinearColor(10.f, 0.f, 0.288108f, 1.f) : FLinearColor(0.f, 4.245329f, 10.f, 1.f));
		
		case(EMagneticEffectColorType::GUN_SHOOT_EFFECT_MAX):
			return (isN ? FLinearColor(10.f, 0.42364f, 0.f, 1.f) : FLinearColor(0.f, 0.351045f, 10.f, 1.f));

		/*자성이 부여되었을 때의 이펙트*/
		case(EMagneticEffectColorType::GRANT_EFFECT):
			return (isN ? FLinearColor(25.f, 0.f, 0.083315f, 1.f) : FLinearColor(0.f, 0.160623f, 10.f, 1.f));
	
		/*자성 비네팅 이펙트*/
		case(EMagneticEffectColorType::ELECTRIC_VIGNETTING_EFFECT):
			return (isN ? FLinearColor(0.984f, 0.135f, 0.161f, 0.3f) : FLinearColor(0.f, 0.690244f, 0.984375f, 0.3f));
	
		/*건틀렛 구체 이펙트*/
		case(EMagneticEffectColorType::GAUNTLET_SPHERE_EFFECT):
			return (isN ? FLinearColor(2.f, 0.f, 0.019997f, 0.5f) : FLinearColor(0.f, 0.059361f, 2.f, 1.f));

		/*건틀렛 번개 이펙트*/
		case(EMagneticEffectColorType::GAUNTLET_THUNDER_EFFECT):
			return (isN ? FLinearColor(100.f, 0.f, 1.428556f, .5f) : FLinearColor(0.f, 1.484013f, 50.f, 1.f));
	}

	return FLinearColor::White;
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
		bDefaultPrimitiveGravity = _parent->IsGravityEnabled();
		_parent->SetMobility(EComponentMobility::Movable);
		GetAttachmentRoot()->SetMobility(EComponentMobility::Movable);
	}

	/*무게 및 자기장 크기 초기화*/
	SettingMagnetWeightAndFieldRange();

	if (CurrMagnetic!=EMagneticType::NONE)
	{
		EMagneticType type = CurrMagnetic;
		CurrMagnetic = EMagneticType::NONE;
		SetCurrentMagnetic(type);
	}
}

void UMagneticComponent::DestroyComponent(bool bPromoteChilderen)
{
	Super::DestroyComponent(bPromoteChilderen);

	if (_parentMesh && ::IsValid(_parentMesh))
	{
		_parentMesh->SetMaterial(0, nullptr);
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
		FieldEffectComp->SetMagneticFieldInfo(CurrMagnetic, FinalMagneticFieldRadius);
		_magActivate = false;
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

	bool notChanged = CurrMagnetic == EMagneticType::NONE && newType == EMagneticType::NONE;
	bool sameMagnetic = CurrMagnetic == newType;
	bool changeMagnetic = CurrMagnetic != newType;
	bool addMagCount = true;

	if (notChanged) return;

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
		FieldEffectComp->SetMagneticFieldInfo(EMagneticType::NONE, FinalMagneticFieldRadius);

		//Simulate physics 적용중이였다면, 중력 적용을 원상복귀 시킨다.
		if (_parent && _parent->IsSimulatingPhysics()) _parent->SetEnableGravity(bDefaultPrimitiveGravity);

		//만약 이동중에 자성이 변경되었다면, 이동이 끝임을 수신하고 무시했던 MovementComponent들을 활성화.
		if (_movement && _applyMovement)
		{
			OnComponentMagnetEndMovement.Broadcast(_lastMoveType, this);
			_lastMoveType = EMagnetMoveType::NONE;
			_applyMovement = false;
		}
	}
	else 
	{
		CurrHaveMagneticSeconds = MaxHaveMagneticSeconds;
		if (changeMagnetic)
		{
			_magActivate = false;
		}

		SettingMagnetWeightAndFieldRange();
		FieldEffectComp->SetMagneticFieldInfo(CurrMagnetic, FinalMagneticFieldRadius);
	}

	OnComponentMagneticChanged.Broadcast(CurrMagnetic, this);
	SetParentMaterial(CurrMagnetic);
	#pragma endregion
}

// Called every frame
void UMagneticComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	#pragma region Summary
	//자성을 유지할 수 있는 시간이 넘으면 자성을 잃게 된다.
	if (!bEternalHaveMagnetic && CurrMagnetic != EMagneticType::NONE && CurrHaveMagneticSeconds > 0.f)
	{
		CurrHaveMagneticSeconds -= DeltaTime;
		if (CurrHaveMagneticSeconds <= 0.f)
		{
			CurrHaveMagneticSeconds = 0.f;
			FieldEffectComp->SetMagneticFieldInfo(CurrMagnetic, 0.f);
			SetCurrentMagnetic(EMagneticType::NONE);
		}
	}

	//자성 변경 애니메이션
	if (_material && _currMagMaterialApplyRatio != _goalMagMaterialApplyRatio) {

		float gap = (_goalMagMaterialApplyRatio - _currMagMaterialApplyRatio);

		if (FMath::Abs(gap)<=0.02f)
		{
			_currMagMaterialApplyRatio = _goalMagMaterialApplyRatio;
			_material->SetScalarParameterValue(MAGNETIC_GRANT_COLOR_PARAM, _currMagMaterialApplyRatio);
		}
		else
		{
			_currMagMaterialApplyRatio += 0.1f * gap;
			_material->SetScalarParameterValue(MAGNETIC_GRANT_COLOR_PARAM, _currMagMaterialApplyRatio);
		}
	}

	//자성이 부여되어 있지 않고, 부착된 MagneticMovement 컴포넌트가 없다면 움직일 이유가 없으니 스킵.
	if (CurrMagnetic == EMagneticType::NONE || _movement == nullptr || _movement != nullptr && !::IsValid(_movement))
	{
		return;
	}

	//또한 CollisionProfile의 지정으로, MagneticField를 가지는 컴포넌트만 충돌을 발생시키기에 동일 클래스의 USphereComponent만 충돌판정을 한다.
	//현재 자기장 범위와 겹쳐있는 자기장을 가진 자석들에 대해서 영향을 받는다.
	TArray<UPrimitiveComponent*> overlapList;
	float maxWeight = 0.f;
	bool applyLogic = false;
	AActor* finalHit = nullptr;
	FVector finalNormal = FVector::ZeroVector;
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
			OnComponentMagnetBeginMovement.Broadcast(moveType, this, magnet);
			_movement->StartMovement(moveType, this, magnet);
		}
		_applyMovement = true;
		applyLogic = true;
		CurrHaveMagneticSeconds = MaxHaveMagneticSeconds;
		if (bAllowMagneticMovement == false) break;

		//부딫힌 것이 자석이라면
		FHitResult hit;
		_movement->ApplyUpdatedComponentMovement(moveType, this, magnet, DeltaTime, hit);
		if (hit.bBlockingHit && hit.GetActor() == magnet->GetOwner())
		{
			finalHit = hit.GetActor();
			finalNormal = hit.Normal;
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
		OnComponentMagnetEndMovement.Broadcast(_lastMoveType, this);

		if (_parent && _parent->IsSimulatingPhysics()) _parent->SetEnableGravity(bDefaultPrimitiveGravity);
		return;
	}
	else if (applyLogic && finalHit != nullptr && ::IsValid(finalHit))
	{
		OnComponentMagnetMoveHit.Broadcast(finalHit, this, finalNormal);
	}
	#pragma endregion
}

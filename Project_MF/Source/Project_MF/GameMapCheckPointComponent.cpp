#include "GameMapCheckPointComponent.h"
#include "Components/SceneComponent.h"

UGameMapCheckPointComponent::UGameMapCheckPointComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ConeMesh = nullptr;
	ConeMaterial = nullptr;
	RGB = FLinearColor(1.f, 0.f, 0.f, 1.f);

	//////// *CDO* ///////////
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CONE_MESH(
		TEXT("/Engine/BasicShapes/Cone.Cone")
	);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MATERIAL(
		TEXT("/Game/Materials/Color/delivery")
	);

	////// *Cone Mesh* ///////
	ConeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CONE"));
	ConeMesh->SetupAttachment(this);
	ConeMesh->SetRelativeScale3D(FVector(1.7f, 1.7f, 1.7f));
	ConeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConeMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 50.f)*1.7f, FRotator::MakeFromEuler(FVector(0.f, 180.f, 0.f)));
	if (CONE_MESH.Succeeded())
	{
		ConeMesh->SetStaticMesh(CONE_MESH.Object);
	}

	/////// *MATERIAL* ////////
	if (MATERIAL.Succeeded())
	{
		Material = MATERIAL.Object;
	}
}

void UGameMapCheckPointComponent::InitConeMaterial()
{
	//머터리얼 인스턴스를 만든다.
	if (Material && ::IsValid(Material) && ConeMaterial == nullptr || ConeMaterial && !::IsValid(ConeMaterial))
	{
		ConeMaterial = UMaterialInstanceDynamic::Create(Material, this);
		if(ConeMaterial) ConeMaterial->SetVectorParameterValue(TEXT("Color"), FVector(RGB.R, RGB.G, RGB.B));
	}

	//머터리얼 적용.
	if (ConeMesh && ::IsValid(ConeMesh) && ConeMesh->GetMaterial(0) != ConeMaterial)
	{
		ConeMesh->SetMaterial(0, ConeMaterial);
	}
}

void UGameMapCheckPointComponent::OnRegister()
{
	Super::OnRegister();

	InitConeMaterial();
}

void UGameMapCheckPointComponent::OnAttachmentChanged()
{
	Super::OnAttachmentChanged();

	if(GetAttachParent()!=nullptr) InitConeMaterial();
}
bool UGameMapCheckPointComponent::CanAttachAsChild(const USceneComponent* ChildComponent, FName SocketName) const
{
	return (ChildComponent == ConeMesh);
}

void UGameMapCheckPointComponent::DestroyComponent(bool bPromoteChilderen)
{
	if (ConeMesh && ::IsValid(ConeMesh))
	{
		ConeMesh->DestroyComponent(bPromoteChilderen);
	}

	Super::DestroyComponent(bPromoteChilderen);
}

#if WITH_EDITOR
void UGameMapCheckPointComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FString& changed = PropertyChangedEvent.GetPropertyName().ToString();

	if (changed=="RGB" || changed=="R" || changed=="G" || changed=="B")
	{
		if(ConeMaterial && ::IsValid(ConeMaterial))	
			ConeMaterial->SetVectorParameterValue(TEXT("Color"), FVector(RGB.R, RGB.G, RGB.B));
	}
}
#endif
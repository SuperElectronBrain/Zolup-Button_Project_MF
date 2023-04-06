// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerConnectionComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UPowerConnectionComponent::UPowerConnectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ObjectLength = 1;
	TriggerSize = 3;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Engine/BasicShapes/Cube.Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));

#if WITH_EDITORONLY_DATA
	DebugMeshComponent = CreateEditorOnlyDefaultSubobject<UStaticMeshComponent>(TEXT("DebugMesh"));
	if (IsRunningCommandlet() == false)
	{
		if (DebugMeshComponent != nullptr)
		{
			DebugMeshComponent->SetupAttachment(this);
			if (SM_BOX.Succeeded() == true)
			{
				DebugMeshComponent->SetStaticMesh(SM_BOX.Object);
				if (M_MATERIAL.Succeeded() == true) { DebugMeshComponent->SetMaterial(0, M_MATERIAL.Object); }
			}
			DebugMeshComponent->SetHiddenInGame(true);
		}
	}
#endif

#pragma region UnUsed
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Engine/BasicShapes/Cube.Cube"));
	//if (SM_BOX.Succeeded() == true) { MeshOrigin = SM_BOX.Object; }
	//static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Game/Resource/Materials/M_MFMaterial.M_MFMaterial"));
	//if (M_MATERIAL.Succeeded() == true) { MaterialOrigin = M_MATERIAL.Object; }

	//UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->SetupAttachment(this);
	//if (SM_BOX.Succeeded() == true)
	//{
	//	Mesh->SetStaticMesh(SM_BOX.Object);
	//	if (M_MATERIAL.Succeeded() == true)
	//	{
	//		Mesh->SetMaterial(0, M_MATERIAL.Object);
	//	}
	//}
#pragma endregion

	LeftPart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftPart"));
	LeftPart->SetupAttachment(this);
	CenterPart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CenterPart"));
	CenterPart->SetupAttachment(this);
	RightPart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightPart"));
	RightPart->SetupAttachment(this);
	if (SM_BOX.Succeeded() == true)
	{
		LeftPart->SetStaticMesh(SM_BOX.Object);
		CenterPart->SetStaticMesh(SM_BOX.Object);
		RightPart->SetStaticMesh(SM_BOX.Object);

		if (M_MATERIAL.Succeeded() == true) 
		{
			LeftPart->SetMaterial(0, M_MATERIAL.Object);
			CenterPart->SetMaterial(0, M_MATERIAL.Object);
			RightPart->SetMaterial(0, M_MATERIAL.Object);
		}
	}

	LeftCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftCollider"));
	LeftCollider->SetupAttachment(this);
	LeftCollider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	LeftCollider->SetCollisionProfileName(TEXT("Collider"));
	RightCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RightCollider"));
	RightCollider->SetupAttachment(this);
	RightCollider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	RightCollider->SetCollisionProfileName(TEXT("Collider"));

	float BoxSize = (TriggerSize * 100.0f) + 50.0f;
	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftTrigger"));
	LeftTrigger->SetupAttachment(this);
	LeftTrigger->SetBoxExtent(FVector(BoxSize, BoxSize, BoxSize));
	LeftTrigger->SetCollisionProfileName(TEXT("NewTrigger"));
	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightTrigger"));
	RightTrigger->SetupAttachment(this);
	RightTrigger->SetBoxExtent(FVector(BoxSize, BoxSize, BoxSize));
	RightTrigger->SetCollisionProfileName(TEXT("NewTrigger"));

#pragma region UnUsed
	//for (int i = 0; i < ObjectLength; i = i + 1)
	//{
	//	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*(FString(TEXT("Mesh")) + FString::FromInt(i))));
	//	Meshs.Add(Mesh);
	//	Mesh->SetupAttachment(this);
	//
	//	if (SM_BOX.Succeeded() == true)
	//	{
	//		Mesh->SetStaticMesh(SM_BOX.Object);
	//		if (M_MATERIAL.Succeeded() == true)
	//		{
	//			Mesh->SetMaterial(0, M_MATERIAL.Object);
	//			Mesh->SetRelativeLocation(FVector(0.0f, 100.0f * ((i % 2 == 0 ? 0 : 1) + i) / 2 * (i % 2 == 0 ? 1 : -1), 0.0f));
	//		}
	//	}
	//}
	//
	//for (int i = 0; i < (ObjectLength > TriggerSize + 1 ? 2 : 1); i = i + 1)
	//{
	//	UBoxComponent* Collider = CreateDefaultSubobject<UBoxComponent>(FName(*(FString(TEXT("Collider")) + FString::FromInt(i))));
	//	UBoxComponent* Trigger = CreateDefaultSubobject<UBoxComponent>(FName(*(FString(TEXT("Trigger")) + FString::FromInt(i))));
	//
	//	Colliders.Add(Collider);
	//	Triggers.Add(Trigger);
	//
	//	Collider->SetupAttachment(this);
	//	Collider->SetRelativeLocation(FVector(0.0f, 100.0f * (ObjectLength - 1) / 2 * (i < 1 ? -1 : 1), 0.0f));
	//	Collider->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	//	Collider->SetCollisionProfileName(TEXT("Carrier"));
	//
	//	Trigger->SetupAttachment(this);
	//	//Triggers가 1개만 존재해야 할 때
	//	if(ObjectLength <= TriggerSize + 1)
	//	{
	//		Trigger->SetBoxExtent(FVector(TriggerSize * 50.0f, (ObjectLength + TriggerSize - 1) * 50.0f, TriggerSize * 50.0f));
	//	}
	//	//Triggers가 2개 이상 존재해야 할 때
	//	else if (ObjectLength > TriggerSize + 1)
	//	{
	//		Trigger->SetRelativeLocation(FVector(0.0f, 100.0f * (ObjectLength - 1) / 2 * (i < 1 ? -1 : 1), 0.0f));
	//		float BoxSize = TriggerSize * 50.0f;
	//		Trigger->SetBoxExtent(FVector(BoxSize, BoxSize, BoxSize));
	//	}
	//	Trigger->SetCollisionProfileName(TEXT("Connector"));
	//}
	//...
#pragma endregion
}

// Called when the game starts
void UPowerConnectionComponent::BeginPlay()
{
	Super::BeginPlay();
	//Meshs[0]->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	UStaticMeshComponent* OwnerRootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (::IsValid(OwnerRootComponent) == true)
	{
		OwnerRootComponent->SetHiddenInGame(true);
	}

	if (LeftPartMesh != nullptr)
	{
		LeftPart->SetStaticMesh(LeftPartMesh);
	}
	if (CenterPartMesh != nullptr)
	{
		CenterPart->SetStaticMesh(CenterPartMesh);
	}
	if (RightPartMesh != nullptr)
	{
		RightPart->SetStaticMesh(RightPartMesh);
	}

	FVector ComponentLocation = FVector(0.0f, 100.0f * (ObjectLength - 1) / 2, 0.0f);
	LeftPart->SetRelativeLocation(-ComponentLocation);
	CenterPart->SetRelativeScale3D(FVector(1.0f, ObjectLength < 4 ? 1 : ObjectLength - 2, 1.0f));
	RightPart->SetRelativeLocation(ComponentLocation);

	LeftCollider->SetRelativeLocation(-ComponentLocation);
	RightCollider->SetRelativeLocation(ComponentLocation);
	
	
	float BoxSize = TriggerSize * 100.0f;
	FVector OwnerScale = GetOwner()->GetRootComponent()->GetRelativeScale3D();
	LeftTrigger->SetBoxExtent(FVector(50.0f + (BoxSize / OwnerScale.X), 50.0f + (BoxSize / OwnerScale.Y), 50.0f + (BoxSize / OwnerScale.Z)));
	LeftTrigger->SetRelativeLocation(-ComponentLocation);
	RightTrigger->SetBoxExtent(FVector(50.0f + (BoxSize / OwnerScale.X), 50.0f + (BoxSize / OwnerScale.Y), 50.0f + (BoxSize / OwnerScale.Z)));
	RightTrigger->SetRelativeLocation(ComponentLocation);

	//SetObjectLength(ObjectLength);
	//SetTriggerSize(TriggerSize);

	// ...

	LeftTrigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerConnectionComponent::OnOverlapBegin);
	LeftTrigger->OnComponentEndOverlap.AddDynamic(this, &UPowerConnectionComponent::OnOverlapEnd);
	RightTrigger->OnComponentBeginOverlap.AddDynamic(this, &UPowerConnectionComponent::OnOverlapBegin);
	RightTrigger->OnComponentEndOverlap.AddDynamic(this, &UPowerConnectionComponent::OnOverlapEnd);
	
	SetPowerState(!bPowerState);
	SetPowerState(!bPowerState);

	UpdateMaterialColor();
}

#if WITH_EDITOR
void UPowerConnectionComponent::PostInitProperties()
{
	Super::PostInitProperties();

#if WITH_EDITORONLY_DATA
	if (IsRunningCommandlet() == false)
	{
		if (DebugMeshComponent != nullptr)
		{
			DebugMeshComponent->SetRelativeScale3D(FVector(1.0f, ObjectLength, 1.0f));
		}
	}
#endif
}
void UPowerConnectionComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

#if WITH_EDITORONLY_DATA
	if (IsRunningCommandlet() == false)
	{
		if (DebugMeshComponent != nullptr)
		{
			DebugMeshComponent->SetRelativeScale3D(FVector(1.0f, ObjectLength, 1.0f));
		}
	}
#endif
}
#endif

// Called every frame
void UPowerConnectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#pragma region UnUsed
//#if ENABLE_DRAW_DEBUG
//	DrawDebugBox(GetWorld(), LeftTrigger->GetComponentLocation(), FVector(150.0f, 150.0f, 150.0f), FQuat(GetOwner()->GetActorRotation()), FColor::Red, false, 0.1f);
//	DrawDebugBox(GetWorld(), RightTrigger->GetComponentLocation(), FVector(150.0f, 150.0f, 150.0f), FQuat(GetOwner()->GetActorRotation()), FColor::Red, false, 0.1f);
//#endif
#pragma endregion

	//...
}

void UPowerConnectionComponent::UpdateMaterialColor()
{
	//UStaticMeshComponent* OwnerRootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	for (int i = 0; i < 3; i = i + 1)
	{
		UStaticMeshComponent * StaticMeshComponent = i < 1 ? LeftPart : (i < 2 ? CenterPart : RightPart);
		if (StaticMeshComponent != nullptr)
		{
			if (StaticMeshComponent->GetStaticMesh() != nullptr)
			{
				UMaterialInstanceDynamic* DynamicMaterial = StaticMeshComponent->CreateDynamicMaterialInstance(0);
				if (DynamicMaterial != nullptr)
				{
					if (bPowerState == true)
					{
						DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(0.0f, 1.0f, 0.0f));
					}
					else if (bPowerState == false)
					{
						DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(0.5f, 0.5f, 0.5f));
					}
				}
			}
		}
	}
}
#pragma region UnUsed
//void UPowerConnectionComponent::SetObjectLength(int32 param)
//{
//	if(param > 0)
//	{
//		//if (ObjectLength != param)
//		//{
//			//새로 변경될 길이가 기존보다 더 길다면
//			if (Meshs.Num() < param)
//			{
//				//추가될 길이만큼 메쉬를 생성
//				int32 MeshsNum = Meshs.Num();
//				//UE_LOG(LogTemp, Warning, TEXT("%d"), MeshsNum);
//				for (int i = 0; i < (param - MeshsNum); i = i + 1)
//				{
//					UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());//, FName(*(FString(TEXT("Mesh")) + FString::FromInt(MeshsNum + i) + FString(TEXT("(Dynamic)")))));
//					if (StaticMeshComponent != nullptr)
//					{
//						if (StaticMeshComponent->IsRegistered() == false)
//						{
//							StaticMeshComponent->RegisterComponent();
//						}
//						StaticMeshComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//						StaticMeshComponent->SetStaticMesh(MeshOrigin);
//						StaticMeshComponent->SetMaterial(0, MaterialOrigin);
//						Meshs.Add(StaticMeshComponent);
//					}
//				}
//
//				int32 CollidersNum = Colliders.Num();
//				for (int i = 0; i < (param < 3 ? 1 : 2) - CollidersNum; i = i + 1)
//				{
//					UBoxComponent* Collider = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass());//, FName(*(FString(TEXT("Collider")) + FString::FromInt(Colliders.Num()) + FString(TEXT("(Dynamic)")))));
//					if (Collider != nullptr)
//					{
//						if (Collider->IsRegistered() == false)
//						{
//							Collider->RegisterComponent();
//						}
//						Collider->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//						Collider->SetCollisionProfileName(TEXT("Collider"));
//						Colliders.Add(Collider);
//					}
//				}
//				
//				int32 TriggersNum = Triggers.Num();
//				for (int i = 0; i < (param > TriggerSize + 1 ? 2 : 1) - TriggersNum; i = i + 1)
//				{
//					UBoxComponent* Trigger = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass());//, FName(*(FString(TEXT("Trigger")) + FString::FromInt(Triggers.Num()) + FString(TEXT("(Dynamic)")))));
//					if (Trigger != nullptr)
//					{
//						if (Trigger->IsRegistered() == false)
//						{
//							Trigger->RegisterComponent();
//						}
//						Trigger->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//						Trigger->SetCollisionProfileName(TEXT("NewTrigger"));
//						Triggers.Add(Trigger);
//					}
//				}
//			}
//			//새로 변경될 길이가 기존보다 더 짧다면
//			else if (Meshs.Num() > param)
//			{
//				int32 MeshsNum = Meshs.Num();
//				//UE_LOG(LogTemp, Warning, TEXT("%d"), MeshsNum);
//				for (int i = 0; i < (MeshsNum - param); i = i + 1)
//				{
//					UStaticMeshComponent* StaticMeshComponent = Meshs.Pop();
//					StaticMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
//					if (StaticMeshComponent->IsRegistered() == true)
//					{
//						StaticMeshComponent->UnregisterComponent();
//					}
//					StaticMeshComponent->DestroyComponent();
//				}
//
//				int32 CollidersNum = Colliders.Num();
//				for (int i = 0; i < CollidersNum - (param < 3 ? 1 : 2); i = i + 1)
//				{
//					UBoxComponent* Collider = Colliders.Pop();
//					Collider->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
//					if (Collider->IsRegistered() == true)
//					{
//						Collider->UnregisterComponent();
//					}
//					Collider->DestroyComponent();
//				}
//
//				int32 TriggersNum = Triggers.Num();
//				for (int i = 0; i < TriggersNum - (param > TriggerSize + 1 ? 2 : 1); i = i + 1)
//				{
//					UBoxComponent* Trigger = Triggers.Pop();
//					Trigger->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
//					if (Trigger->IsRegistered() == true)
//					{
//						Trigger->UnregisterComponent();
//					}
//					Trigger->DestroyComponent();
//				}
//			}
//
//			for (int i = 0; i < Meshs.Num(); i = i + 1)
//			{
//				Meshs[i]->SetRelativeLocation(FVector(0.0f, (Meshs.Num() % 2 == 0 ? 50 : 0) + 100.0f * ((i % 2 == 0 ? 0 : 1) + i) / 2 * (i % 2 == 0 ? 1 : -1), 0.0f));
//			}
//
//			for (int i = 0; i < Colliders.Num(); i = i + 1)
//			{
//				Colliders[i]->SetBoxExtent(FVector(50.0f, param == 2 ? 100.0f : 50.0f, 50.0f));
//				Colliders[i]->SetRelativeLocation(FVector(0.0f, 100.0f * ((param == 2 ? 1 : param) - 1) / 2 * (i < 1 ? -1 : 1), 0.0f));
//			}
//
//			for (int i = 0; i < Triggers.Num(); i = i + 1)
//			{
//				float BoxSize = TriggerSize * 50.0f;
//				Triggers[i]->SetBoxExtent(FVector(BoxSize, param > TriggerSize + 1 ? BoxSize : (param + TriggerSize - 1) * 50, BoxSize));
//				Triggers[i]->SetRelativeLocation(FVector(0.0f, 100.0f * ((param > TriggerSize + 1 ? param : 1) - 1) / 2 * (i < 1 ? -1 : 1), 0.0f));
//			}
//		//}
//
//		ObjectLength = param;
//	}
//}
//
//void UPowerConnectionComponent::SetTriggerSize(int32 param)
//{
//	//if (TriggerSize != param)
//	//{
//		
//		if ((ObjectLength > param + 1 ? 2 : 1) > Triggers.Num())
//		{
//			int32 TriggersNum = Triggers.Num();
//			for (int i = 0; i < (ObjectLength > param + 1 ? 2 : 1) - TriggersNum; i = i + 1)
//			{
//				UBoxComponent* Trigger = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass());//, FName(*(FString(TEXT("Trigger")) + FString::FromInt(Triggers.Num()) + FString(TEXT("(Dynamic)")))));
//				if (Trigger != nullptr)
//				{
//					if (Trigger->IsRegistered() == false)
//					{
//						Trigger->RegisterComponent();
//					}
//					Trigger->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
//					Trigger->SetCollisionProfileName(TEXT("NewTrigger"));
//					Triggers.Add(Trigger);
//				}
//			}
//		}
//		else if ((ObjectLength > param + 1 ? 2 : 1) < Triggers.Num())
//		{
//			int32 TriggersNum = Triggers.Num();
//			for (int i = 0; i < TriggersNum - (ObjectLength > param + 1 ? 2 : 1); i = i + 1)
//			{
//				UBoxComponent* Trigger = Triggers.Pop();
//				Trigger->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
//				if (Trigger->IsRegistered() == true)
//				{
//					Trigger->UnregisterComponent();
//				}
//				Trigger->DestroyComponent();
//			}
//		}
//
//		for (int i = 0; i < Triggers.Num(); i = i + 1)
//		{
//			float BoxSize = TriggerSize * 50.0f;
//			Triggers[i]->SetBoxExtent(FVector(BoxSize, ObjectLength > param + 1 ? BoxSize : (ObjectLength + param - 1) * 50, BoxSize));
//			Triggers[i]->SetRelativeLocation(FVector(0.0f, 100.0f * ((ObjectLength > param + 1 ? ObjectLength : 1) - 1) / 2 * (i < 1 ? -1 : 1), 0.0f));
//		}
//
//		TriggerSize = param;
//	//}
//}
#pragma endregion

void UPowerConnectionComponent::SetPowerState(bool param, bool IsGenerator)
{
	if (bPowerState != param)
	{
		bPowerState = param;

		for (int i = 0; i < 2; i = i + 1)
		{
			FVector TriggerLocation;
			FVector TriggerVolume;
			
			TriggerLocation = (i == 0 ? LeftCollider : RightCollider)->GetComponentLocation();
			//float BoxSize = TriggerSize * 50.0f;
			float BoxSize = TriggerSize * 100.0f;
			FVector OwnerScale = GetOwner()->GetRootComponent()->GetRelativeScale3D();
			TriggerVolume = FVector((OwnerScale.X * 50.0f) + BoxSize, (OwnerScale.Y * 50.0f) + BoxSize, (OwnerScale.Z * 50.0f) + BoxSize);
			//TriggerVolume = FVector(BoxSize, BoxSize, BoxSize);

			TArray<FHitResult> HitResult;
			FCollisionQueryParams Params(NAME_None, false, GetOwner());
			bool bResult = GetWorld()->SweepMultiByChannel
			(
				HitResult,
				TriggerLocation,
				TriggerLocation,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel4,
				FCollisionShape::MakeBox(TriggerVolume),
				Params
			);
#pragma region UnUsed
//#if ENABLE_DRAW_DEBUG
//			FColor DrawColor = bResult == true ? FColor::Green : FColor::Red;
//			float DebugLifeTime = 5.0f;
//
//			DrawDebugBox(GetWorld(), TriggerLocation, FVector(150.0f, 150.0f, 150.0f), FQuat(GetOwner()->GetActorRotation()), DrawColor, false, DebugLifeTime);
//#endif
#pragma endregion

			if (bResult == true)
			{
				for (int j = 0; j < HitResult.Num(); j = j + 1)
				{
					if (HitResult[j].Actor.IsValid() == true)
					{
						UPowerComponent* PowerConnectionComponent = Cast<UPowerComponent>(HitResult[j].Actor->FindComponentByClass<UPowerComponent>());
						if (PowerConnectionComponent != nullptr)
						{
							if (PowerConnectionComponent != this)
							{
								PowerConnectionComponent->SetPowerState(bPowerState);
							}
						}
					}
				}
			}
		}

		UpdateMaterialColor();
	}
}

void UPowerConnectionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UPowerComponent* PowerConnectionComponent = OtherActor->FindComponentByClass<UPowerComponent>();
	if (PowerConnectionComponent != nullptr)
	{
		if (PowerConnectionComponent != this)
		{
			if (bPowerState == true)
			{
				PowerConnectionComponent->SetPowerState(true);
			}
		}
	}
}

void UPowerConnectionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UPowerComponent* PowerConnectionComponent = OtherActor->FindComponentByClass<UPowerComponent>();
	if (PowerConnectionComponent != nullptr)
	{
		if (PowerConnectionComponent != this)
		{
			SetPowerState(false);
			PowerConnectionComponent->SetPowerState(false);
		}
	}
}
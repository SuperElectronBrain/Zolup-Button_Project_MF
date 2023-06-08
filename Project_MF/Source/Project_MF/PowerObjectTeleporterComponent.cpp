// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerObjectTeleporterComponent.h"

UPowerObjectTeleporterComponent::UPowerObjectTeleporterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	NeedPower = true;
	ActivateDespawner = false;
	ActingTarget = EPowerActingTarget::Everything;
	UnlimitedActing = true;
	ActingTimes = 1;

	//BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//BoxComponent->SetupAttachment(this);
}

void UPowerObjectTeleporterComponent::BeginPlay()
{
	Super::BeginPlay();
	
	int32 ComponentsFindCount = 0;
	TArray<USceneComponent*> ParentsComponents = GetAttachParent()->GetAttachChildren();
	for (int32 i = 0; i < ParentsComponents.Num(); i = i + 1)
	{
		UArrowComponent* Arrow = Cast<UArrowComponent>(ParentsComponents[i]);
		if (::IsValid(Arrow) == true)
		{
			ArrowComponent = Arrow;
			ArrowComponent->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform);
			ComponentsFindCount = ComponentsFindCount + 1;
		}

		UBoxComponent* Box = Cast<UBoxComponent>(ParentsComponents[i]);
		if (::IsValid(Box) == true)
		{
			BoxComponent = Box;
			BoxComponent->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform);
			BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
			BoxComponent->SetGenerateOverlapEvents(true);
			//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UPowerObjectTeleporterComponent::OnOverlapBegin);
			//BoxComponent->OnComponentEndOverlap.AddDynamic(this, &UPowerObjectTeleporterComponent::OnOverlapEnd);
			ComponentsFindCount = ComponentsFindCount + 1;
		}

		if (ComponentsFindCount > 1)
		{
			break;
		}
	}
}

void UPowerObjectTeleporterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Action(DeltaTime);
}

void UPowerObjectTeleporterComponent::Action(float DeltaTime)
{
	bool Case_0 = false;

	if (NeedPower == false)
	{
		Case_0 = true;
	}

	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			Case_0 = true;

			if (bActingState == false) { bActingState = true; }
		}
		else if (ObserveTargetExecutionComponent->GetPowerState() == false)
		{
			if (bActingState == true) { bActingState = false; }
		}
	}

	if (Case_0 == true)
	{
		int Count = 0;
		TArray<AActor*> OverlappingActors;
		BoxComponent->GetOverlappingActors(OverlappingActors);
		for (int i = 0; i < OverlappingActors.Num(); i = i + 1)
		{
			if (OverlappingActors[i] != GetOwner())
			{
				if (OverlappingActors[i]->GetRootComponent()->Mobility == EComponentMobility::Movable)
				{
					bool Case_1 = true;
					if (ActingTarget == EPowerActingTarget::PlayerIgnore)
					{
						if (::IsValid(Cast<ACharacter>(OverlappingActors[i])) == true)
						{
							Case_1 = false;
						}
					}
					else if (ActingTarget == EPowerActingTarget::PlayerOnly)
					{
						if (::IsValid(Cast<ACharacter>(OverlappingActors[i])) == false)
						{
							Case_1 = false;
						}
					}

					if (Case_1 == true)
					{
						if (UnlimitedActing == true)
						{
							if (ActingTimes < 1)
							{
								ActingTimes = 1;
							}
						}

						if (ActingTimes > 0)
						{
							if (::IsValid(ArrowComponent.Get()) == true)
							{
								if (ActivateDespawner == false)
								{
									OverlappingActors[i]->SetActorLocationAndRotation(ArrowComponent->GetComponentLocation(), ArrowComponent->GetComponentRotation());
								}
								else if (ActivateDespawner == true)
								{
									if (::IsValid(Cast<ACharacter>(OverlappingActors[i])) == true)
									{

									}
									else if (::IsValid(Cast<ACharacter>(OverlappingActors[i])) == false)
									{
										OverlappingActors[i]->Destroy();
									}
								}

								if (UnlimitedActing == false)
								{
									ActingTimes = ActingTimes - 1;
								}
							}
						}
						else if (ActingTimes < 1)
						{
							SetComponentTickEnabled(false);
						}
					}
				}
			}
		}
	}
}

void UPowerObjectTeleporterComponent::BeginDestroy()
{
	Super::BeginDestroy();

	//if (::IsValid(ArrowComponent.Get()) == true)
	//{
	//	ArrowComponent->DestroyComponent();
	//}
	//if (::IsValid(BoxComponent.Get()) == true)
	//{
	//	BoxComponent->DestroyComponent();
	//}
}

void UPowerObjectTeleporterComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void UPowerObjectTeleporterComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
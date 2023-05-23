// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerObjectTeleporterComponent.h"

UPowerObjectTeleporterComponent::UPowerObjectTeleporterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UnlimitedActing = true;
	ActingTimes = 1;

	//BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//BoxComponent->SetupAttachment(this);
}

void UPowerObjectTeleporterComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> ParentsComponents = GetAttachParent()->GetAttachChildren();
	for (int32 i = 0; i < ParentsComponents.Num(); i = i + 1)
	{
		UArrowComponent* Arrow = Cast<UArrowComponent>(ParentsComponents[i]);
		if (::IsValid(Arrow) == true)
		{
			ArrowComponent = Arrow;
			ArrowComponent->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform);
			break;
		}
	}

	TArray<USceneComponent*> ParentsComponents = GetAttachParent()->GetAttachChildren();
	for (int32 i = 0; i < ParentsComponents.Num(); i = i + 1)
	{
		UBoxComponent* Box = Cast<UBoxComponent>(ParentsComponents[i]);
		if (::IsValid(Box) == true)
		{
			BoxComponent = Box;
			BoxComponent->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform);
			BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
			BoxComponent->SetGenerateOverlapEvents(true);
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UPowerObjectTeleporterComponent::OnOverlapBegin);
			BoxComponent->OnComponentEndOverlap.AddDynamic(this, &UPowerObjectTeleporterComponent::OnOverlapEnd);
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
	
}

void UPowerObjectTeleporterComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
		{
			if (ObserveTargetExecutionComponent->GetPowerState() == true)
			{
				if (bActingState == false)
				{
					bActingState = true;

					if (ActingTimes > 0)
					{
						if (::IsValid(ArrowComponent.Get()) == true)
						{
							OtherActor->SetActorLocationAndRotation(ArrowComponent->GetComponentLocation(), ArrowComponent->GetComponentRotation());
							ActingTimes = ActingTimes - 1;
						}
					}

					//if (OneTime == true)
					//{
					//	SetComponentTickEnabled(false);
					//}
				}
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{
				if (bActingState == true)
				{
					bActingState = false;
				}
			}
		}
	}
}

void UPowerObjectTeleporterComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
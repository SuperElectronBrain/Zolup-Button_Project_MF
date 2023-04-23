// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerDirectionMovementComponent.h"

UPowerDirectionMovementComponent::UPowerDirectionMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
//#if WITH_EDITORONLY_DATA
	//ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	//ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	//
	//if (IsRunningCommandlet() == false)
	//{
	//	if (ArrowComponent)
	//	{
	//		ArrowComponent->ArrowColor = FColor(150, 200, 255);
	//		ArrowComponent->SetupAttachment(this);
	//		ArrowComponent->ArrowSize = 1.0f;
	//		ArrowComponent->bTreatAsASprite = true;
	//		ArrowComponent->bIsScreenSizeScaled = false;
	//	}
	//}
//#endif
	UnlimitedMovement = false;
	NonReversibleMovement = false;
}

void UPowerDirectionMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	//GetAttachParent();
	GetAttachParent()->SetMobility(EComponentMobility::Movable);
	
	TArray<USceneComponent*> ParentComponent = GetAttachParent()->GetAttachChildren();
	for (int i = 0; i < ParentComponent.Num(); i = i + 1)
	{
		UArrowComponent* Arrow = Cast<UArrowComponent>(ParentComponent[i]);
		if (::IsValid(Arrow) == true)
		{
			ArrowComponent = Arrow;
			ArrowComponent->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::KeepRelativeTransform);
			break;
		}
	}
	//OriginPosition = GetOwner()->GetActorLocation();
}

void UPowerDirectionMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Action(DeltaTime);
}

void UPowerDirectionMovementComponent::Action(float DeltaTime)
{
	if (ObserveTarget != nullptr)
	{
		UPowerExecutionComponent* ObserveTargetExecutionComponent = ObserveTarget->FindComponentByClass<UPowerExecutionComponent>();
		if (::IsValid(ObserveTargetExecutionComponent) == true)
		{
			if (ObserveTargetExecutionComponent->GetPowerState() == true)
			{
				CurrentMovement = FMath::Clamp<float>(CurrentMovement + (ActingSpeed * DeltaTime), 0, ActingRange);
				if ((CurrentMovement < ActingRange) || UnlimitedMovement == true)
				{
					//FVector temp = (ArrowComponent->GetForwardVector() - GetOwner()->GetActorForwardVector());
					//UE_LOG(LogTemp, Warning, TEXT("(%f, %f, %f)"), temp.X, temp.Y, temp.Z);

					//GetOwner()->AddActorLocalOffset(FVector::ForwardVector * (ActingSpeed * DeltaTime));
					GetAttachParent()->AddLocalOffset((::IsValid(ArrowComponent.Get()) == true ? Cast<USceneComponent>(ArrowComponent) : Cast<USceneComponent>(this))->GetRelativeTransform().GetUnitAxis(EAxis::X) * (ActingSpeed * DeltaTime));
				}
				//FVector MovementVector = GetOwner()->GetActorTransform().GetUnitAxis(EAxis::X) * CurrentMovement;
				//GetOwner()->SetActorLocation(OriginPosition + MovementVector);
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{
				if (NonReversibleMovement == false)
				{
					CurrentMovement = FMath::Clamp<float>(CurrentMovement - (ActingSpeed * DeltaTime), 0, ActingRange);
					if (CurrentMovement > 0)
					{
						//GetOwner()->AddActorLocalOffset(FVector::ForwardVector * (-ActingSpeed * DeltaTime));
						GetAttachParent()->AddLocalOffset((::IsValid(ArrowComponent.Get()) == true ? Cast<USceneComponent>(ArrowComponent) : Cast<USceneComponent>(this))->GetRelativeTransform().GetUnitAxis(EAxis::X) * (-ActingSpeed * DeltaTime));
					}
				}
				//FVector MovementVector = GetOwner()->GetActorTransform().GetUnitAxis(EAxis::X) * CurrentMovement;
				//GetOwner()->SetActorLocation(OriginPosition + MovementVector);
			}
		}
	}
}
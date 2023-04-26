// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerRotationMovementComponent.h"

UPowerRotationMovementComponent::UPowerRotationMovementComponent()
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
	//		//ArrowComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	//	}
	//}
//#endif

	UnlimitedMovement = false;
	NonReversibleMovement = false;
}

void UPowerRotationMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	//OriginRotation = GetOwner()->GetActorQuat().Rotator().Yaw;
	//OriginNormalVector = GetOwner()->GetActorForwardVector();
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
}

void UPowerRotationMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	Action(DeltaTime);
}

void UPowerRotationMovementComponent::Action(float DeltaTime)
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
					//GetOwner()->AddActorWorldRotation(FQuat(GetOwner()->GetActorForwardVector(), FMath::DegreesToRadians(ActingSpeed * DeltaTime)));
					//GetOwner()->AddActorLocalRotation(FQuat(FVector::ForwardVector, FMath::DegreesToRadians(ActingSpeed * DeltaTime)));
					GetAttachParent()->AddLocalRotation(FQuat((::IsValid(ArrowComponent.Get()) == true ? Cast<USceneComponent>(ArrowComponent) : Cast<USceneComponent>(this))->GetRelativeTransform().GetUnitAxis(EAxis::X), FMath::DegreesToRadians(ActingSpeed * DeltaTime)));
				}
#pragma region UnUsed
				//UE_LOG(LogTemp, Warning, TEXT("(%f)"), CurrentMovement);
				//UE_LOG(LogTemp, Warning, TEXT("(%f, %f, %f)"), GetOwner()->GetActorForwardVector().X, GetOwner()->GetActorForwardVector().Y, GetOwner()->GetActorForwardVector().Z);
				//GetOwner()->SetActorRelativeRotation(FQuat(FRotator(GetOwner()->GetActorQuat().Rotator().Pitch, OriginRotation + CurrentMovement, GetOwner()->GetActorQuat().Rotator().Roll)));
				//SetRelativeRotation(FQuat(FVector(0.0f, 0.0f, 1.0f), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
				//GetOwner()->SetActorRelativeRotation(FQuat(OriginNormalVector, FMath::DegreesToRadians(CurrentMovement)));
				//SetRelativeRotation(FQuat(GetRelativeTransform().GetUnitAxis(EAxis::Z), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
#pragma endregion
			}
			else if (ObserveTargetExecutionComponent->GetPowerState() == false)
			{
				if (NonReversibleMovement == false)
				{
					CurrentMovement = FMath::Clamp<float>(CurrentMovement - (ActingSpeed * DeltaTime), 0, ActingRange);
					if (CurrentMovement > 0)
					{
						//GetOwner()->AddActorWorldRotation(FQuat(GetOwner()->GetActorForwardVector(), FMath::DegreesToRadians(-ActingSpeed * DeltaTime)));
						//GetOwner()->AddActorLocalRotation(FQuat(FVector::ForwardVector, FMath::DegreesToRadians(-ActingSpeed * DeltaTime)));
						GetAttachParent()->AddLocalRotation(FQuat((::IsValid(ArrowComponent.Get()) == true ? Cast<USceneComponent>(ArrowComponent) : Cast<USceneComponent>(this))->GetRelativeTransform().GetUnitAxis(EAxis::X), FMath::DegreesToRadians(-ActingSpeed * DeltaTime)));
					}
				}
#pragma region UnUsed
				//GetOwner()->SetActorRelativeRotation(FQuat(FRotator(GetOwner()->GetActorQuat().Rotator().Pitch, OriginRotation + CurrentMovement, GetOwner()->GetActorQuat().Rotator().Roll)));
				//SetRelativeRotation(FQuat(FVector(0.0f, 0.0f, 1.0f), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
				//GetOwner()->SetActorRelativeRotation(FQuat(OriginNormalVector, FMath::DegreesToRadians(CurrentMovement)));
				//SetRelativeRotation(FQuat(GetRelativeTransform().GetUnitAxis(EAxis::Z), FMath::DegreesToRadians(OriginRotation + CurrentMovement)));
#pragma endregion
			}
		}
	}
}
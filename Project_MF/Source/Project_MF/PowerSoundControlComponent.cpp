// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerSoundControlComponent.h"
#include "Components/AudioComponent.h"

UPowerSoundControlComponent::UPowerSoundControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ReversAction = false;
	NonReversibleAction = false;
	LoopSound = false;
	ContinueSound = false;
	ActingSpeed = 1.0f;
	StartingPoint = 0.0f;
}

void UPowerSoundControlComponent::BeginPlay()
{
	Super::BeginPlay();

	UAudioComponent* AudioComponent = Cast<UAudioComponent>(GetAttachParent());
	if (::IsValid(AudioComponent) == true)
	{
		AudioComponent->PitchMultiplier = AudioComponent->PitchMultiplier * ActingSpeed;

		if (ReversAction == false)
		{
			if (ContinueSound == true)
			{
				AudioComponent->Play(StartingPoint);
				AudioComponent->SetPaused(!ReversAction);
			}
			else if(ContinueSound == false)
			{
				AudioComponent->Stop();
			}
		}
		else if (ReversAction == true)
		{
			if (ContinueSound == true)
			{
				AudioComponent->Play(StartingPoint);
				AudioComponent->SetPaused(!ReversAction);
			}
			else if (ContinueSound == false)
			{
				AudioComponent->Play(StartingPoint);
			}
		}
	}
}

void UPowerSoundControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Action(DeltaTime);
}

void UPowerSoundControlComponent::Action(float DeltaTime)
{
	if (::IsValid(ObserveTargetExecutionComponent.Get()) == true)
	{
		if (ObserveTargetExecutionComponent->GetPowerState() == true)
		{
			UAudioComponent* AudioComponent = Cast<UAudioComponent>(GetAttachParent());
			if (bActingState == false)
			{
				if (::IsValid(AudioComponent) == true)
				{
					if (ReversAction == false)
					{
						if (ContinueSound == true)
						{
							AudioComponent->SetPaused(ReversAction);
						}
						else if (ContinueSound == false)
						{
							AudioComponent->Play(StartingPoint);
						}
					}
					else if (ReversAction == true)
					{
						if (ContinueSound == true)
						{
							AudioComponent->SetPaused(ReversAction);
						}
						else if (ContinueSound == false)
						{
							AudioComponent->Stop();
						}
					}
				}

				if (NonReversibleAction == true)
				{
					SetComponentTickEnabled(false);
				}

				bActingState = true;
			}

			if (ReversAction == false)
			{
				if (LoopSound == true)
				{
					if (AudioComponent->GetPlayState() == EAudioComponentPlayState::Stopped)
					{
						AudioComponent->Play(StartingPoint);
					}
				}
			}
		}
		else if (ObserveTargetExecutionComponent->GetPowerState() == false)
		{
			UAudioComponent* AudioComponent = Cast<UAudioComponent>(GetAttachParent());
			if (bActingState == true)
			{
				if (NonReversibleAction == false)
				{
					if (::IsValid(AudioComponent) == true)
					{
						if (ReversAction == false)
						{
							if (ContinueSound == true)
							{
								AudioComponent->SetPaused(!ReversAction);
							}
							else if (ContinueSound == false)
							{
								AudioComponent->Stop();
							}
						}
						else if (ReversAction == true)
						{
							if (ContinueSound == true)
							{
								AudioComponent->SetPaused(!ReversAction);
							}
							else if (ContinueSound == false)
							{
								AudioComponent->Play(StartingPoint);
							}
						}
					}
				}

				bActingState = false;
			}

			if (ReversAction == true)
			{
				if (LoopSound == true)
				{
					if (AudioComponent->GetPlayState() == EAudioComponentPlayState::Stopped)
					{
						AudioComponent->Play(StartingPoint);
					}
				}
			}
		}
	}
}

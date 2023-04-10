#include "GameMapSectionComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UGameMapSectionComponent::UGameMapSectionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Range = CreateDefaultSubobject<UBoxComponent>(TEXT("RANGE"));
	Range->SetBoxExtent(FVector(100.f, 100.f, 100.f));
}


// Called when the game starts
void UGameMapSectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

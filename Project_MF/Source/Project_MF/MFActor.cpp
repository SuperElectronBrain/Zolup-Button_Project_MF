// Fill out your copyright notice in the Description page of Project Settings.


#include "MFActor.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AMFActor::AMFActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (SM_BOX.Succeeded() == true)
	{
		Mesh->SetStaticMesh(SM_BOX.Object);

		//static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
		static ConstructorHelpers::FObjectFinder<UMaterial> M_MATERIAL(TEXT("/Game/Resource/Other/Materials/M_MFMaterial.M_MFMaterial"));
		if (M_MATERIAL.Succeeded() == true)
		{
			Mesh->SetMaterial(0, M_MATERIAL.Object);
		}
	}
}

void AMFActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Mesh->SetMaterial(0, UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this));
}

// Called when the game starts or when spawned
void AMFActor::BeginPlay()
{
	Super::BeginPlay();

}

UStaticMeshComponent* AMFActor::GetMesh()
{
	return Mesh;
}

// Called every frame
void AMFActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


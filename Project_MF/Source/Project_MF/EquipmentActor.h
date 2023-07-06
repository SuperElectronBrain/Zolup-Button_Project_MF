// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "EquipmentActor.generated.h"

UCLASS(BlueprintType, Blueprintable)
class PROJECT_MF_API AEquipmentActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TObjectPtr<USceneComponent> DefaultRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true)) TObjectPtr<USkeletalMeshComponent> Mesh;

#if WITH_EDITORONLY_DATA
	UPROPERTY() TObjectPtr<UArrowComponent> ArrowComponent;
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true)) TWeakObjectPtr<AActor> EquipmentOwner;

protected:
public:	


private:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AEquipmentActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable) void Use();
	virtual void Use_Implementation() {}

	UFUNCTION(BlueprintCallable) virtual void ChangeOwner(AActor* NewOwner);
};

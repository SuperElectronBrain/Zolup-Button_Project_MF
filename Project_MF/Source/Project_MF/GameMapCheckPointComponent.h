// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameMapCheckPointComponent.generated.h"

//class USceneComponent;

UCLASS(ClassGroup = (GameMapSection), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UGameMapCheckPointComponent final : public USceneComponent
{
	GENERATED_BODY()

public:	
	////////////////////
	/// Constructor ////
	////////////////////
	UGameMapCheckPointComponent();

private:
	///////////////////////////
	//// Override methods /////
	///////////////////////////
	virtual void OnRegister() override;
	virtual void OnAttachmentChanged() override;
	virtual bool CanAttachAsChild(const USceneComponent* ChildComponent, FName SocketName) const override;
	virtual void DestroyComponent(bool bPromoteChilderen) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	///////////////////////
	/// Private methods //
	//////////////////////
	void InitConeMaterial();

	///////////////////////////////
	/// Components And Fields /////
	//////////////////////////////
	UPROPERTY()
	UStaticMeshComponent* ConeMesh;

	UPROPERTY()
	UMaterialInterface* Material;

	UPROPERTY()
	UMaterialInstanceDynamic* ConeMaterial;
	
	UPROPERTY(EditAnywhere, Category = CheckPoint, Meta = (AllowPrivateAccess = true))
	FLinearColor RGB;
		
};

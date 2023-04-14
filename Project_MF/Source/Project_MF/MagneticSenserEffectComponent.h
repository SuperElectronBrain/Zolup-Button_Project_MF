#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MagneticComponent.h"
#include "MagneticSenserComponent.h"
#include "MagneticSenserEffectComponent.generated.h"

class UMagneticComponent;
class UMagneticSenserComponent;

UCLASS( abstract )
class PROJECT_MF_API UMagneticSenserEffectComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	/*Constructor*/
	UMagneticSenserEffectComponent();

	virtual void ApplyEffect(UMagneticComponent* const magnet, UMagneticSenserComponent* const senser) PURE_VIRTUAL(UMagneticComponent::ApplyEffect,);
	virtual void ReleaseEffect(UMagneticComponent* const magnet, UMagneticSenserComponent* const senser) PURE_VIRTUAL(UMagneticComponent::ReleaseEffect, );

	/*Override methods*/
	virtual bool CanAttachAsChild(USceneComponent* ChildComponent, FName SocketName) const override { return false; }
		
};

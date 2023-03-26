// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <UMG/Public/Components/Image.h>
#include "MagneticComponent.h"
#include "PlayerUIMagneticInfoWidget.generated.h"


UCLASS()
class PROJECT_MF_API UPlayerUIMagneticInfoWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	/*Construct*/
	virtual void NativeConstruct() override;

	/*Public method*/
	void ClearInfo();
	void SetInfo(EMagneticType type1, EMagneticType type2);
	void SetInfo(UMagneticComponent* t1, UMagneticComponent* t2);

private:
	/*fields and components*/
	bool _bAvaliableImages;

	UPROPERTY()
	UImage* _magL;

	UPROPERTY()
	UImage* _magR;
	
};

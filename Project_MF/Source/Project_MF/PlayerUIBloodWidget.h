// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIBloodWidget.generated.h"

USTRUCT(BlueprintType)
struct FBloodImages
{
	GENERATED_BODY()

	TArray<class UHandlerImage*> Images;
};

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UPlayerUIBloodWidget final : public UUserWidget
{
	GENERATED_BODY()

	///////////////////////////////
	////	Public methods	   ////
	//////////////////////////////
public:
	void ShowBloodEffect(int level);

private:
	////////////////////////////////
	////	Override methods	////
	////////////////////////////////
	virtual void NativeOnInitialized() override;


	/////////////////////////////////
	///		Private methods		////
	////////////////////////////////
	void FillBloodImages(FBloodImages& level, int levelCount, int count);


	///////////////////////////////////
	////	Field and Components   ////
	///////////////////////////////////
	UPROPERTY(EditAnywhere, Category = PlayerUIBloodWidget, Meta = (AllowPrivateAccess = true), BlueprintReadWrite)
	TArray<FBloodImages> BloodEffectLevels;

	TWeakObjectPtr<class UCustomGameInstance> _Instance;
	
};

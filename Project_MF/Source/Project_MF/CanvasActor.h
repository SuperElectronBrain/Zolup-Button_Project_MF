// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "CanvasActor.generated.h"

UCLASS()
class PROJECT_MF_API ACanvasActor : public AInfo
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = UI, Meta = (AllowPrivateAccess = true)) USceneComponent* SceneComponent;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = UI, Meta = (AllowPrivateAccess = true)) TSubclassOf<class UUserWidget> CanvasClass;
public:
	UPROPERTY() UUserWidget* CanvasInstance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ACanvasActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

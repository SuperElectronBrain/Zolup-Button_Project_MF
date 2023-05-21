#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUIHandler.h"
#include "UIBlackScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MF_API UUIBlackScreenWidget final : public UUserWidget, public IGameUIHandler
{
	GENERATED_BODY()
	
public:

	virtual float GetAlpha() const override;
	virtual void SetAlpha(float newAlpha) override;

	virtual FLinearColor GetColor() const override;
	virtual void SetColor(FLinearColor newColor) override;
};

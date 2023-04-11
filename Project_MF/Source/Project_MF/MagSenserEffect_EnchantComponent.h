#pragma once

#include "CoreMinimal.h"
#include "MagneticSenserEffectComponent.h"
#include "MagSenserEffect_EnchantComponent.generated.h"

/*UMagneticSenserComponent에서, 범위에 들어온 자석에게 부여/해제시의 효과가 정의되어 있는 컴포넌트입니다.
 * 이 컴포넌트가 UMagneticSenserComponent에 부착되어 있을 경우, 범위에 들어온 자석의 자성을 최대증폭가능횟수를 
 * 증가시키고, 증폭하는 무게/자기장 범위가 정의되어있습니다.
 */
UCLASS(ClassGroup = (MagneticSenser), meta = (BlueprintSpawnableComponent))
class PROJECT_MF_API UMagSenserEffect_EnchantComponent final : public UMagneticSenserEffectComponent
{
	GENERATED_BODY()

public:
	UMagSenserEffect_EnchantComponent();

	virtual void ApplyEffect(UMagneticComponent* const magnet, UMagneticSenserComponent* const senser) override;
	virtual void ReleaseEffect(UMagneticComponent* const magnet, UMagneticSenserComponent* const senser) override;

private:
	UPROPERTY(EditAnywhere, Category = Enchanter, Meta = (AllowPrivateAccess = true, ClampMin = 1))
	int32 EnchantableCount;

	UPROPERTY(EditAnywhere, Category = Enchanter, Meta = (AllowPrivateAccess = true))
	float EnchantWeight;

	UPROPERTY(EditAnywhere, Category = Enchanter, Meta = (AllowPrivateAccess = true))
	float EnchantRange;
	
};

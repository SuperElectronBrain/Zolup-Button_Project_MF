// Fill out your copyright notice in the Description page of Project Settings.
#include "MagSenserEffect_EnchantComponent.h"

UMagSenserEffect_EnchantComponent::UMagSenserEffect_EnchantComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	EnchantableCount = 3;
	EnchantWeight = EnchantRange = 30.f;
}

void UMagSenserEffect_EnchantComponent::ApplyEffect(UMagneticComponent* const magnet, UMagneticSenserComponent* const senser)
{
	if (magnet->GetMaxEnchantableCount() < EnchantableCount)
	{
		magnet->SetEnchantInfo(EnchantableCount, EnchantWeight, EnchantRange);
	}
}

void UMagSenserEffect_EnchantComponent::ReleaseEffect(UMagneticComponent* const magnet, UMagneticSenserComponent* const senser)
{
	TArray<UMagneticSenserComponent*> magApplyList;
	UMagneticSenserComponent::GetMagnetAppliedSenserListByClass(magnet, magApplyList, UMagSenserEffect_EnchantComponent::StaticClass());

	UMagSenserEffect_EnchantComponent* max = nullptr;
	
	for (auto s : magApplyList)
	{
		UMagSenserEffect_EnchantComponent* enchanter = Cast<UMagSenserEffect_EnchantComponent>(s->GetCurrUsedEffect());
		
		//가장 높은 것을 택한다.
		if (max == nullptr || max && enchanter->EnchantableCount > max->EnchantableCount)
		{
			max = enchanter;
		}
	}

	if (max)
	{
		magnet->SetEnchantInfo(max->EnchantableCount, max->EnchantWeight, max->EnchantRange);
	}
	else {
		magnet->SetEnchantInfo(0, 0.f, 0.f);
	}
}

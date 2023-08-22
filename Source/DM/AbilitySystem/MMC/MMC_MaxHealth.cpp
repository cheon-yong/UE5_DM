// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/DMAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	DefenseDEF.AttributeToCapture = UDMAttributeSet::GetAttackAttribute();
	DefenseDEF.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DefenseDEF.bSnapshot = false;

	RelevantAttributesToCapture.Add(DefenseDEF);

}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Defense = 0.f;
	GetCapturedAttributeMagnitude(DefenseDEF, Spec, EvaluationParameters, OUT Defense);
	Defense = FMath::Max<float>(Defense, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	const int32 FinalMaxHp = PlayerLevel * 100.f;

	return FinalMaxHp;
}

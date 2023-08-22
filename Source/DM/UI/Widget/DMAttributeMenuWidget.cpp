// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/DMAttributeMenuWidget.h"
#include "AbilitySystem/DMAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "DMGameplayTags.h"

void UDMAttributeMenuWidget::BindCallbacksToDependencies()
{
}

void UDMAttributeMenuWidget::BroadcastInitialValues()
{
	UDMAttributeSet* AS = CastChecked<UDMAttributeSet>(AttributeSet);
	check(AttributeSet);

	FDMAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FDMGameplayTags::Get().Attribute_Primary_Attack);
	Info.AttributeValue = AS->GetAttack();
	AttributeInfoDelegate.Broadcast(Info);
}

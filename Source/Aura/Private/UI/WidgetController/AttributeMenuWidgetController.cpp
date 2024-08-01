// Copyright Haperkk


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGamelplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	FAuraAttributeInfo StrengthInfo = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	StrengthInfo.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(StrengthInfo);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

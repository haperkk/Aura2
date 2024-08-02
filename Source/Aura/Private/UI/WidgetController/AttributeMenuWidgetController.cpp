// Copyright Haperkk


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGamelplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (const auto& TagToAttribute : AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(TagToAttribute.Key);
		Info.AttributeValue = TagToAttribute.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
	FAuraAttributeInfo StrengthInfo = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	StrengthInfo.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(StrengthInfo);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

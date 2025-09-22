// Copyright Haperkk


#include "Input/AuraInputConfig.h"

UAuraInputConfig::UAuraInputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UAuraInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	return nullptr;
}

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
                                                                   bool bLogNotFound) const
{
	for (FAuraInputAction Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig[%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}

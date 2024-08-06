// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFunType, typename ReleasedFunType, typename HeldFunType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,PressedFunType PressedFun, ReleasedFunType ReleasedFun, HeldFunType HeldFun);
};

template <class UserClass, typename PressedFunType, typename ReleasedFunType, typename HeldFunType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFunType PressedFun, ReleasedFunType ReleasedFun, HeldFunType HeldFun)
{
	check(InputConfig);
	for (FAuraInputAction Action: InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFun)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFun, Action.InputTag);
			}
			if (ReleasedFun)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFun, Action.InputTag);
			}
			if (HeldFun)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFun, Action.InputTag);
			}
		}
	}
}

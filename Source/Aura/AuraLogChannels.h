#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"

AURA_API DECLARE_LOG_CATEGORY_EXTERN(LogAura, Log, All);
AURA_API DECLARE_LOG_CATEGORY_EXTERN(LogAuraExperience, Log, All);
AURA_API DECLARE_LOG_CATEGORY_EXTERN(LogAuraAbilitySystem, Log, All);

AURA_API FString GetClientServerContextString(UObject* ContextObject = nullptr);
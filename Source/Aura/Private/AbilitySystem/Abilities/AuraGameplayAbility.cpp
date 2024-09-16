// Copyright Haperkk


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"

FString UAuraGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s, </><Level>%d</>"), L"Default Ability Name - Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper Haper ", Level);
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Next Level: %d, </><Damage>Causes much more damage</>"), Level);
}

FString UAuraGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell Locked until Level: %d, </>"), Level);
}

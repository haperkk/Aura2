// Copyright Haperkk

#pragma once

#pragma once

#include "NativeGameplayTags.h"

namespace AuraGameplayTags
{
	AURA_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// Declare all of the custom native tags that Lyra will use
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_IsDead);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cooldown);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cost);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsBlocked);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsMissing);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Networking);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_ActivationGroup);

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Behavior_SurvivesDeath);

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Stick);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AutoRun);

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataAvailable);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataInitialized);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_GameplayReady);

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Death);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Reset);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_RequestReset);

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Damage);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Heal);

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_GodMode);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_UnlimitedHealth);

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Crouching);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_AutoRunning);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dying);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dead);

	// These are mappings from MovementMode enums to GameplayTags associated with those enums (below)
	AURA_API	extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	AURA_API	extern const TMap<uint8, FGameplayTag> CustomMovementModeTagMap;

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);

	AURA_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Custom);
}

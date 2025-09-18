// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Abilities/AuraGameplayAbility.h"
#include "AuraAbilitySystemComponent.generated.h"

//old
// DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);
// DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
// DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
// DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, int32 /*AbilityLevel*/);
// DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag& /*AbilityTag*/, const FGameplayTag& /*StatusTag*/, const FGameplayTag& /*SlotTag*/, const FGameplayTag& /*PreviousSlotTag*/);
// DECLARE_MULTICAST_DELEGATE_OneParam(FDeactivatePassiveAbility, const FGameplayTag& /*AbilityTag*/);
// DECLARE_MULTICAST_DELEGATE_TwoParams(FActivatePassiveEffect, const FGameplayTag& /*AbilityTag*/, bool /*bActivate*/);

enum class ELyraAbilityActivationGroup : uint8;
class UAuraGameplayAbility;
class UAuraAbilityTagRelationshipMapping;
/**
 * ULyraAbilitySystemComponent
 *
 *	Base ability system component class used by this project.
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	public:

	UAuraAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UActorComponent interface
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of UActorComponent interface

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	typedef TFunctionRef<bool(const UAuraGameplayAbility* LyraAbility, FGameplayAbilitySpecHandle Handle)> TShouldCancelAbilityFunc;
	void CancelAbilitiesByFunc(TShouldCancelAbilityFunc ShouldCancelFunc, bool bReplicateCancelAbility);

	void CancelInputActivatedAbilities(bool bReplicateCancelAbility);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

	bool IsActivationGroupBlocked(ELyraAbilityActivationGroup Group) const;
	void AddAbilityToActivationGroup(ELyraAbilityActivationGroup Group, UAuraGameplayAbility* LyraAbility);
	void RemoveAbilityFromActivationGroup(ELyraAbilityActivationGroup Group, UAuraGameplayAbility* LyraAbility);
	void CancelActivationGroupAbilities(ELyraAbilityActivationGroup Group, UAuraGameplayAbility* IgnoreLyraAbility, bool bReplicateCancelAbility);

	// Uses a gameplay effect to add the specified dynamic granted tag.
	void AddDynamicTagGameplayEffect(const FGameplayTag& Tag);

	// Removes all active instances of the gameplay effect that was used to add the specified dynamic granted tag.
	void RemoveDynamicTagGameplayEffect(const FGameplayTag& Tag);

	/** Gets the ability target data associated with the given ability handle and activation info */
	void GetAbilityTargetData(const FGameplayAbilitySpecHandle AbilityHandle, FGameplayAbilityActivationInfo ActivationInfo, FGameplayAbilityTargetDataHandle& OutTargetDataHandle);

	/** Sets the current tag relationship mapping, if null it will clear it out */
	void SetTagRelationshipMapping(UAuraAbilityTagRelationshipMapping* NewMapping);
	
	/** Looks at ability tags and gathers additional required and blocking tags */
	void GetAdditionalActivationTagRequirements(const FGameplayTagContainer& AbilityTags, FGameplayTagContainer& OutActivationRequired, FGameplayTagContainer& OutActivationBlocked) const;

protected:

	void TryActivateAbilitiesOnSpawn();

	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

	virtual void NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability) override;
	virtual void NotifyAbilityFailed(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason) override;
	virtual void NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, bool bWasCancelled) override;
	virtual void ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bEnableBlockTags, const FGameplayTagContainer& BlockTags, bool bExecuteCancelTags, const FGameplayTagContainer& CancelTags) override;
	virtual void HandleChangeAbilityCanBeCanceled(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bCanBeCanceled) override;

	/** Notify client that an ability failed to activate */
	UFUNCTION(Client, Unreliable)
	void ClientNotifyAbilityFailed(const UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason);

	void HandleAbilityFailed(const UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason);
protected:

	// If set, this table is used to look up tag relationships for activate and cancel
	UPROPERTY()
	TObjectPtr<UAuraAbilityTagRelationshipMapping> TagRelationshipMapping;

	// Handles to abilities that had their input pressed this frame.
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	// Handles to abilities that had their input released this frame.
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	// Handles to abilities that have their input held.
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

	// Number of abilities running in each activation group.
	int32 ActivationGroupCounts[(uint8)ELyraAbilityActivationGroup::MAX];

	//old
// public:
// 	void AbilityActorInfoSet();
//
// 	FEffectAssetTags EffectAssetTags;
// 	FAbilitiesGiven AbilitiesGivenDelegate;
// 	FAbilityStatusChanged AbilityStatusChanged;
// 	FAbilityEquipped AbilityEquipped;
// 	FDeactivatePassiveAbility DeactivatePassiveAbility;
// 	FActivatePassiveEffect ActivatePassiveEffect;
// 	
//
// 	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
// 	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
// 	bool bStartupAbilitiesGiven = false;
//
// 	void AbilityInputTagPressed(const FGameplayTag& InputTag);
// 	void AbilityInputTagHeld(const FGameplayTag& InputTag);
// 	void AbilityInputTagReleased(const FGameplayTag& InputTag);
// 	void ForEachAbility(const FForEachAbility& Delegate);
// 	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
// 	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
// 	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);
// 	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& AbilityTag);
// 	FGameplayTag GetSlotTagFromAbilityTag(const FGameplayTag& AbilityTag);
// 	bool SlotIsEmpty(const FGameplayTag& Slot);
// 	static bool AbilityHasSlot(const FGameplayAbilitySpec& AbilityTag, const FGameplayTag& Slot);
// 	static bool AbilityHasAnySlot(const FGameplayAbilitySpec& Spec);
// 	FGameplayAbilitySpec* GetSpecWithSlot(const FGameplayTag& Slot);
// 	bool IsPassiveAbility(const FGameplayAbilitySpec& Spec) const;
// 	static void AssignSlotToAbility(FGameplayAbilitySpec& Spec, const FGameplayTag& Slot);
//
// 	UFUNCTION(NetMulticast, Unreliable)
// 	void MulticastActivatePassiveEffect(const FGameplayTag& AbilityTag, bool bActivate);
//
// 	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);
//
// 	void UpgradeAttribute(const FGameplayTag& AttributeTag);
//
// 	UFUNCTION(Server, Reliable)
// 	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);
//
// 	void UpdateAbilityStatuses(int32 Level);
//
// 	UFUNCTION(Server, Reliable)
// 	void ServerSpendSpellPoint(const FGameplayTag& AbilityTag);
//
// 	UFUNCTION(Server, Reliable)
// 	void ServerEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& SlotTag);
//
// 	UFUNCTION(Client, Reliable)
// 	void ClientEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot);
//
// 	bool GetDescriptionByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription, FString& OutNextLevelDescription);
//
// 	static void ClearSlot (FGameplayAbilitySpec* AbilitySpec);
// 	void ClearAbilitiesOfSlot(const FGameplayTag& SlotTag);
// 	bool AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& SlotTag);
// protected:
//
// 	virtual void OnRep_ActivateAbilities() override;
// 	
// 	UFUNCTION(Client, Reliable)
// 	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle) const;
//
// 	UFUNCTION(Client, Reliable)
// 	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);
};

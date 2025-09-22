// Copyright Haperkk


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystem/AuraAttributeSet.h"


class UAuraHeroComponent;

UAuraGameplayAbility::UAuraGameplayAbility(const FObjectInitializer& ObjectInitializer)
{
}

UAuraAbilitySystemComponent* UAuraGameplayAbility::GetLyraAbilitySystemComponentFromActorInfo() const
{
	return nullptr;
}

AAuraPlayerController* UAuraGameplayAbility::GetLyraPlayerControllerFromActorInfo() const
{
	return nullptr;
}

AController* UAuraGameplayAbility::GetControllerFromActorInfo() const
{
	return nullptr;
}

AAuraCharacter* UAuraGameplayAbility::GetLyraCharacterFromActorInfo() const
{
	return nullptr;
}

UAuraHeroComponent* UAuraGameplayAbility::GetHeroComponentFromActorInfo() const
{
	return nullptr;
}

void UAuraGameplayAbility::TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec) const
{
}

bool UAuraGameplayAbility::CanChangeActivationGroup(EAuraAbilityActivationGroup NewGroup) const
{
	return true;
}

bool UAuraGameplayAbility::ChangeActivationGroup(EAuraAbilityActivationGroup NewGroup)
{
	return true;
}

void UAuraGameplayAbility::ClearCameraMode()
{
}

void UAuraGameplayAbility::NativeOnAbilityFailedToActivate(const FGameplayTagContainer& FailedReason) const
{
}

bool UAuraGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UAuraGameplayAbility::SetCanBeCanceled(bool bCanBeCanceled)
{
	Super::SetCanBeCanceled(bCanBeCanceled);
}

void UAuraGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
}

void UAuraGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);
}

void UAuraGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UAuraGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags);
}

void UAuraGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

FGameplayEffectContextHandle UAuraGameplayAbility::MakeEffectContext(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo) const
{
	return Super::MakeEffectContext(Handle, ActorInfo);
}

void UAuraGameplayAbility::ApplyAbilityTagsToGameplayEffectSpec(FGameplayEffectSpec& Spec,
	FGameplayAbilitySpec* AbilitySpec) const
{
	Super::ApplyAbilityTagsToGameplayEffectSpec(Spec, AbilitySpec);
}

bool UAuraGameplayAbility::DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::DoesAbilitySatisfyTagRequirements(AbilitySystemComponent, SourceTags, TargetTags,
	                                                OptionalRelevantTags);
}

void UAuraGameplayAbility::OnPawnAvatarSet()
{
}

void UAuraGameplayAbility::GetAbilitySource(FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, float& OutSourceLevel,
	const IAuraAbilitySourceInterface*& OutAbilitySource, AActor*& OutEffectCauser) const
{
}


//old
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
	return FString::Printf(TEXT("<Default>Spell Locked until Level: %d </>"), Level);
}

float UAuraGameplayAbility::GetManaCost(float Level) const
{
	float ManaCost = 0.f;
	if (const UGameplayEffect* CostEffect =  GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
		{
			if (Mod.Attribute == UAuraAttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(Level, ManaCost);
				break;
			}
		}
	}
	return ManaCost;
}

float UAuraGameplayAbility::GetCooldown(float Level) const
{
	float Cooldown = 0.f;
	if (const UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect())
	{	
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(Level, Cooldown);
	}
	return Cooldown;
}

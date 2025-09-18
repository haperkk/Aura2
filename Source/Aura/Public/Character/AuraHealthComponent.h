// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "AuraHealthComponent.generated.h"

class UAuraHealthSet;
class UAuraAbilitySystemComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAuraHealth_DeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FAuraHealth_AttributeChanged, UAuraHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

/**
 * ELyraDeathState
 *
 *	Defines current state of death.
 */
UENUM(BlueprintType)
enum class ELyraDeathState : uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class AURA_API UAuraHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	UAuraHealthComponent(const FObjectInitializer& ObjectInitializer);

	// Returns the health component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "Lyra|Health")
	static UAuraHealthComponent* FindHealthComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UAuraHealthComponent>() : nullptr); }

	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Health")
	void InitializeWithAbilitySystem(UAuraAbilitySystemComponent* InASC);

	// Uninitialize the component, clearing any references to the ability system.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Health")
	void UninitializeFromAbilitySystem();

	// Returns the current health value.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Health")
	float GetHealth() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Health")
	float GetMaxHealth() const;

	// Returns the current health in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "Lyra|Health")
	float GetHealthNormalized() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Health")
	ELyraDeathState GetDeathState() const { return DeathState; }

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Lyra|Health", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	bool IsDeadOrDying() const { return (DeathState > ELyraDeathState::NotDead); }

	// Begins the death sequence for the owner.
	virtual void StartDeath();

	// Ends the death sequence for the owner.
	virtual void FinishDeath();

	// Applies enough damage to kill the owner.
	virtual void DamageSelfDestruct(bool bFellOutOfWorld = false);

public:
	// Delegate fired when the health value has changed.
	UPROPERTY(BlueprintAssignable)
	FAuraHealth_AttributeChanged OnHealthChanged;

	// Delegate fired when the max health value has changed.
	UPROPERTY(BlueprintAssignable)
	FAuraHealth_AttributeChanged OnMaxHealthChanged;

	// Delegate fired when the death sequence has started.
	UPROPERTY(BlueprintAssignable)
	FAuraHealth_DeathEvent OnDeathStarted;

	// Delegate fired when the death sequence has finished.
	UPROPERTY(BlueprintAssignable)
	FAuraHealth_DeathEvent OnDeathFinished;

protected:
	virtual void OnUnregister() override;

	void ClearGameplayTags();

	virtual void HandleHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);

	UFUNCTION()
	virtual void OnRep_DeathState(ELyraDeathState OldDeathState);

protected:
	// Ability system used by this component. 由character的OnAbilitySystemInitialized方法传递下来
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;

	// Health set used by this component.
	UPROPERTY()
	TObjectPtr<const UAuraHealthSet> HealthSet;

	// Replicated state used to handle dying.
	UPROPERTY(ReplicatedUsing = OnRep_DeathState)
	ELyraDeathState DeathState;
};

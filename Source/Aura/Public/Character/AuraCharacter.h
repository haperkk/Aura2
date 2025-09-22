// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AuraCharacter.generated.h"

class UAuraHealthComponent;
class UAuraAbilitySystemComponent;
class AAuraPlayerState;
class AAuraPlayerController;
class UAuraPawnExtensionComponent;
/**
 * ALyraCharacter
 *
 *	The base character pawn class used by this project.
 *	Responsible for sending events to pawn components.
 *	New behavior should be added via pawn components when possible.
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface, public IGameplayCueInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	AAuraCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//~begin of get function
	UFUNCTION(BlueprintCallable, Category = "Lyra|Character")
	AAuraPlayerController* GetAuraPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Character")
	AAuraPlayerState* GetAuraPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "Lyra|Character")
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent() const;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	//~end of get function

	//~begin of override of UGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	//

	//~begin AActor interface
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Reset() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
	//~end AActor interface

	//~Begin APawn interface
	virtual void NotifyControllerChanged() override;
	//~End APawn interface

	/* begin Player Interface */
	// virtual void AddToXP_Implementation(int32 InXP) override;
	// virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	// virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	// virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	// virtual void LevelUp_Implementation() override;	
	// virtual int32 GetXP_Implementation() const override;
	// virtual int32 GetAttributePointsReward_Implementation(int32 Level) const override;
	// virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;
	// virtual int32 GetAttributePoints_Implementation() const override;
	// virtual int32 GetSpellPoints_Implementation() const override;
	// virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	// virtual void SaveProgress_Implementation(const FName& CheckpointTag) override;
	// /* end Player Interface */
	//
	// /* begin Combat Interface */
	// virtual int32 GetPlayerLevel_Implementation() const override;
	/* end Combat Interface */
	

	//~begin old code
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;
	//
	// virtual void OnRep_Stunned() override;
	// virtual void OnRep_Burned() override;
	//
	// void LoadProgress();

	//~end old code
	
protected:

	virtual void OnAbilitySystemInitialized();
	virtual void OnAbilitySystemUninitialized();

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	virtual void OnRep_Controller() override;
	virtual void OnRep_PlayerState() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void InitializeGameplayTags();

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	// Begins the death sequence for the character (disables collision, disables movement, etc...)
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	void DisableMovementAndCollision();
	void DestroyDueToDeath();
	void UnInitAndDestroy();

	// Called when the death sequence for the character has completed
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnDeathFinished"))
	void K2_OnDeathFinished();

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	void SetMovementModeTag(EMovementMode MovementMode, uint8 CustomMovementMode, bool bTagEnabled);
	
	//old
	// virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	
private:
	//~begin old
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aura|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAuraHealthComponent> HealthComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	// virtual void InitAbilityActorInfo() override;

	// UFUNCTION(NetMulticast, Reliable)
	// void MulticastLevelUpParticles();
	//~end old

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAuraPawnExtensionComponent> PawnExtComponent;

	
};

// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ModularGameState.h"
#include "AuraGameState.generated.h"

class UAuraExperienceManagerComponent;
class UAuraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameState : public AModularGameState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	
public:

	AAuraGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	float GetServerFPS() const { return ServerFPS; }

	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

	//~AGameStateBase interface
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
	virtual void SeamlessTravelTransitionCheckpoint(bool bToTransitionMap) override;
	//~End of AGameStateBase interface

	//~IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End of IAbilitySystemInterface

	UFUNCTION(BlueprintCallable, Category = "Lyra|GameState")
	UAuraAbilitySystemComponent* GetLyraAbilitySystemComponent() const { return AbilitySystemComponent; }

	// // Send a message that all clients will (probably) get
	// // (use only for client notifications like eliminations, server join messages, etc... that can handle being lost)
	// UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "Lyra|GameState")
	// void MulticastMessageToClients(const FAuraVerbMessage Message);
	//
	// // Send a message that all clients will be guaranteed to get
	// // (use only for client notifications that cannot handle being lost)
	// UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Lyra|GameState")
	// void MulticastReliableMessageToClients(const FLyraVerbMessage Message);

private:
	UPROPERTY()
	TObjectPtr<UAuraExperienceManagerComponent> ExperienceManagerComponent;

	// The ability system component subobject for game-wide things (primarily gameplay cues)
	UPROPERTY(VisibleAnywhere, Category = "Lyra|GameState")
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;


protected:

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(Replicated)
	float ServerFPS;
};

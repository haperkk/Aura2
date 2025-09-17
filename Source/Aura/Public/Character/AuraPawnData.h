// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AuraPawnData.generated.h"

class UAuraAbilitySet;
class UAuraAbilityTagRelationshipMapping;
/**
 * 
 */
UCLASS()
class AURA_API UAuraPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UAuraPawnData(const FObjectInitializer& ObjectInitializer);
	
	// Class to instantiate for this pawn (should usually derive from ALyraPawn or ALyraCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Pawn")
	TSubclassOf<APawn> PawnClass;

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Abilities")
	TArray<TObjectPtr<UAuraAbilitySet>> AbilitySets;

	// What mapping of ability tags to use for actions taking by this pawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Abilities")
	TObjectPtr<UAuraAbilityTagRelationshipMapping> TagRelationshipMapping;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	//暂时不需要改变相机
	// Default camera mode used by player controlled pawns.
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Camera")
	// TSubclassOf<ULyraCameraMode> DefaultCameraMode;
};

// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	/* begin Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	/* end Enemy Interface */

	/* begin Combat Interface */
	virtual int32 GetPlayerLevel() const override;
	/* end Combat Interface */
	
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults") 
	int32 Level = 1;
};

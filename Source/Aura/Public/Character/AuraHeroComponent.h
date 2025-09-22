// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "AuraHeroComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraHeroComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAuraHeroComponent(const FObjectInitializer& ObjectInitializer);
};

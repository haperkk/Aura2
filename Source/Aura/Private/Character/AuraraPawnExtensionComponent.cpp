// Copyright Haperkk


#include "Character/AuraraPawnExtensionComponent.h"


const FName UAuraraPawnExtensionComponent::NAME_ActorFeatureName("PawnExtension");

// Sets default values for this component's properties
UAuraraPawnExtensionComponent::UAuraraPawnExtensionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


UAuraraPawnExtensionComponent::UAuraraPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
{
}

// Called when the game starts
void UAuraraPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAuraraPawnExtensionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


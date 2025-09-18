// Copyright Haperkk


#include "AuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "OldAuraGamelplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FOldAuraGameplayTags::InitializeNativeGameplayTags();
	//This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}

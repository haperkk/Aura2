// Copyright Haperkk


#include "System/AuraGameData.h"

#include "AuraAssetManager.h"

UAuraGameData::UAuraGameData()
{
}

const UAuraGameData& UAuraGameData::Get()
{
	return UAuraAssetManager::Get().GetGameData();
}

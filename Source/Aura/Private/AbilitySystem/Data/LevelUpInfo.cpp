// Copyright Haperkk


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)
{
	int32 level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= level) return level;
		if (XP >= LevelUpInformation[level].LevelUpRequirement)
		{
			++level;
		}
		else
		{
			bSearching = false;
		}
	}
	return level;
}

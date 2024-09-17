// Copyright Haperkk


#include "AbilitySystem/Abilities/AuraFireBolt.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScalarDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Launches a bolt of fire, exploding on impact and dealing: </><Damage>%d</><Default>damage with a chance to burn</>"
			),
			Level,
			ManaCost,
			Cooldown,
			ScalarDamage
			);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Launches %d bolt of fire, exploding on impact and dealing: </><Damage>%d</><Default>damage with a chance to burn</>"
			),
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScalarDamage
			);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScalarDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL</>\n\n"
		"<Small>Level: </><Level>%d</>\n"
		"<Small>Mana Cost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Launches %d bolt of fire, exploding on impact and dealing: </><Damage>%d</><Default>damage with a chance to burn</>"
		),
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScalarDamage
		);
}
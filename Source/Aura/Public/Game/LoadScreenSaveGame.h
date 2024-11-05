// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

UENUM()
enum ESaveSlotStatus
{
	Vacant,
	EnterName,
	Taken
};


/**
 * 
 */
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SlotName = FString();

	UPROPERTY()
	int32 SlotIndex =0;

	UPROPERTY()
	FString PlayerName = FString("Default Player Name");

	UPROPERTY()
	FString MapName = FString("Default Map Name");

	UPROPERTY()
	FName PlayerStartTag;

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;

	UPROPERTY()
	bool bFirstTimeLoadIn = true;
	
	/*Player*/
	UPROPERTY()
	int32 PlayerLevel = 0;

	UPROPERTY()
	int32 XP = 0;

	UPROPERTY()
	int32 SpellPoints = 0;

	UPROPERTY()
	int32 AttributePoints = 0;

	/*Attributes*/
	UPROPERTY()
	int32 Strength = 0;

	UPROPERTY()
	int32 Intelligence = 0;

	UPROPERTY()
	int32 Resilience = 0;
	
	UPROPERTY()
	int32 Vigor = 0;
};

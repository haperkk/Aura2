// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FAuraGameplayTags
{
public:
static const FAuraGameplayTags& Get() {return GameplayTags;}
protected:
static void InitializeNativeGameplayTags();
private:
 static FAuraGameplayTags GameplayTags;
};
// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwicherIndex, int32, WidgetSwitcherIndex);

/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwicherIndex SetWidgetSwitcherIndex;


	void InitializeSlot();

	UPROPERTY()
	FString PlayerName;
	
	UPROPERTY()
	FString LoadSlotName;

	UPROPERTY()
	int32 LoadIndex;
};

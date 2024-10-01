// Copyright Haperkk

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/LoadScreenSaveGame.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwicherIndex, int32, WidgetSwitcherIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButton, bool, bEnable);

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

	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButton EnableSelectSlotButton;


	void InitializeSlot();

	
	
	UPROPERTY()
	FString LoadSlotName;

	UPROPERTY()
	int32 SlotIndex;

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SlotStatus;
	
	/* Field Notifies */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	FString PlayerName;

	void SetPlayerName(const FString& InPlayerName);

	FString GetPlayerName() const { return PlayerName;};
};

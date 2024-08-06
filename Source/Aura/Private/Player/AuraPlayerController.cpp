// Copyright Haperkk


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2d InputAxis2D = Value.Get<FVector2d>();
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxis2D.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxis2D.X);
	}
	
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/*
	 * Line Trace from cursor. There are several scenarios:
	 *  A. Last Actor is null && This Actor is null
	 *		- Do nothing
	 *	B. Last Actor is null && This Actor is not null
	 *		-Highlight This Actor
	 *	C. Last Actor is not null && This Actor is null
	 *		 -Unhighlight Last Actor
	 *	D. Last Actor is not null && This Actor is not null && Last Actor != This Actor
	 *		 -Unhighlight Last Actor and Highlight This Actor
	 *	E. Last Actor is not null && This Actor is not null && Last Actor == This Actor
	 *		 -Do nothing
	 */
	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr)
		{
			//A - Do nothing
		}
		else
		{
			//B - Highlight This Actor
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			//C - Unhighlight Last Actor
			LastActor->UnhighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				//D - Unhighlight Last Actor and Highlight This Actor
				LastActor->UnhighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//E - Do nothing
			}
		}
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Green, *InputTag.ToString());
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Blue, *InputTag.ToString());
}

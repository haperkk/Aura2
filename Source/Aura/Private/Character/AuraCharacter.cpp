// Copyright Haperkk


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "OldAuraGamelplayTags.h"
#include "SignificanceManager.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Character/AuraCharacterMovementComponent.h"
#include "Character/AuraHealthComponent.h"
#include "Character/AuraPawnExtensionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Game/AuraGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

static FName NAME_AuraCharacterCollisionProfile_Capsule(TEXT("AuraPawnCapsule"));
static FName NAME_AuraCharacterCollisionProfile_Mesh(TEXT("AuraPawnMesh"));

AAuraCharacter::AAuraCharacter(const FObjectInitializer& ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>("TopDownCameraComponent");
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	//
	//
	// LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	// LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	// LevelUpNiagaraComponent->bAutoActivate = false;
	//
	// GetCharacterMovement()->bOrientRotationToMovement = true;
	// GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// GetCharacterMovement()->bConstrainToPlane = true;
	// GetCharacterMovement()->bSnapToPlaneAtStart = true;
	//
	// bUseControllerRotationPitch = false;
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;
	//
	// CharacterClass = ECharacterClass::Elementalist;

	// Avoid ticking characters if possible.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	NetCullDistanceSquared = 900000000.0f;
	
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);
	CapsuleComp->SetCollisionProfileName(NAME_AuraCharacterCollisionProfile_Capsule);

	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));  // Rotate mesh to be X forward since it is exported as Y forward.
	MeshComp->SetCollisionProfileName(NAME_AuraCharacterCollisionProfile_Mesh);

	UAuraCharacterMovementComponent* AuraMoveComp = CastChecked<UAuraCharacterMovementComponent>(GetCharacterMovement());
	AuraMoveComp->GravityScale = 1.0f;
	AuraMoveComp->MaxAcceleration = 2400.0f;
	AuraMoveComp->BrakingFrictionFactor = 1.0f;
	AuraMoveComp->BrakingFriction = 6.0f;
	AuraMoveComp->GroundFriction = 8.0f;
	AuraMoveComp->BrakingDecelerationWalking = 1400.0f;
	AuraMoveComp->bUseControllerDesiredRotation = false;
	AuraMoveComp->bOrientRotationToMovement = false;
	AuraMoveComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	AuraMoveComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
	
	PawnExtComponent = CreateDefaultSubobject<UAuraPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemInitialized));
	PawnExtComponent->OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemUninitialized));

	HealthComponent = CreateDefaultSubobject<UAuraHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);

	// CameraComponent = CreateDefaultSubobject<UAuraCameraComponent>(TEXT("CameraComponent"));
	// CameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 75.0f));
}

AAuraPlayerController* AAuraCharacter::GetAuraPlayerController() const
{
	return CastChecked<AAuraPlayerController>(Controller, ECastCheckedType::NullAllowed);
}

AAuraPlayerState* AAuraCharacter::GetAuraPlayerState() const
{
	return CastChecked<AAuraPlayerState>(GetPlayerState(), ECastCheckedType::NullAllowed);
}

UAuraAbilitySystemComponent* AAuraCharacter::GetAuraAbilitySystemComponent() const
{
	return CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* AAuraCharacter::GetAbilitySystemComponent() const
{
	return PawnExtComponent->GetAuraAbilitySystemComponent();
}

void AAuraCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (const UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent())
	{
		AuraASC->GetOwnedGameplayTags(TagContainer);
	}
}

bool AAuraCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	if (const UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent())
	{
		return AuraASC->HasMatchingGameplayTag(TagToCheck);
	}

	return false;
}

bool AAuraCharacter::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent())
	{
		return AuraASC->HasAllMatchingGameplayTags(TagContainer);
	}

	return false;
}

bool AAuraCharacter::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent())
	{
		return AuraASC->HasAnyMatchingGameplayTags(TagContainer);
	}

	return false;
}

void AAuraCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UWorld* World = GetWorld();

	const bool bRegisterWithSignificanceManager = !IsNetMode(NM_DedicatedServer);
	if (bRegisterWithSignificanceManager)
	{
		if (USignificanceManager* SignificanceManager = USignificanceManager::Get(World))
		{
			//todo: what's this
			SignificanceManager->UnregisterObject(this);
		}
	}
}

//todo: why not super::reset()? 在UnInitAndDestroy做了pawn中reset的DetachFromControllerPendingDestroy， 而K2_OnReset是Actor的reset内容，所以这里是规避pawn中的destroy()?
void AAuraCharacter::Reset()
{
	DisableMovementAndCollision();

	K2_OnReset();

	UnInitAndDestroy();
}

//todo
void AAuraCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// DOREPLIFETIME_CONDITION(ThisClass, ReplicatedAcceleration, COND_SimulatedOnly);
	// DOREPLIFETIME(ThisClass, MyTeamID)
}

//todo
void AAuraCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);
}


//todo: some team functionality in it, see lyra souce code
void AAuraCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/*old code*/
	// Init ability actor info for the server
	// InitAbilityActorInfo();
	// LoadProgress();

	//转发给pawnExt
	PawnExtComponent->HandleControllerChanged();
}

// void AAuraCharacter::LoadProgress()
// {
// 	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
// 	if (AuraGameMode)
// 	{
// 		ULoadScreenSaveGame* SaveData = AuraGameMode->RetrieveInGameSaveData();
// 		if (SaveData == nullptr) return;
// 		
// 		if (SaveData->bFirstTimeLoadIn)
// 		{
// 			InitializeDefaultAttributes();
// 			AddCharacterAbilities();
// 		}
// 		else
// 		{
// 			//Todo Load in Abilities from disk
// 			if (AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(GetPlayerState()))
// 			{
// 				AuraPlayerState->SetLevel(SaveData->PlayerLevel);
// 				AuraPlayerState->SetXP(SaveData->XP);
// 				AuraPlayerState->SetAttributePoints(SaveData->AttributePoints);
// 				AuraPlayerState->SetSpellPoints(SaveData->SpellPoints);
// 			}
// 			UAuraAbilitySystemLibrary::InitializeDefaultAttributesFromSaveData(this, AbilitySystemComponent, SaveData);
// 		}
// 	}
// }

void AAuraCharacter::OnAbilitySystemInitialized()
{
	UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent();
	check(AuraASC);

	HealthComponent->InitializeWithAbilitySystem(AuraASC);

	InitializeGameplayTags();
}

void AAuraCharacter::OnAbilitySystemUninitialized()
{
	HealthComponent->UninitializeFromAbilitySystem();
}

//todo: some team functionality in it, see lyra souce code
void AAuraCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void AAuraCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	PawnExtComponent->HandleControllerChanged();
}

void AAuraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PawnExtComponent->SetupPlayerInputComponent();
}

void AAuraCharacter::InitializeGameplayTags()
{
	// Clear tags that may be lingering on the ability system from the previous pawn.
	if (UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent())
	{
		for (const TPair<uint8, FGameplayTag>& TagMapping : AuraGameplayTags::MovementModeTagMap)
		{
			if (TagMapping.Value.IsValid())
			{
				AuraASC->SetLooseGameplayTagCount(TagMapping.Value, 0);
			}
		}

		for (const TPair<uint8, FGameplayTag>& TagMapping : AuraGameplayTags::CustomMovementModeTagMap)
		{
			if (TagMapping.Value.IsValid())
			{
				AuraASC->SetLooseGameplayTagCount(TagMapping.Value, 0);
			}
		}

		UAuraCharacterMovementComponent* AuraMoveComp = CastChecked<UAuraCharacterMovementComponent>(GetCharacterMovement());
		SetMovementModeTag(AuraMoveComp->MovementMode, AuraMoveComp->CustomMovementMode, true);
	}
}

void AAuraCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	HealthComponent->DamageSelfDestruct(true);
}

void AAuraCharacter::OnDeathStarted(AActor* OwningActor)
{
	DisableMovementAndCollision();
}

void AAuraCharacter::OnDeathFinished(AActor* OwningActor)
{
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::DestroyDueToDeath);
}

void AAuraCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	UAuraCharacterMovementComponent* LyraMoveComp = CastChecked<UAuraCharacterMovementComponent>(GetCharacterMovement());

	SetMovementModeTag(PrevMovementMode, PreviousCustomMode, false);
	SetMovementModeTag(LyraMoveComp->MovementMode, LyraMoveComp->CustomMovementMode, true);
}

void AAuraCharacter::SetMovementModeTag(EMovementMode MovementMode, uint8 CustomMovementMode, bool bTagEnabled)
{
	if (UAuraAbilitySystemComponent* AuraASC = GetAuraAbilitySystemComponent())
	{
		const FGameplayTag* MovementModeTag = nullptr;
		if (MovementMode == MOVE_Custom)
		{
			MovementModeTag = AuraGameplayTags::CustomMovementModeTagMap.Find(CustomMovementMode);
		}
		else
		{
			MovementModeTag = AuraGameplayTags::MovementModeTagMap.Find(MovementMode);
		}

		if (MovementModeTag && MovementModeTag->IsValid())
		{
			AuraASC->SetLooseGameplayTagCount(*MovementModeTag, (bTagEnabled ? 1 : 0));
		}
	}
}

void AAuraCharacter::DisableMovementAndCollision()
{
	if (Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	UAuraCharacterMovementComponent* AuraMoveComp = CastChecked<UAuraCharacterMovementComponent>(GetCharacterMovement());
	AuraMoveComp->StopMovementImmediately();
	AuraMoveComp->DisableMovement();
}

void AAuraCharacter::DestroyDueToDeath()
{
	K2_OnDeathFinished();

	UnInitAndDestroy();
}

void AAuraCharacter::UnInitAndDestroy()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		DetachFromControllerPendingDestroy();

		//todo:为什么不直接destroy，还要等0.1f?中间还有其他事情需要完成吗,是要给0.1s用来PawnExtComponent->UninitializeAbilitySystem()？如果是这样为什么不用委托来通知destroy
		SetLifeSpan(0.1f);
	}

	// Uninitialize the ASC if we're still the avatar actor (otherwise another pawn already did it when they became the avatar actor)
	if (UAuraAbilitySystemComponent* LyraASC = GetAuraAbilitySystemComponent())
	{
		if (LyraASC->GetAvatarActor() == this)
		{
			PawnExtComponent->UninitializeAbilitySystem();
		}
	}

	SetActorHiddenInGame(true);
}


void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	PawnExtComponent->HandlePlayerStateReplicated();
	
	//old
	// Init ability actor info for the Client
	// InitAbilityActorInfo();
}

// void AAuraCharacter::AddToXP_Implementation(int32 InXP)
// {
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	AuraPlayerState->AddToXP(InXP);
// }
//
// void AAuraCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
// {
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	AuraPlayerState->AddToAttributePoints(InAttributePoints);
// }
//
// void AAuraCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
// {
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	AuraPlayerState->AddToSpellPoints(InSpellPoints);
// }
//
// void AAuraCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
// {
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	AuraPlayerState->AddToLevel(InPlayerLevel);
// 	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent()))
// 	{
// 		AuraASC->UpdateAbilityStatuses(AuraPlayerState->GetPlayerLevel());
// 	}
// }
//
// int32 AAuraCharacter::GetAttributePointsReward_Implementation(int32 Level) const
// {
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	return AuraPlayerState->LevelUpInfo->LevelUpInformation[Level].AttributePointAward;
// }
//
// int32 AAuraCharacter::GetSpellPointsReward_Implementation(int32 Level) const
// {
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	return AuraPlayerState->LevelUpInfo->LevelUpInformation[Level].SpellPointAward;
// }
//
// int32 AAuraCharacter::GetAttributePoints_Implementation() const
// {
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	return AuraPlayerState->GetAttributePoints();
// }
//
// int32 AAuraCharacter::GetSpellPoints_Implementation() const
// {
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	return AuraPlayerState->GetSpellPoints();
// }
//
// void AAuraCharacter::LevelUp_Implementation()
// {
// 	MulticastLevelUpParticles();
// }
//
// void AAuraCharacter::MulticastLevelUpParticles_Implementation()
// {
// 	if (IsValid(LevelUpNiagaraComponent))
// 	{
// 		const FVector CameraLoaction = TopDownCameraComponent->GetComponentLocation();
// 		const FVector NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
// 		const FRotator ToCameraRotation = (CameraLoaction - NiagaraSystemLocation).Rotation();
// 		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
// 		LevelUpNiagaraComponent->Activate(true);
// 	}
// }
//
//
// int32 AAuraCharacter::GetXP_Implementation() const
// {
// 	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	return AuraPlayerState->GetXP();
// }
//
// int32 AAuraCharacter::FindLevelForXP_Implementation(int32 InXP) const
// {
// 	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	return AuraPlayerState->LevelUpInfo->FindLevelForXP(InXP);
// }
//
// void AAuraCharacter::SaveProgress_Implementation(const FName& CheckpointTag)
// {
// 	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
// 	if (AuraGameMode)
// 	{
// 		ULoadScreenSaveGame* SaveData = AuraGameMode->RetrieveInGameSaveData();
// 		if (SaveData == nullptr) return;
//
// 		SaveData->PlayerStartTag = CheckpointTag;
// 		if (AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(GetPlayerState()))
// 		{
// 			SaveData->PlayerLevel = AuraPlayerState->GetPlayerLevel();
// 			SaveData->XP = AuraPlayerState->GetXP();
// 			SaveData->AttributePoints = AuraPlayerState->GetAttributePoints();
// 			SaveData->SpellPoints = AuraPlayerState->GetSpellPoints();
// 		}
// 		SaveData->Strength = UAuraAttributeSet::GetStrengthAttribute().GetNumericValue(GetAttributeSet());
// 		SaveData->Intelligence = UAuraAttributeSet::GetIntelligenceAttribute().GetNumericValue(GetAttributeSet());
// 		SaveData->Resilience = UAuraAttributeSet::GetResilienceAttribute().GetNumericValue(GetAttributeSet());
// 		SaveData->Vigor = UAuraAttributeSet::GetVigorAttribute().GetNumericValue(GetAttributeSet());
// 		SaveData->bFirstTimeLoadIn = false;
// 		AuraGameMode->SaveInGameProgressData(SaveData);
// 	}
// }
//
// int32 AAuraCharacter::GetPlayerLevel_Implementation() const
// {
// 	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	return AuraPlayerState->GetPlayerLevel();
// }
//
// void AAuraCharacter::OnRep_Stunned()
// {
// 	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
// 	{
// 		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
// 		FGameplayTagContainer BlockedTags;
// 		BlockedTags.AddTag(GameplayTags.Player_Block_CursorTrace);
// 		BlockedTags.AddTag(GameplayTags.Player_Block_InputPressed);
// 		BlockedTags.AddTag(GameplayTags.Player_Block_InputReleased);
// 		BlockedTags.AddTag(GameplayTags.Player_Block_InputHeld);
// 		if (bIsStunned)
// 		{
// 			AuraASC->AddLooseGameplayTags(BlockedTags);
// 			StunDebuffComponent->Activate();
// 		}
// 		else
// 		{
// 			AuraASC->RemoveLooseGameplayTags(BlockedTags);
// 			StunDebuffComponent->Deactivate();
// 		}
// 	}
// }
//
// void AAuraCharacter::OnRep_Burned()
// {
// 	if (bIsStunned)
// 	{
// 		StunDebuffComponent->Activate();
// 	}
// 	else
// 	{
// 		StunDebuffComponent->Deactivate();
// 	}
// }
//
// void AAuraCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
// {
// 	Super::StunTagChanged(CallbackTag, NewCount);
// }
//
// void AAuraCharacter::InitAbilityActorInfo()
// {
// 	// Init AbilityActorInfo and Set AbilitySystemComponent, AttributeSet
// 	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
// 	check(AuraPlayerState);
// 	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
// 	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
// 	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
// 	AttributeSet = AuraPlayerState->GetAttributeSet();
// 	OnASCRegistered.Broadcast(AbilitySystemComponent);
// 	AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AAuraCharacter::StunTagChanged);
// 	
// 	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
// 	{
// 		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
// 		{
// 			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
// 		}
// 	}
// 	//without loadprogress we need to add the startup abilities here
// 	AddCharacterAbilities();
// 	InitializeDefaultAttributes();
// }


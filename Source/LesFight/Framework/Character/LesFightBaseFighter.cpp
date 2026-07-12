#include "LesFightBaseFighter.h"
#include "LesFightHealthComponent.h"
#include "LesFightStaminaComponent.h"
#include "LesFightAnimationComponent.h"
#include "LesFightAudioComponent.h"
#include "LesFightStatisticsComponent.h"
#include "LesFightAppearanceComponent.h"
#include "LesFightInteractionComponent.h"
#include "LesFightCharacterProgression.h"
#include "LesFightFighterDataAsset.h"
#include "LesFightCharacterMovementComponent.h"
#include "LesFightCombatComponent.h"
#include "LesFightCombatDataAsset.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimationDataAsset.h"
#include "Orchestration/LesFightMartialArtsManager.h"
#include "Styles/LesFightStyleManager.h"
#include "LesFight.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALesFightBaseFighter::ALesFightBaseFighter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , bFighterInitialized(false)
    , PlayerIndex(-1)
    , OwnerPlayerIndex(-1)
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    CreateComponents();
}

void ALesFightBaseFighter::BeginPlay()
{
    Super::BeginPlay();

    if (DefaultFighterData)
    {
        InitializeFighter(DefaultFighterData);
    }

    if (CombatComponent)
    {
        CombatComponent->Initialize(this, DefaultCombatData);
    }

    if (CharacterAnimComponent)
    {
        CharacterAnimComponent->Initialize(this, DefaultAnimationData);
    }

    if (MartialArtsManager)
    {
        MartialArtsManager->InitializeWithOwner(this);
    }

    BindComponentEvents();
    UE_LOG(LogLesFight, Log, TEXT("BaseFighter initialized: %s"), *GetName());
}

void ALesFightBaseFighter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALesFightBaseFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALesFightBaseFighter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
}

float ALesFightBaseFighter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    if (HealthComponent)
    {
        return HealthComponent->TakeDamage(DamageAmount, DamageCauser);
    }
    return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ALesFightBaseFighter::InitializeFighter(ULesFightFighterDataAsset* FighterData)
{
    if (!FighterData || bFighterInitialized) return;

    ApplyFighterData(FighterData->FighterData);

    UE_LOG(LogLesFight, Log, TEXT("Fighter initialized: %s (%s)"), *FighterName, *FighterID.ToString());

    bFighterInitialized = true;
    OnFighterInitialized.Broadcast(FighterID);
}

void ALesFightBaseFighter::ApplyFighterData(const FCharacterTableRow& Data)
{
    Identity = Data.Identity;
    PhysicalAttributes = Data.Physical;
    MovementAttributes = Data.Movement;
    CombatAttributes = Data.Combat;
    ResourceAttributes = Data.Resources;

    FighterID = Data.Identity.CharacterID;
    FighterName = Data.Identity.CharacterName;
    DisplayName = Data.Identity.Nickname.IsEmpty()
        ? Data.Identity.CharacterName : Data.Identity.Nickname;

    if (HealthComponent)
    {
        HealthComponent->Initialize(Data.Resources.MaxHealth);
    }

    if (StaminaComponent)
    {
        StaminaComponent->Initialize(Data.Resources.MaxStamina, Data.Resources.StaminaRecoveryRate);
    }

    if (StatisticsComponent)
    {
        StatisticsComponent->Initialize(Data.Combat, Data.Movement, Data.Resources);
    }

    if (AnimationComponent && GetMesh())
    {
        AnimationComponent->Initialize(GetMesh());
    }

    if (AudioComponent)
    {
        AudioComponent->Initialize(
            Data.Audio.FootstepSounds,
            Data.Audio.BreathingSounds,
            Data.Audio.GruntSounds,
            Data.Audio.VictoryVoice.LoadSynchronous(),
            Data.Audio.DefeatVoice.LoadSynchronous(),
            Data.Audio.TauntSounds
        );
    }

    if (AppearanceComponent && GetMesh())
    {
        AppearanceComponent->Initialize(GetMesh(), Data.Cosmetics);
    }

    if (Progression)
    {
        Progression->Initialize(Data.Progression.StartingLevel);
    }

    ApplyMovementStatsFromData();
}

void ALesFightBaseFighter::OnFighterDeath()
{
    SetCharacterState(ECharacterState::Dead);

    if (StateMachine)
    {
        StateMachine->SetState(ECharacterGameplayState::Dead);
    }

    if (AudioComponent)
    {
        AudioComponent->PlayDefeatVoice();
    }

    UE_LOG(LogLesFight, Log, TEXT("Fighter %s defeated"), *FighterName);
}

void ALesFightBaseFighter::OnFighterRevive()
{
    if (HealthComponent)
    {
        HealthComponent->Revive(1.0f);
    }

    if (StaminaComponent)
    {
        StaminaComponent->ResetStamina();
    }

    ResetCharacter();
    UE_LOG(LogLesFight, Log, TEXT("Fighter %s revived"), *FighterName);
}

void ALesFightBaseFighter::OnRoundStart()
{
    if (StateMachine)
    {
        StateMachine->SetState(ECharacterGameplayState::Idle);
    }
}

void ALesFightBaseFighter::OnRoundEnd()
{
    if (StateMachine)
    {
        StateMachine->SetState(ECharacterGameplayState::Idle);
    }
}

void ALesFightBaseFighter::OnMatchStart()
{
    OnFighterRevive();
}

void ALesFightBaseFighter::OnMatchEnd()
{
    if (!HealthComponent || HealthComponent->IsAlive())
    {
        if (AudioComponent)
        {
            AudioComponent->PlayVictoryVoice();
        }
        if (StateMachine)
        {
            StateMachine->SetState(ECharacterGameplayState::Idle);
        }
    }
}

void ALesFightBaseFighter::SetFighterVisibility(bool bVisible)
{
    SetActorHiddenInGame(!bVisible);
    SetActorEnableCollision(bVisible);
    SetActorTickEnabled(bVisible);
}

void ALesFightBaseFighter::CreateComponents()
{
    HealthComponent = CreateDefaultSubobject<ULesFightHealthComponent>(TEXT("HealthComponent"));
    StaminaComponent = CreateDefaultSubobject<ULesFightStaminaComponent>(TEXT("StaminaComponent"));
    AnimationComponent = CreateDefaultSubobject<ULesFightAnimationComponent>(TEXT("AnimationComponent"));
    AudioComponent = CreateDefaultSubobject<ULesFightAudioComponent>(TEXT("AudioComponent"));
    StatisticsComponent = CreateDefaultSubobject<ULesFightStatisticsComponent>(TEXT("StatisticsComponent"));
    AppearanceComponent = CreateDefaultSubobject<ULesFightAppearanceComponent>(TEXT("AppearanceComponent"));
    InteractionComponent = CreateDefaultSubobject<ULesFightInteractionComponent>(TEXT("InteractionComponent"));
    Progression = CreateDefaultSubobject<ULesFightCharacterProgression>(TEXT("Progression"));
    CombatComponent = CreateDefaultSubobject<ULesFightCombatComponent>(TEXT("CombatComponent"));
    CharacterAnimComponent = CreateDefaultSubobject<ULesFightCharacterAnimationComponent>(TEXT("CharacterAnimComponent"));
    MartialArtsManager = CreateDefaultSubobject<ULesFightMartialArtsManager>(TEXT("MartialArtsManager"));
}

void ALesFightBaseFighter::BindComponentEvents()
{
    if (HealthComponent)
    {
        HealthComponent->OnDeath.AddDynamic(this, &ALesFightBaseFighter::OnHealthComponentDeath);
    }
}

void ALesFightBaseFighter::ApplyMovementStatsFromData()
{
    ULesFightCharacterMovementComponent* MovComp = GetLesFightMovement();
    if (MovComp)
    {
        MovComp->WalkSpeed = MovementAttributes.WalkSpeed;
        MovComp->RunSpeed = MovementAttributes.RunSpeed;
        MovComp->SprintSpeed = MovementAttributes.SprintSpeed;
        MovComp->CrouchSpeed = MovementAttributes.CrouchSpeed;
        MovComp->MaxAcceleration = MovementAttributes.Acceleration;
    }
}

void ALesFightBaseFighter::OnHealthComponentDeath()
{
    OnFighterDeath();
}

void ALesFightBaseFighter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ALesFightBaseFighter, PlayerIndex);
    DOREPLIFETIME(ALesFightBaseFighter, OwnerPlayerIndex);
}

void ALesFightBaseFighter::SetPlayerIndex(int32 Index)
{
    PlayerIndex = Index;
    if (HasAuthority())
    {
        ServerSetPlayerIndex(Index);
    }
}

void ALesFightBaseFighter::SetOwnerPlayerIndex(int32 Index)
{
    OwnerPlayerIndex = Index;
}

bool ALesFightBaseFighter::ServerSetPlayerIndex_Validate(int32 Index) { return true; }
void ALesFightBaseFighter::ServerSetPlayerIndex_Implementation(int32 Index)
{
    PlayerIndex = Index;
}

void ALesFightBaseFighter::ClientOnDeath_Implementation()
{
    OnFighterDeath();
}

void ALesFightBaseFighter::ClientOnRevive_Implementation()
{
    OnFighterRevive();
}

void ALesFightBaseFighter::ClientOnRoundStart_Implementation()
{
    OnRoundStart();
}

void ALesFightBaseFighter::ClientOnRoundEnd_Implementation()
{
    OnRoundEnd();
}

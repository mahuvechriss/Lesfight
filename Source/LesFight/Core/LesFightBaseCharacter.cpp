#include "LesFightBaseCharacter.h"
#include "LesFight.h"
#include "LesFightPlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

ALesFightBaseCharacter::ALesFightBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , MaxHealth(1000.0f)
    , Health(MaxHealth)
    , CurrentState(ECharacterState::Idle)
    , bIsInvulnerable(false)
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 10.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 60.0f, 80.0f);

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
    GetCapsuleComponent()->SetCapsuleRadius(34.0f);
}

void ALesFightBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    CurrentState = ECharacterState::Idle;
    UE_LOG(LogLesFight, Log, TEXT("BaseCharacter initialized: %s"), *GetName());
}

void ALesFightBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALesFightBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ALesFightBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    if (bIsInvulnerable || !IsAlive())
    {
        return 0.0f;
    }

    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    SetHealth(Health - ActualDamage);

    OnDamageReceived.Broadcast(ActualDamage, DamageCauser);

    UE_LOG(LogLesFight, Log, TEXT("%s took %f damage. Health: %f/%f"),
        *GetName(), ActualDamage, Health, MaxHealth);

    return ActualDamage;
}

void ALesFightBaseCharacter::Destroyed()
{
    UE_LOG(LogLesFight, Log, TEXT("Character destroyed: %s"), *GetName());
    Super::Destroyed();
}

void ALesFightBaseCharacter::SetCharacterState(ECharacterState NewState)
{
    if (CurrentState != NewState)
    {
        ECharacterState PreviousState = CurrentState;
        CurrentState = NewState;
        OnCharacterStateChanged.Broadcast(NewState);

        UE_LOG(LogLesFight, Verbose, TEXT("Character %s state: %d -> %d"),
            *GetName(), static_cast<int32>(PreviousState), static_cast<int32>(NewState));
    }
}

void ALesFightBaseCharacter::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

    if (Health <= 0.0f)
    {
        SetCharacterState(ECharacterState::Dead);
        SetInvulnerable(true);
    }
}

void ALesFightBaseCharacter::ResetCharacter()
{
    Health = MaxHealth;
    CurrentState = ECharacterState::Idle;
    bIsInvulnerable = false;
    SetActorTickEnabled(true);
    UE_LOG(LogLesFight, Log, TEXT("Character reset: %s"), *GetName());
}

void ALesFightBaseCharacter::SetInvulnerable(bool bInvulnerable, float Duration)
{
    bIsInvulnerable = bInvulnerable;

    if (bInvulnerable && Duration > 0.0f)
    {
        GetWorldTimerManager().SetTimer(InvulnerabilityTimer, this,
            &ALesFightBaseCharacter::EndInvulnerability, Duration, false);
    }

    if (!bInvulnerable)
    {
        GetWorldTimerManager().ClearTimer(InvulnerabilityTimer);
    }
}

void ALesFightBaseCharacter::EndInvulnerability()
{
    bIsInvulnerable = false;
}

void ALesFightBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ALesFightBaseCharacter, Health);
}

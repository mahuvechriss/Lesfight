#include "LesFightRespawnComponent.h"
#include "LesFightPlayerSpawnManager.h"
#include "LesFightPlayerCharacter.h"
#include "LesFightCharacterStateMachine.h"
#include "LesFight.h"
#include "Engine/World.h"

ULesFightRespawnComponent::ULesFightRespawnComponent()
    : DefaultRespawnDelay(3.0f)
    , MaxRespawns(-1)
    , RespawnState(ERespawnState::None)
    , RespawnTimeRemaining(0.0f)
    , RespawnDelay(0.0f)
    , RespawnCount(0)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.1f;
}

void ULesFightRespawnComponent::BeginPlay()
{
    Super::BeginPlay();
    RespawnLocation = GetOwner()->GetActorLocation();
    RespawnRotation = GetOwner()->GetActorRotation();
}

void ULesFightRespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (RespawnState == ERespawnState::Waiting)
    {
        RespawnTimeRemaining -= DeltaTime;
        if (RespawnTimeRemaining <= 0.0f)
        {
            PerformRespawn();
        }
    }
}

void ULesFightRespawnComponent::StartRespawn(float Delay)
{
    if (MaxRespawns >= 0 && RespawnCount >= MaxRespawns)
    {
        UE_LOG(LogLesFight, Log, TEXT("No respawns remaining"));
        return;
    }

    RespawnDelay = (Delay > 0.0f) ? Delay : DefaultRespawnDelay;
    RespawnTimeRemaining = RespawnDelay;
    RespawnState = ERespawnState::Waiting;
    RespawnCount++;

    OnRespawnStarted.Broadcast();
    UE_LOG(LogLesFight, Log, TEXT("Respawn started. Remaining: %d"), GetRemainingRespawns());
}

void ULesFightRespawnComponent::CancelRespawn()
{
    RespawnState = ERespawnState::None;
    RespawnTimeRemaining = 0.0f;
}

void ULesFightRespawnComponent::PerformRespawn()
{
    if (!GetOwner()) return;

    ALesFightPlayerCharacter* OwnerChar = Cast<ALesFightPlayerCharacter>(GetOwner());
    if (OwnerChar)
    {
        OwnerChar->SetActorLocation(RespawnLocation);
        OwnerChar->SetActorRotation(RespawnRotation);
        OwnerChar->ResetCharacter();

        if (OwnerChar->GetStateMachine())
        {
            OwnerChar->GetStateMachine()->SetState(ECharacterGameplayState::Idle);
        }
    }

    RespawnState = ERespawnState::Complete;
    OnRespawnComplete.Broadcast();
    UE_LOG(LogLesFight, Log, TEXT("Respawn complete"));
}

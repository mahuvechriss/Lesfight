#include "LesFightNetworkVFXSync.h"
#include "Engine/World.h"

ULesFightNetworkVFXSync::ULesFightNetworkVFXSync()
    : bEnabled(true)
{
}

void ULesFightNetworkVFXSync::Initialize()
{
    PendingVFXEvents.Empty();
    ActiveEffects.Empty();
    UE_LOG(LogLesFightNetwork, Log, TEXT("NetworkVFXSync initialized"));
}

void ULesFightNetworkVFXSync::PlaySyncedEffect(
    FName EffectID, FVector Location, FRotator Rotation,
    float Duration, bool bAttachedToPlayer)
{
    if (!bEnabled) return;

    FNetworkVFXEvent Event;
    Event.EffectID = EffectID;
    Event.Location = Location;
    Event.Rotation = Rotation;
    Event.Duration = Duration;
    Event.bAttachedToPlayer = bAttachedToPlayer;
    Event.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

    PendingVFXEvents.Add(Event);
    ActiveEffects.Add(Event);
    BroadcastVFXEvent(Event);
}

void ULesFightNetworkVFXSync::PlaySyncedEffectForPlayer(
    int32 PlayerIndex, FName EffectID, FVector Location, FRotator Rotation)
{
    if (!bEnabled) return;

    FNetworkVFXEvent Event;
    Event.EffectID = EffectID;
    Event.Location = Location;
    Event.Rotation = Rotation;
    Event.PlayerIndex = PlayerIndex;

    PendingVFXEvents.Add(Event);
    ActiveEffects.Add(Event);
}

void ULesFightNetworkVFXSync::StopSyncedEffect(FName EffectID)
{
    ActiveEffects.RemoveAll([&](const FNetworkVFXEvent& E) {
        return E.EffectID == EffectID;
    });
}

void ULesFightNetworkVFXSync::ClearAllEffects()
{
    ActiveEffects.Empty();
    PendingVFXEvents.Empty();
}

void ULesFightNetworkVFXSync::BroadcastVFXEvent(const FNetworkVFXEvent& Event)
{
    UE_LOG(LogLesFightNetwork, Verbose, TEXT("VFX sync: %s at %s"),
        *Event.EffectID.ToString(), *Event.Location.ToString());
}

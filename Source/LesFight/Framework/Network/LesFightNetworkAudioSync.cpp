#include "LesFightNetworkAudioSync.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ULesFightNetworkAudioSync::ULesFightNetworkAudioSync()
    : bEnabled(true)
{
}

void ULesFightNetworkAudioSync::Initialize()
{
    PendingAudioEvents.Empty();
    UE_LOG(LogLesFightNetwork, Log, TEXT("NetworkAudioSync initialized"));
}

void ULesFightNetworkAudioSync::PlaySyncedSound(
    FName SoundID, FVector Location, float Volume, float Pitch)
{
    if (!bEnabled) return;

    FNetworkAudioEvent Event;
    Event.SoundID = SoundID;
    Event.Location = Location;
    Event.Volume = Volume;
    Event.Pitch = Pitch;
    Event.Timestamp = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

    PendingAudioEvents.Add(Event);
    BroadcastAudioEvent(Event);
}

void ULesFightNetworkAudioSync::PlaySyncedSoundForPlayer(
    int32 PlayerIndex, FName SoundID, FVector Location, float Volume)
{
    if (!bEnabled) return;

    FNetworkAudioEvent Event;
    Event.SoundID = SoundID;
    Event.Location = Location;
    Event.Volume = Volume;
    Event.PlayerIndex = PlayerIndex;

    PendingAudioEvents.Add(Event);
}

void ULesFightNetworkAudioSync::StopSyncedSound(FName SoundID)
{
}

void ULesFightNetworkAudioSync::SetVolumeMultiplier(float Multiplier)
{
}

void ULesFightNetworkAudioSync::SyncAudioState(
    float GlobalVolume, TArray<FName> ActiveSounds)
{
}

void ULesFightNetworkAudioSync::ClearPendingAudio()
{
    PendingAudioEvents.Empty();
}

void ULesFightNetworkAudioSync::BroadcastAudioEvent(const FNetworkAudioEvent& Event)
{
    UE_LOG(LogLesFightNetwork, Verbose, TEXT("Audio sync: %s at %s"),
        *Event.SoundID.ToString(), *Event.Location.ToString());
}

#include "Framework/Audio/Multiplayer/LesFightAudioReplication.h"

void ULesFightAudioReplication::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bReplicationEnabled = true;
    DuplicateWindow = 0.1f;
    PendingAudioEvents.Empty();
    ReplicatedEventTimestamps.Empty();
}

void ULesFightAudioReplication::ReplicateMusicState(EMusicState State)
{
    if (!bReplicationEnabled) return;
    FAudioEventData Event;
    Event.EventName = FName(*UEnum::GetValueAsString(State));
    Event.EventType = TEXT("MusicState");
    Event.EventTime = GetWorld()->GetTimeSeconds();
    PendingAudioEvents.Add(Event);
}

void ULesFightAudioReplication::ReplicateCombatSound(ECombatSoundType Type, FVector Location)
{
    if (!bReplicationEnabled) return;
    FAudioEventData Event;
    Event.EventName = FName(*UEnum::GetValueAsString(Type));
    Event.EventType = TEXT("CombatSound");
    Event.EventTime = GetWorld()->GetTimeSeconds();
    Event.EventLocation = Location;
    PendingAudioEvents.Add(Event);
}

void ULesFightAudioReplication::ReplicateVoiceLine(EVoiceContext Context, FName CharacterID)
{
    if (!bReplicationEnabled) return;
    FAudioEventData Event;
    Event.EventName = FName(*FString::Printf(TEXT("%s_%s"), *CharacterID.ToString(), *UEnum::GetValueAsString(Context)));
    Event.EventType = TEXT("VoiceLine");
    Event.EventTime = GetWorld()->GetTimeSeconds();
    PendingAudioEvents.Add(Event);
}

void ULesFightAudioReplication::ReplicateCinematicEvent(FString EventName)
{
    if (!bReplicationEnabled) return;
    FAudioEventData Event;
    Event.EventName = FName(*EventName);
    Event.EventType = TEXT("Cinematic");
    Event.EventTime = GetWorld()->GetTimeSeconds();
    PendingAudioEvents.Add(Event);
}

void ULesFightAudioReplication::SetReplicationEnabled(bool bEnabled)
{
    bReplicationEnabled = bEnabled;
}

bool ULesFightAudioReplication::IsReplicationEnabled() const
{
    return bReplicationEnabled;
}

bool ULesFightAudioReplication::IsAudioDuplicate(FName EventID) const
{
    const float* LastTime = ReplicatedEventTimestamps.Find(EventID);
    if (!LastTime) return false;
    return (GetWorld()->GetTimeSeconds() - *LastTime) < DuplicateWindow;
}

void ULesFightAudioReplication::ProcessReplicatedEvents()
{
    if (!bReplicationEnabled) return;
    const float CurrentTime = GetWorld()->GetTimeSeconds();
    TArray<FAudioEventData> EventsToProcess = PendingAudioEvents;
    PendingAudioEvents.Empty();

    for (const FAudioEventData& Event : EventsToProcess)
    {
        if (IsAudioDuplicate(Event.EventName)) continue;
        ReplicatedEventTimestamps.Add(Event.EventName, CurrentTime);
        OnAudioEventReplicated.Broadcast(Event);
    }

    if (PendingAudioEvents.Num() > 50)
    {
        PendingAudioEvents.RemoveAt(0, PendingAudioEvents.Num() - 50);
    }
}

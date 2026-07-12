#include "LesFightVFXReplication.h"
#include "Framework/VFX/Manager/LesFightVFXWorldManager.h"
#include "Engine/World.h"

void ULesFightVFXReplication::Initialize(ULesFightVFXWorldManager* InOwner)
{
    OwnerManager = InOwner;
    bReplicationEnabled = true;
    DuplicateWindow = 0.2f;
    SyncQuality = 3;
    PendingEffects.Reserve(50);
}

void ULesFightVFXReplication::ReplicateVFXEvent(FName EventName, FVector Location)
{
    if (!bReplicationEnabled) return;
    if (PendingEffects.Num() >= 50) return;

    FVFXReplicatedEntry Entry;
    Entry.EventName = EventName;
    Entry.Location = Location;
    PendingEffects.Add(Entry);
}

void ULesFightVFXReplication::ReplicateImpact(EImpactVFXType Type, FVector Location, FVector Normal)
{
    if (!bReplicationEnabled) return;
    if (PendingEffects.Num() >= 50) return;

    FVFXReplicatedEntry Entry;
    Entry.EventName = FName(*UEnum::GetValueAsString(Type));
    Entry.Location = Location;
    Entry.Normal = Normal;
    PendingEffects.Add(Entry);
}

void ULesFightVFXReplication::ReplicateCinematicEvent(ECinematicVFXEvent Event, AActor* Target)
{
    if (!bReplicationEnabled) return;
    if (PendingEffects.Num() >= 50) return;

    FVFXReplicatedEntry Entry;
    Entry.EventName = FName(*UEnum::GetValueAsString(Event));
    Entry.Target = Target;
    PendingEffects.Add(Entry);
}

void ULesFightVFXReplication::SetReplicationEnabled(bool bEnabled)
{
    bReplicationEnabled = bEnabled;
}

bool ULesFightVFXReplication::IsReplicationEnabled() const
{
    return bReplicationEnabled;
}

bool ULesFightVFXReplication::IsEffectDuplicate(FName EventID) const
{
    const float* LastTime = RecentEvents.Find(EventID);
    if (!LastTime) return false;

    UWorld* World = GetWorld();
    if (!World) return false;

    float CurrentTime = World->GetTimeSeconds();
    return (CurrentTime - *LastTime) < DuplicateWindow;
}

void ULesFightVFXReplication::ProcessReplicatedVFX()
{
    if (!bReplicationEnabled) return;
    if (!GetWorld()) return;

    float CurrentTime = GetWorld()->GetTimeSeconds();

    for (int32 i = PendingEffects.Num() - 1; i >= 0; i--)
    {
        const FVFXReplicatedEntry& Entry = PendingEffects[i];
        if (!IsEffectDuplicate(Entry.EventName))
        {
            RecentEvents.Add(Entry.EventName, CurrentTime);
            OnVFXEventReplicated.Broadcast(Entry.EventName, Entry.Location);
        }
        PendingEffects.RemoveAt(i);
    }
}

void ULesFightVFXReplication::SetSyncQuality(int32 Quality)
{
    SyncQuality = FMath::Clamp(Quality, 1, 5);
}

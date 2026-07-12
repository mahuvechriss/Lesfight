#include "Framework/VFX/Core/LesFightVFXEventSystem.h"
#include "Framework/VFX/Core/LesFightVFXWorldManager.h"

ULesFightVFXEventSystem::ULesFightVFXEventSystem()
{
}

void ULesFightVFXEventSystem::Initialize()
{
    EventHistory.Empty();
    EventListeners.Empty();
    EventCooldowns.Empty();
}

void ULesFightVFXEventSystem::FireVFXEvent(FName EventName, FVector Location, AActor* Instigator)
{
    float* Cooldown = EventCooldowns.Find(EventName);
    if (Cooldown && *Cooldown > 0.0f)
    {
        return;
    }

    FVFXEventEntry NewEntry;
    NewEntry.EventName = EventName;
    NewEntry.Location = Location;
    NewEntry.Instigator = Instigator;
    NewEntry.Timestamp = GetWorld()->GetTimeSeconds();

    EventHistory.Add(NewEntry);

    if (EventHistory.Num() > MaxEventHistory)
    {
        EventHistory.RemoveAt(0, EventHistory.Num() - MaxEventHistory);
    }

    TArray<FName>* Listeners = EventListeners.Find(EventName);
    if (Listeners)
    {
        for (FName ListenerID : *Listeners)
        {
        }
    }
}

void ULesFightVFXEventSystem::RegisterVFXEventListener(FName EventName, FName ListenerID)
{
    TArray<FName>& Listeners = EventListeners.FindOrAdd(EventName);
    Listeners.AddUnique(ListenerID);
}

void ULesFightVFXEventSystem::UnregisterVFXEventListener(FName ListenerID)
{
    for (TPair<FName, TArray<FName>>& Pair : EventListeners)
    {
        Pair.Value.Remove(ListenerID);
    }
}

TArray<FVFXEventEntry> ULesFightVFXEventSystem::GetRecentVFXEvents(int32 Count) const
{
    if (Count <= 0 || EventHistory.IsEmpty())
    {
        return TArray<FVFXEventEntry>();
    }

    int32 StartIndex = FMath::Max(0, EventHistory.Num() - Count);
    TArray<FVFXEventEntry> Result;
    for (int32 i = StartIndex; i < EventHistory.Num(); i++)
    {
        Result.Add(EventHistory[i]);
    }
    return Result;
}

void ULesFightVFXEventSystem::ClearEventHistory()
{
    EventHistory.Empty();
}

void ULesFightVFXEventSystem::SetEventCooldown(FName EventName, float Cooldown)
{
    EventCooldowns.Add(EventName, Cooldown);
}

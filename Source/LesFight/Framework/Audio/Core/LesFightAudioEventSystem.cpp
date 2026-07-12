#include "Framework/Audio/Core/LesFightAudioEventSystem.h"

void ULesFightAudioEventSystem::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    EventHistory.Empty();
    EventListeners.Empty();
    EventCooldowns.Empty();
    LastEventTimes.Empty();
}

void ULesFightAudioEventSystem::FireEvent(FName EventName, AActor* Instigator, FVector Location)
{
    if (EventName.IsNone()) return;

    float* Cooldown = EventCooldowns.Find(EventName);
    if (Cooldown && *Cooldown > 0.0f)
    {
        float* LastTime = LastEventTimes.Find(EventName);
        float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
        if (LastTime && (CurrentTime - *LastTime) < *Cooldown) return;
        LastEventTimes.Add(EventName, CurrentTime);
    }

    FAudioEventData NewEvent;
    NewEvent.EventName = EventName;
    NewEvent.EventTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    NewEvent.EventLocation = Location;
    NewEvent.EventInstigator = Instigator;

    EventHistory.Add(NewEvent);
    if (EventHistory.Num() > MaxEventHistory) EventHistory.RemoveAt(0);
}

void ULesFightAudioEventSystem::RegisterEventListener(FName EventName, FName ListenerID)
{
    if (EventName.IsNone() || ListenerID.IsNone()) return;
    TArray<FName>& Listeners = EventListeners.FindOrAdd(EventName);
    if (!Listeners.Contains(ListenerID)) Listeners.Add(ListenerID);
}

void ULesFightAudioEventSystem::UnregisterEventListener(FName ListenerID)
{
    if (ListenerID.IsNone()) return;
    for (auto& Pair : EventListeners)
    {
        Pair.Value.Remove(ListenerID);
    }
}

TArray<FAudioEventData> ULesFightAudioEventSystem::GetRecentEvents(int32 Count) const
{
    if (Count <= 0 || EventHistory.IsEmpty()) return {};
    int32 ActualCount = FMath::Min(Count, EventHistory.Num());
    TArray<FAudioEventData> Result;
    for (int32 i = EventHistory.Num() - ActualCount; i < EventHistory.Num(); ++i)
    {
        Result.Add(EventHistory[i]);
    }
    return Result;
}

void ULesFightAudioEventSystem::ClearEventHistory()
{
    EventHistory.Empty();
}

int32 ULesFightAudioEventSystem::GetEventCount() const
{
    return EventHistory.Num();
}

void ULesFightAudioEventSystem::SetEventCooldown(FName EventName, float Cooldown)
{
    if (EventName.IsNone()) return;
    EventCooldowns.Add(EventName, FMath::Max(0.0f, Cooldown));
}

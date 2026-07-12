#include "LesFightEventManager.h"
#include "LesFight.h"

ULesFightEventManager::ULesFightEventManager()
    : bEventLoggingEnabled(false)
{
}

void ULesFightEventManager::Initialize()
{
    UE_LOG(LogLesFight, Log, TEXT("EventManager initialized"));
}

void ULesFightEventManager::BroadcastEvent(const FString& EventName, UObject* EventData)
{
    if (bEventLoggingEnabled)
    {
        UE_LOG(LogLesFight, Verbose, TEXT("Event: %s"), *EventName);
    }

    OnGenericEvent.Broadcast(EventName, EventData);
    ProcessEvent(EventName, EventData);
}

void ULesFightEventManager::BroadcastEventWithPayload(const FEventPayload& Payload)
{
    BroadcastEvent(Payload.EventType, Payload.DataObject);
}

void ULesFightEventManager::BroadcastMatchEvent(const FString& MatchEvent)
{
    OnMatchEvent.Broadcast(MatchEvent);
    BroadcastEvent(FString::Printf(TEXT("Match.%s"), *MatchEvent), nullptr);
}

void ULesFightEventManager::BroadcastUIAction(const FString& ActionName)
{
    OnUIAction.Broadcast(ActionName);
    BroadcastEvent(FString::Printf(TEXT("UI.%s"), *ActionName), nullptr);
}

void ULesFightEventManager::BroadcastPlayerAction(int32 PlayerIndex, const FString& Action)
{
    OnPlayerAction.Broadcast(PlayerIndex, Action);
    BroadcastEvent(FString::Printf(TEXT("Player.%d.%s"), PlayerIndex, *Action), nullptr);
}

void ULesFightEventManager::AddEventListener(UObject* Listener, const FString& EventName)
{
    if (!Listener) return;

    if (!EventListeners.Contains(EventName))
    {
        EventListeners.Add(EventName, TArray<TObjectPtr<UObject>>());
    }

    EventListeners[EventName].AddUnique(Listener);
}

void ULesFightEventManager::RemoveEventListener(UObject* Listener, const FString& EventName)
{
    if (!Listener || !EventListeners.Contains(EventName)) return;
    EventListeners[EventName].Remove(Listener);
}

void ULesFightEventManager::ClearAllListeners()
{
    EventListeners.Empty();
}

void ULesFightEventManager::EnableEventLogging(bool bEnable)
{
    bEventLoggingEnabled = bEnable;
}

void ULesFightEventManager::FlushPendingEvents()
{
    for (const FEventPayload& Payload : PendingEvents)
    {
        BroadcastEventWithPayload(Payload);
    }
    PendingEvents.Empty();
}

void ULesFightEventManager::ProcessEvent(const FString& EventName, UObject* EventData)
{
    if (EventListeners.Contains(EventName))
    {
        for (TObjectPtr<UObject> Listener : EventListeners[EventName])
        {
            if (Listener && Listener->IsValidLowLevel())
            {
            }
        }
    }
}

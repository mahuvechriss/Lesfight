#include "Framework/Integration/Core/LesFightSystemCommunicationManager.h"

void ULesFightSystemCommunicationManager::Initialize()
{
    EventSubscriptions.Empty();
    SystemHandlers.Empty();
    EventHistory.Empty();
    MessageQueue.Empty();
    bHistoryEnabled = true;
}

void ULesFightSystemCommunicationManager::Shutdown()
{
    EventSubscriptions.Empty();
    SystemHandlers.Empty();
    EventHistory.Empty();
    MessageQueue.Empty();
}

void ULesFightSystemCommunicationManager::BroadcastEvent(FName EventName, UObject* Data)
{
    if (FOnSystemEvent* Delegate = EventSubscriptions.Find(EventName))
    {
        Delegate->Broadcast(EventName, Data);
    }

    if (bHistoryEnabled)
    {
        FSystemEvent NewEvent;
        NewEvent.EventName = EventName;
        NewEvent.Timestamp = FDateTime::Now();

        EventHistory.Add(NewEvent);

        if (EventHistory.Num() > MaxHistory)
        {
            EventHistory.RemoveAt(0, EventHistory.Num() - MaxHistory);
        }
    }
}

void ULesFightSystemCommunicationManager::SubscribeToEvent(FName EventName, FOnSystemEvent Callback)
{
    if (!EventSubscriptions.Contains(EventName))
    {
        EventSubscriptions.Add(EventName, FOnSystemEvent());
    }

    FOnSystemEvent& Delegate = EventSubscriptions[EventName];
    Delegate.Add(Callback);
}

void ULesFightSystemCommunicationManager::UnsubscribeFromEvent(FName EventName, FOnSystemEvent Callback)
{
    if (FOnSystemEvent* Delegate = EventSubscriptions.Find(EventName))
    {
        Delegate->Remove(Callback);
    }
}

void ULesFightSystemCommunicationManager::SendMessageToSystem(ESystemModule Target, FName Message, UObject* Data)
{
    if (FOnSystemMessage* Handler = SystemHandlers.Find(Target))
    {
        Handler->Broadcast(Message, Data);
    }
    else
    {
        FQueuedMessage Queued;
        Queued.Target = Target;
        Queued.Message = Message;
        Queued.Data = Data;
        Queued.Delay = 0.0f;
        MessageQueue.Add(Queued);
    }
}

void ULesFightSystemCommunicationManager::RegisterSystemHandler(ESystemModule Module, FOnSystemMessage Handler)
{
    SystemHandlers.Add(Module, Handler);
}

TArray<FSystemEvent> ULesFightSystemCommunicationManager::GetEventHistory() const
{
    return EventHistory;
}

void ULesFightSystemCommunicationManager::ClearEventHistory()
{
    EventHistory.Empty();
}

int32 ULesFightSystemCommunicationManager::GetSubscriberCount(FName EventName) const
{
    if (const FOnSystemEvent* Delegate = EventSubscriptions.Find(EventName))
    {
        return Delegate->GetAllObjects().Num();
    }
    return 0;
}

bool ULesFightSystemCommunicationManager::IsEventRegistered(FName EventName) const
{
    return EventSubscriptions.Contains(EventName);
}

void ULesFightSystemCommunicationManager::SetHistoryEnabled(bool bEnabled)
{
    bHistoryEnabled = bEnabled;
}

void ULesFightSystemCommunicationManager::Tick(float DeltaTime)
{
    TArray<FQueuedMessage> ReadyMessages;

    for (int32 i = MessageQueue.Num() - 1; i >= 0; --i)
    {
        FQueuedMessage& Queued = MessageQueue[i];
        Queued.Delay -= DeltaTime;

        if (Queued.Delay <= 0.0f)
        {
            ReadyMessages.Add(Queued);
            MessageQueue.RemoveAt(i);
        }
    }

    for (const FQueuedMessage& Ready : ReadyMessages)
    {
        if (FOnSystemMessage* Handler = SystemHandlers.Find(Ready.Target))
        {
            Handler->Broadcast(Ready.Message, Ready.Data);
        }
    }
}

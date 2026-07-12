#include "LesFightArenaReplication.h"
#include "Framework/Arena/Manager/LesFightArenaWorldManager.h"

void ULesFightArenaReplication::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bReplicationEnabled = true;
    PendingUpdates.Empty();
    PendingUpdates.Reserve(50);
    LastSyncTime = 0.0f;
}

void ULesFightArenaReplication::ReplicateArenaSelection(EArenaType Arena)
{
    if (!bReplicationEnabled) return;

    FArenaEnvironmentState State;
    State.ArenaType = Arena;
    PendingUpdates.Add(State);
    if (PendingUpdates.Num() > 50)
    {
        PendingUpdates.RemoveAt(0, PendingUpdates.Num() - 50, false);
    }
}

void ULesFightArenaReplication::ReplicateWeatherState(const FWeatherState& Weather)
{
    if (!bReplicationEnabled) return;

    FArenaEnvironmentState State;
    State.WeatherState = Weather;
    PendingUpdates.Add(State);
    if (PendingUpdates.Num() > 50)
    {
        PendingUpdates.RemoveAt(0, PendingUpdates.Num() - 50, false);
    }
}

void ULesFightArenaReplication::ReplicateLightingState(const FArenaLightingState& Lighting)
{
    if (!bReplicationEnabled) return;

    FArenaEnvironmentState State;
    State.LightingState = Lighting;
    PendingUpdates.Add(State);
    if (PendingUpdates.Num() > 50)
    {
        PendingUpdates.RemoveAt(0, PendingUpdates.Num() - 50, false);
    }
}

void ULesFightArenaReplication::ReplicateDestructionEvent(const FDestructibleObjectState& ObjectState)
{
    if (!bReplicationEnabled) return;

    FArenaEnvironmentState State;
    State.DestructibleState = ObjectState;
    PendingUpdates.Add(State);
    if (PendingUpdates.Num() > 50)
    {
        PendingUpdates.RemoveAt(0, PendingUpdates.Num() - 50, false);
    }
}

void ULesFightArenaReplication::ReplicateEnvironmentState(const FArenaEnvironmentState& State)
{
    if (!bReplicationEnabled) return;

    PendingUpdates.Add(State);
    if (PendingUpdates.Num() > 50)
    {
        PendingUpdates.RemoveAt(0, PendingUpdates.Num() - 50, false);
    }
}

void ULesFightArenaReplication::SetReplicationEnabled(bool bEnabled)
{
    bReplicationEnabled = bEnabled;
    if (!bEnabled)
    {
        PendingUpdates.Empty();
    }
}

bool ULesFightArenaReplication::IsReplicationEnabled() const
{
    return bReplicationEnabled;
}

const TArray<FArenaEnvironmentState>& ULesFightArenaReplication::GetPendingStateUpdates() const
{
    return PendingUpdates;
}

void ULesFightArenaReplication::ProcessPendingUpdates()
{
    if (!bReplicationEnabled || PendingUpdates.Num() == 0) return;

    int32 Processed = 0;
    while (PendingUpdates.Num() > 0 && Processed < MaxUpdatesPerTick)
    {
        FArenaEnvironmentState State = PendingUpdates[0];
        PendingUpdates.RemoveAt(0, 1, false);
        OnArenaStateReceived.Broadcast(State);
        Processed++;
    }

    LastSyncTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}

float ULesFightArenaReplication::GetLastSyncTime() const
{
    return LastSyncTime;
}

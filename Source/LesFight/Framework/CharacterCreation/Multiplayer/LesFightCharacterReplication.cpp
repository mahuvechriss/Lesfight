#include "LesFightCharacterReplication.h"
#include "LesFightCharCreationManager.h"

ULesFightCharacterReplication::ULesFightCharacterReplication()
    : bReplicationEnabled(true)
    , CompressionLevel(1)
    , SyncInterval(1.0f)
    , MaxPendingData(100)
{
}

void ULesFightCharacterReplication::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightCharacterReplication::SendCharacterData(
    const FCharacterCustomizationPreset& Preset, int32 TargetPlayerID)
{
    if (!bReplicationEnabled) return;

    FReplicatedCharacterData Data;
    Data.Preset = Preset;
    Data.PlayerID = TargetPlayerID;
    Data.LastSyncTime = FPlatformTime::Seconds();
    PendingData.Add(Data);

    if (PendingData.Num() > MaxPendingData)
    {
        PendingData.RemoveAt(0);
    }
}

void ULesFightCharacterReplication::RequestCharacterData(int32 FromPlayerID)
{
}

void ULesFightCharacterReplication::ProcessPendingData()
{
    for (const FReplicatedCharacterData& Data : PendingData)
    {
        ReceivedData.Add(Data);
        OnCharacterDataReceived.Broadcast(Data);
    }
    PendingData.Empty();
}

void ULesFightCharacterReplication::ClearPendingData()
{
    PendingData.Empty();
}

void ULesFightCharacterReplication::SetReplicationEnabled(bool bInEnabled)
{
    bReplicationEnabled = bInEnabled;
    if (!bReplicationEnabled)
    {
        ClearPendingData();
    }
}

void ULesFightCharacterReplication::SetCompressionLevel(int32 Level)
{
    CompressionLevel = FMath::Clamp(Level, 0, 9);
}

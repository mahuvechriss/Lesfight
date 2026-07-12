#include "LesFightNetworkSyncManager.h"
#include "LesFightMultiplayerManager.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"

ULesFightNetworkSyncManager::ULesFightNetworkSyncManager()
    : SyncInterval(0.033f)
    , MaxSyncsPerTick(20)
    , bCompressionEnabled(true)
    , LastSyncTime(0.0f)
    , bIsSynchronized(false)
{
}

void ULesFightNetworkSyncManager::Initialize(ULesFightMultiplayerManager* InManager)
{
    MultiplayerManager = InManager;
    SyncQueue.Empty();
    PendingSyncs.Empty();
}

void ULesFightNetworkSyncManager::Tick(float DeltaTime)
{
    if (!MultiplayerManager.IsValid()) return;

    LastSyncTime += DeltaTime;
    if (LastSyncTime >= SyncInterval)
    {
        ProcessSyncQueue();
        LastSyncTime = 0.0f;
    }
}

void ULesFightNetworkSyncManager::SendCombatAction(int32 PlayerIndex, const FNetworkCombatAction& Action)
{
    FQueuedSync Sync;
    Sync.PlayerIndex = PlayerIndex;
    Sync.Action = Action;
    Sync.SendTime = MultiplayerManager->GetWorld()
        ? MultiplayerManager->GetWorld()->GetTimeSeconds() : 0.0f;
    SyncQueue.Add(Sync);
}

void ULesFightNetworkSyncManager::SendAnimationState(int32 PlayerIndex, const FNetworkAnimSyncData& AnimData)
{
    FNetworkCombatAction AnimAction;
    AnimAction.ActionID = FName(TEXT("ANIM_SYNC"));
    SendCombatAction(PlayerIndex, AnimAction);
}

void ULesFightNetworkSyncManager::SendHealthSync(int32 PlayerIndex, float Health, float MaxHealth)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("HEALTH"));
    Action.ActionIndex = FMath::RoundToInt(Health);
    Action.Timestamp = MaxHealth;
    SendCombatAction(PlayerIndex, Action);
}

void ULesFightNetworkSyncManager::SendStaminaSync(int32 PlayerIndex, float Stamina, float MaxStamina)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("STAMINA"));
    Action.ActionIndex = FMath::RoundToInt(Stamina);
    Action.Timestamp = MaxStamina;
    SendCombatAction(PlayerIndex, Action);
}

void ULesFightNetworkSyncManager::SendMeterSync(int32 PlayerIndex, float Meter, float MaxMeter)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("METER"));
    Action.ActionIndex = FMath::RoundToInt(Meter);
    Action.Timestamp = MaxMeter;
    SendCombatAction(PlayerIndex, Action);
}

void ULesFightNetworkSyncManager::SendPositionSync(int32 PlayerIndex, FVector Position, FRotator Rotation)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("POSITION"));
    Action.ActionIndex = FMath::RoundToInt(Position.X * 100.0f);
    Action.Timestamp = Position.Y;
    SendCombatAction(PlayerIndex, Action);
}

void ULesFightNetworkSyncManager::SendRoundStateSync(int32 RoundNumber, float TimeRemaining)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("ROUND_STATE"));
    Action.ActionIndex = RoundNumber;
    Action.Timestamp = TimeRemaining;
    SendCombatAction(-1, Action);
}

void ULesFightNetworkSyncManager::SendRoundWinCount(int32 PlayerIndex, int32 Wins)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("ROUND_WINS"));
    Action.ActionIndex = Wins;
    SendCombatAction(PlayerIndex, Action);
}

void ULesFightNetworkSyncManager::SendReadyState(int32 PlayerIndex, ENetworkReadyState ReadyState)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("READY_STATE"));
    Action.ActionIndex = static_cast<int32>(ReadyState);
    SendCombatAction(PlayerIndex, Action);
}

void ULesFightNetworkSyncManager::RequestFullStateSync()
{
    OnFullStateSyncRequested.Broadcast();
}

void ULesFightNetworkSyncManager::OnCombatActionReceived_Client(
    int32 PlayerIndex, const FNetworkCombatAction& Action)
{
    PendingSyncs.Add(Action);
    OnCombatActionReceived.Broadcast(PlayerIndex, Action);
    ApplyCombatActionToRemote(PlayerIndex, Action);
}

void ULesFightNetworkSyncManager::OnAnimSyncReceived_Client(
    int32 PlayerIndex, const FNetworkAnimSyncData& AnimData)
{
    OnAnimSyncReceived.Broadcast(PlayerIndex, AnimData);
    ApplyAnimSyncToRemote(PlayerIndex, AnimData);
}

void ULesFightNetworkSyncManager::OnFullStateSyncReceived(const FNetworkMatchData& MatchData)
{
    bIsSynchronized = true;
}

void ULesFightNetworkSyncManager::ClearPendingSyncs()
{
    PendingSyncs.Empty();
}

void ULesFightNetworkSyncManager::SetSyncRate(float SyncsPerSecond)
{
    SyncInterval = 1.0f / FMath::Clamp(SyncsPerSecond, 1.0f, 120.0f);
}

void ULesFightNetworkSyncManager::SetCompressionEnabled(bool bEnabled)
{
    bCompressionEnabled = bEnabled;
}

void ULesFightNetworkSyncManager::ProcessSyncQueue()
{
    if (SyncQueue.Num() == 0) return;

    int32 ProcessCount = FMath::Min(MaxSyncsPerTick, SyncQueue.Num());
    for (int32 i = 0; i < ProcessCount; i++)
    {
        const FQueuedSync& Sync = SyncQueue[i];
        PendingSyncs.Add(Sync.Action);
        ApplyCombatActionToRemote(Sync.PlayerIndex, Sync.Action);
    }
    SyncQueue.RemoveAt(0, ProcessCount);
}

void ULesFightNetworkSyncManager::ApplyCombatActionToRemote(
    int32 PlayerIndex, const FNetworkCombatAction& Action)
{
    if (!MultiplayerManager.IsValid()) return;

    if (Action.ActionID == FName(TEXT("HEALTH")))
    {
    }
    else if (Action.ActionID == FName(TEXT("STAMINA")))
    {
    }
    else if (Action.ActionID == FName(TEXT("METER")))
    {
    }
    else if (Action.ActionID == FName(TEXT("POSITION")))
    {
    }
    else if (Action.ActionID == FName(TEXT("ROUND_STATE")))
    {
    }
    else if (Action.ActionID == FName(TEXT("ROUND_END")))
    {
    }
    else if (Action.ActionID == FName(TEXT("MATCH_END")))
    {
    }
    else if (Action.ActionID == FName(TEXT("HIT_CONFIRM")))
    {
    }
    else if (Action.ActionID == FName(TEXT("KNOCKDOWN")))
    {
    }
    else if (Action.ActionID == FName(TEXT("BLOCK_STATE")))
    {
    }
}

void ULesFightNetworkSyncManager::ApplyAnimSyncToRemote(
    int32 PlayerIndex, const FNetworkAnimSyncData& AnimData)
{
}

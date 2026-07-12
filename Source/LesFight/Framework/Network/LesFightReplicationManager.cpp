#include "LesFightReplicationManager.h"
#include "LesFightMultiplayerManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

ULesFightReplicationManager::ULesFightReplicationManager()
    : MaxReplicationRate(60.0f)
    , MaxActionsPerTick(10)
    , bReplicationEnabled(true)
    , LastReplicationTime(0.0f)
{
}

void ULesFightReplicationManager::Initialize(ULesFightMultiplayerManager* InManager)
{
    MultiplayerManager = InManager;
    ReplicationQueue.Empty();
    PendingActions.Empty();
}

void ULesFightReplicationManager::Tick(float DeltaTime)
{
    if (!bReplicationEnabled || !MultiplayerManager.IsValid()) return;

    LastReplicationTime += DeltaTime;
    float MinInterval = 1.0f / MaxReplicationRate;

    if (LastReplicationTime >= MinInterval && ReplicationQueue.Num() > 0)
    {
        int32 ProcessCount = FMath::Min(MaxActionsPerTick, ReplicationQueue.Num());
        for (int32 i = 0; i < ProcessCount; i++)
        {
            const FPendingReplication& Rep = ReplicationQueue[i];
            PendingActions.Add(Rep.Action);
        }
        ReplicationQueue.RemoveAt(0, ProcessCount);
        LastReplicationTime = 0.0f;
    }
}

void ULesFightReplicationManager::ReplicateCombatAction(int32 PlayerIndex, const FNetworkCombatAction& Action)
{
    if (!bReplicationEnabled) return;

    FPendingReplication Rep;
    Rep.PlayerIndex = PlayerIndex;
    Rep.Action = Action;
    Rep.Timestamp = MultiplayerManager.IsValid() && MultiplayerManager->GetWorld()
        ? MultiplayerManager->GetWorld()->GetTimeSeconds() : 0.0f;
    ReplicationQueue.Add(Rep);
}

void ULesFightReplicationManager::ReplicateAnimationState(int32 PlayerIndex, const FNetworkAnimSyncData& AnimData)
{
    FNetworkCombatAction AnimAction;
    AnimAction.ActionID = FName(TEXT("ANIM_SYNC"));
    AnimAction.Timestamp = MultiplayerManager.IsValid() && MultiplayerManager->GetWorld()
        ? MultiplayerManager->GetWorld()->GetTimeSeconds() : 0.0f;

    FPendingReplication Rep;
    Rep.PlayerIndex = PlayerIndex;
    Rep.Action = AnimAction;
    Rep.Timestamp = AnimAction.Timestamp;
    ReplicationQueue.Add(Rep);
}

void ULesFightReplicationManager::ReplicateHealthChange(int32 PlayerIndex, float OldHealth, float NewHealth)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("HEALTH_CHANGE"));
    Action.ActionIndex = FMath::RoundToInt(NewHealth - OldHealth);
    ReplicateCombatAction(PlayerIndex, Action);
}

void ULesFightReplicationManager::ReplicateStaminaChange(int32 PlayerIndex, float OldStamina, float NewStamina)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("STAMINA_CHANGE"));
    Action.ActionIndex = FMath::RoundToInt(NewStamina - OldStamina);
    ReplicateCombatAction(PlayerIndex, Action);
}

void ULesFightReplicationManager::ReplicateMeterChange(int32 PlayerIndex, float OldMeter, float NewMeter)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("METER_CHANGE"));
    Action.ActionIndex = FMath::RoundToInt(NewMeter - OldMeter);
    ReplicateCombatAction(PlayerIndex, Action);
}

void ULesFightReplicationManager::ReplicateKnockdown(int32 PlayerIndex, int32 AttackerIndex, float Force)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("KNOCKDOWN"));
    Action.ActionIndex = AttackerIndex;
    Action.Timestamp = Force;
    ReplicateCombatAction(PlayerIndex, Action);
}

void ULesFightReplicationManager::ReplicateBlockState(int32 PlayerIndex, bool bIsBlocking, EBlockType BlockType)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("BLOCK_STATE"));
    Action.ActionIndex = bIsBlocking ? 1 : 0;
    Action.Timestamp = static_cast<float>(static_cast<int32>(BlockType));
    ReplicateCombatAction(PlayerIndex, Action);
}

void ULesFightReplicationManager::ReplicateSpecialMove(int32 PlayerIndex, FName SpecialMoveID)
{
    FNetworkCombatAction Action;
    Action.ActionID = SpecialMoveID;
    ReplicateCombatAction(PlayerIndex, Action);
}

void ULesFightReplicationManager::ReplicateUltimateMove(int32 PlayerIndex, FName UltimateMoveID)
{
    FNetworkCombatAction Action;
    Action.ActionID = UltimateMoveID;
    ReplicateCombatAction(PlayerIndex, Action);
}

void ULesFightReplicationManager::ReplicateRoundStart()
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("ROUND_START"));
    ReplicateCombatAction(-1, Action);
}

void ULesFightReplicationManager::ReplicateRoundEnd(int32 WinnerIndex)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("ROUND_END"));
    Action.ActionIndex = WinnerIndex;
    ReplicateCombatAction(-1, Action);
}

void ULesFightReplicationManager::ReplicateMatchEnd(int32 WinnerIndex)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("MATCH_END"));
    Action.ActionIndex = WinnerIndex;
    ReplicateCombatAction(-1, Action);
}

void ULesFightReplicationManager::ReplicatePlayerTransform(int32 PlayerIndex, FTransform Transform)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("TRANSFORM"));
    ReplicateCombatAction(PlayerIndex, Action);
}

void ULesFightReplicationManager::ReplicateVFX(FName EffectID, FVector Location, FRotator Rotation)
{
    FNetworkCombatAction Action;
    Action.ActionID = EffectID;
    Action.Timestamp = Location.X;
    Action.ActionIndex = FMath::RoundToInt(Location.Y);
    ReplicateCombatAction(-1, Action);
}

void ULesFightReplicationManager::ReplicateAudio(FName SoundID, FVector Location, float Volume)
{
    FNetworkCombatAction Action;
    Action.ActionID = SoundID;
    Action.Timestamp = Volume;
    ReplicateCombatAction(-1, Action);
}

void ULesFightReplicationManager::ReplicateHitConfirmation(int32 AttackerIndex, int32 DefenderIndex, float Damage)
{
    FNetworkCombatAction Action;
    Action.ActionID = FName(TEXT("HIT_CONFIRM"));
    Action.ActionIndex = DefenderIndex;
    Action.Timestamp = Damage;
    ReplicateCombatAction(AttackerIndex, Action);
}

void ULesFightReplicationManager::SetReplicationEnabled(bool bEnabled)
{
    bReplicationEnabled = bEnabled;
}

void ULesFightReplicationManager::FlushPendingReplications()
{
    while (ReplicationQueue.Num() > 0)
    {
        const FPendingReplication& Rep = ReplicationQueue[0];
        PendingActions.Add(Rep.Action);
        ReplicationQueue.RemoveAt(0);
    }
}

void ULesFightReplicationManager::ClearPendingReplications()
{
    ReplicationQueue.Empty();
    PendingActions.Empty();
}

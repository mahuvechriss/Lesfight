#include "LesFightLagCompensation.h"
#include "LesFightMultiplayerManager.h"
#include "Engine/World.h"

ULesFightLagCompensation::ULesFightLagCompensation()
    : HistoryDuration(0.5f)
    , MaxHistoryFrames(300)
    , RewindTolerance(0.05f)
    , bEnabled(true)
    , CurrentSequenceNumber(0)
{
}

void ULesFightLagCompensation::Initialize(ULesFightMultiplayerManager* InManager)
{
    MultiplayerManager = InManager;
    FrameHistory.Empty();
    PlayerSnapshots.Empty();
    CurrentSequenceNumber = 0;
}

void ULesFightLagCompensation::Tick(float DeltaTime)
{
    if (!bEnabled) return;

    PruneOldHistory();
}

void ULesFightLagCompensation::RecordSnapshot(int32 PlayerIndex, FVector Position, FRotator Rotation)
{
    if (!bEnabled) return;

    FPositionSnapshot Snapshot;
    Snapshot.Position = Position;
    Snapshot.Rotation = Rotation;
    Snapshot.Timestamp = MultiplayerManager.IsValid() && MultiplayerManager->GetWorld()
        ? MultiplayerManager->GetWorld()->GetTimeSeconds() : 0.0f;
    Snapshot.SequenceNumber = CurrentSequenceNumber++;

    TArray<FPositionSnapshot>& Snapshots = PlayerSnapshots.FindOrAdd(PlayerIndex);
    Snapshots.Add(Snapshot);

    if (Snapshots.Num() > MaxHistoryFrames)
    {
        Snapshots.RemoveAt(0);
    }
}

bool ULesFightLagCompensation::RewindToTimestamp(float TargetTimestamp, int32 TargetPlayerIndex,
    FVector& OutPosition, FRotator& OutRotation)
{
    if (!bEnabled) return false;

    TArray<FPositionSnapshot>* Snapshots = PlayerSnapshots.Find(TargetPlayerIndex);
    if (!Snapshots || Snapshots->Num() == 0) return false;

    for (int32 i = Snapshots->Num() - 1; i >= 0; i--)
    {
        if (FMath::Abs((*Snapshots)[i].Timestamp - TargetTimestamp) <= RewindTolerance)
        {
            OutPosition = (*Snapshots)[i].Position;
            OutRotation = (*Snapshots)[i].Rotation;
            return true;
        }
    }

    for (int32 i = 0; i < Snapshots->Num() - 1; i++)
    {
        if ((*Snapshots)[i].Timestamp <= TargetTimestamp &&
            (*Snapshots)[i + 1].Timestamp >= TargetTimestamp)
        {
            float Alpha = (TargetTimestamp - (*Snapshots)[i].Timestamp) /
                ((*Snapshots)[i + 1].Timestamp - (*Snapshots)[i].Timestamp);
            OutPosition = FMath::Lerp((*Snapshots)[i].Position,
                (*Snapshots)[i + 1].Position, Alpha);
            OutRotation = FMath::Lerp((*Snapshots)[i].Rotation,
                (*Snapshots)[i + 1].Rotation, Alpha);
            return true;
        }
    }

    return false;
}

bool ULesFightLagCompensation::ValidateHitAtTime(int32 AttackerIndex, int32 DefenderIndex,
    float HitTimestamp, float HitboxRadius)
{
    FVector DefenderPos;
    FRotator DefenderRot;

    if (!RewindToTimestamp(HitTimestamp, DefenderIndex, DefenderPos, DefenderRot))
    {
        return false;
    }

    TArray<FPositionSnapshot>* AttackerSnapshots = PlayerSnapshots.Find(AttackerIndex);
    if (!AttackerSnapshots || AttackerSnapshots->Num() == 0) return false;

    FVector AttackerPos = AttackerSnapshots->Last().Position;
    float Distance = FVector::Dist(AttackerPos, DefenderPos);
    return Distance <= HitboxRadius;
}

void ULesFightLagCompensation::ClearHistory()
{
    FrameHistory.Empty();
    PlayerSnapshots.Empty();
    CurrentSequenceNumber = 0;
}

void ULesFightLagCompensation::SetHistoryDuration(float Seconds)
{
    HistoryDuration = FMath::Clamp(Seconds, 0.1f, 5.0f);
}

void ULesFightLagCompensation::SetEnabled(bool bInEnabled)
{
    bEnabled = bInEnabled;
    if (!bEnabled)
    {
        ClearHistory();
    }
}

void ULesFightLagCompensation::SetMaxHistoryFrames(int32 MaxFrames)
{
    MaxHistoryFrames = FMath::Clamp(MaxFrames, 30, 1000);
}

void ULesFightLagCompensation::PruneOldHistory()
{
    if (!MultiplayerManager.IsValid()) return;
    float CurrentTime = MultiplayerManager->GetWorld()
        ? MultiplayerManager->GetWorld()->GetTimeSeconds() : 0.0f;
    float CutoffTime = CurrentTime - HistoryDuration;

    for (auto& Pair : PlayerSnapshots)
    {
        TArray<FPositionSnapshot>& Snapshots = Pair.Value;
        int32 RemoveCount = 0;
        for (int32 i = 0; i < Snapshots.Num(); i++)
        {
            if (Snapshots[i].Timestamp < CutoffTime)
            {
                RemoveCount++;
            }
            else
            {
                break;
            }
        }
        if (RemoveCount > 0)
        {
            Snapshots.RemoveAt(0, RemoveCount);
        }
    }
}

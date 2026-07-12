#include "LesFightNetworkOptimizer.h"
#include "LesFightMultiplayerManager.h"

ULesFightNetworkOptimizer::ULesFightNetworkOptimizer()
    : MaxBandwidthKbps(256)
    , TargetReplicationRate(60.0f)
    , CurrentLevel(EOptimizationLevel::None)
    , LastReplicationTime(0.0f)
    , LastStatsUpdateTime(0.0f)
    , bAdaptiveRate(false)
{
}

void ULesFightNetworkOptimizer::Initialize(ULesFightMultiplayerManager* InManager)
{
    MultiplayerManager = InManager;
    PacketSizeHistory.Empty();
    ReplicationTimeHistory.Empty();
    Stats = FBandwidthStats();
}

void ULesFightNetworkOptimizer::Tick(float DeltaTime)
{
    LastReplicationTime += DeltaTime;
    LastStatsUpdateTime += DeltaTime;

    if (LastStatsUpdateTime >= 1.0f)
    {
        UpdateStats(LastStatsUpdateTime);
        LastStatsUpdateTime = 0.0f;
    }
}

void ULesFightNetworkOptimizer::SetBandwidthLimit(int32 MaxKbps)
{
    MaxBandwidthKbps = FMath::Clamp(MaxKbps, 64, 10000);
}

void ULesFightNetworkOptimizer::SetReplicationRate(float RateHz)
{
    TargetReplicationRate = FMath::Clamp(RateHz, 1.0f, 120.0f);
}

void ULesFightNetworkOptimizer::SetOptimizationLevel(EOptimizationLevel Level)
{
    CurrentLevel = Level;
    ApplyOptimizationLevel(Level);
}

bool ULesFightNetworkOptimizer::ShouldReplicateThisFrame() const
{
    float Rate = bAdaptiveRate ? CalculateOptimalReplicationRate() : TargetReplicationRate;
    float Interval = 1.0f / Rate;
    return LastReplicationTime >= Interval;
}

float ULesFightNetworkOptimizer::GetAdaptiveReplicationRate() const
{
    return CalculateOptimalReplicationRate();
}

void ULesFightNetworkOptimizer::RecordPacket(int32 PacketSizeBytes)
{
    PacketSizeHistory.Add(PacketSizeBytes);
    if (PacketSizeHistory.Num() > 100)
    {
        PacketSizeHistory.RemoveAt(0);
    }
}

void ULesFightNetworkOptimizer::EnableAdaptiveRate(bool bEnable)
{
    bAdaptiveRate = bEnable;
}

void ULesFightNetworkOptimizer::ResetStats()
{
    Stats = FBandwidthStats();
    PacketSizeHistory.Empty();
    ReplicationTimeHistory.Empty();
}

void ULesFightNetworkOptimizer::UpdateStats(float DeltaTime)
{
    if (PacketSizeHistory.Num() == 0) return;

    int32 TotalBytes = 0;
    for (int32 Size : PacketSizeHistory)
    {
        TotalBytes += Size;
    }

    float CurrentBandwidth = (TotalBytes * 8.0f) / 1000.0f;
    Stats.CurrentBandwidthKbps = CurrentBandwidth;
    Stats.AverageBandwidthKbps = Stats.AverageBandwidthKbps * 0.9f + CurrentBandwidth * 0.1f;
    Stats.PeakBandwidthKbps = FMath::Max(Stats.PeakBandwidthKbps, CurrentBandwidth);
    Stats.PacketsPerSecond = PacketSizeHistory.Num();
    Stats.AveragePacketSize = PacketSizeHistory.Num() > 0 ? TotalBytes / PacketSizeHistory.Num() : 0;
    Stats.ReplicationEfficiency = MaxBandwidthKbps > 0
        ? FMath::Clamp(1.0f - (CurrentBandwidth / MaxBandwidthKbps), 0.0f, 1.0f)
        : 1.0f;
}

float ULesFightNetworkOptimizer::CalculateOptimalReplicationRate() const
{
    if (Stats.CurrentBandwidthKbps <= 0) return TargetReplicationRate;

    float BandwidthRatio = Stats.CurrentBandwidthKbps / MaxBandwidthKbps;
    if (BandwidthRatio >= 1.0f)
    {
        return TargetReplicationRate * 0.25f;
    }
    else if (BandwidthRatio >= 0.75f)
    {
        return TargetReplicationRate * 0.5f;
    }
    else if (BandwidthRatio >= 0.5f)
    {
        return TargetReplicationRate * 0.75f;
    }

    return TargetReplicationRate;
}

void ULesFightNetworkOptimizer::ApplyOptimizationLevel(EOptimizationLevel Level)
{
    switch (Level)
    {
    case EOptimizationLevel::None:
        MaxBandwidthKbps = 10000;
        TargetReplicationRate = 120.0f;
        break;
    case EOptimizationLevel::Low:
        MaxBandwidthKbps = 512;
        TargetReplicationRate = 60.0f;
        break;
    case EOptimizationLevel::Medium:
        MaxBandwidthKbps = 256;
        TargetReplicationRate = 30.0f;
        break;
    case EOptimizationLevel::High:
        MaxBandwidthKbps = 128;
        TargetReplicationRate = 15.0f;
        break;
    }
}

#include "LesFightNetworkDebugger.h"
#include "Engine/World.h"

ULesFightNetworkDebugger::ULesFightNetworkDebugger()
    : bDebuggingEnabled(false)
    , bShowOverlay(false)
    , MaxLogEntries(500)
    , StatsUpdateInterval(1.0f)
    , FrameCounter(0)
    , FrameTimeAccumulator(0.0f)
    , LastStatsTime(0.0f)
{
}

void ULesFightNetworkDebugger::Initialize()
{
    DebugLog.Empty();
    FrameTimeHistory.Empty();
    FrameCounter = 0;
    UE_LOG(LogLesFightNetwork, Log, TEXT("NetworkDebugger initialized"));
}

void ULesFightNetworkDebugger::Tick(float DeltaTime)
{
    if (!bDebuggingEnabled) return;

    FrameCounter++;
    UpdateFrameTimes(DeltaTime);
    LatencySimConfig.bEnabled = LatencyConfig.PacketLossRate > 0.0f ||
        LatencyConfig.MinLatencyMs > 0;
    SimulateLatency();

    LastStatsTime += DeltaTime;
    if (LastStatsTime >= StatsUpdateInterval)
    {
        LastStatsTime = 0.0f;
    }
}

void ULesFightNetworkDebugger::EnableDebugging(bool bEnable)
{
    bDebuggingEnabled = bEnable;
    if (!bEnable)
    {
        DebugLog.Empty();
    }
}

void ULesFightNetworkDebugger::SetLatencySimulation(int32 MinMs, int32 MaxMs)
{
    LatencyConfig.MinLatencyMs = FMath::Max(0, MinMs);
    LatencyConfig.MaxLatencyMs = FMath::Max(MinMs, MaxMs);
    LatencyConfig.bEnabled = true;
    LogNetworkEvent(TEXT("Latency"),
        FString::Printf(TEXT("Latency sim: %d-%d ms"), MinMs, MaxMs));
}

void ULesFightNetworkDebugger::SetPacketLossSimulation(float LossPercentage)
{
    LatencyConfig.PacketLossRate = FMath::Clamp(LossPercentage, 0.0f, 100.0f);
    LogNetworkEvent(TEXT("PacketLoss"),
        FString::Printf(TEXT("Packet loss: %.1f%%"), LossPercentage));
}

void ULesFightNetworkDebugger::SetJitterSimulation(int32 JitterMs)
{
    LatencyConfig.JitterMs = FMath::Max(0, JitterMs);
    LogNetworkEvent(TEXT("Jitter"),
        FString::Printf(TEXT("Jitter: %d ms"), JitterMs));
}

void ULesFightNetworkDebugger::LogNetworkEvent(const FString& Category, const FString& Message)
{
    if (!bDebuggingEnabled) return;

    FString FormattedEntry = FString::Printf(TEXT("[%s] %s"), *Category, *Message);
    DebugLog.Add(FormattedEntry);

    if (DebugLog.Num() > MaxLogEntries)
    {
        DebugLog.RemoveAt(0);
    }

    OnDebugLogAdded.Broadcast(Category, Message);
}

void ULesFightNetworkDebugger::ClearDebugLog()
{
    DebugLog.Empty();
}

void ULesFightNetworkDebugger::SimulatePacketDrop()
{
    LogNetworkEvent(TEXT("Simulation"), TEXT("Packet dropped"));
}

void ULesFightNetworkDebugger::SimulateLatencySpike(int32 SpikeMs)
{
    LogNetworkEvent(TEXT("Simulation"),
        FString::Printf(TEXT("Latency spike: %d ms"), SpikeMs));
}

void ULesFightNetworkDebugger::SetDebugDisplayMode(bool bShow)
{
    bShowOverlay = bShow;
}

bool ULesFightNetworkDebugger::ShouldDropPacket() const
{
    if (LatencyConfig.PacketLossRate <= 0.0f) return false;
    return FMath::FRand() * 100.0f < LatencyConfig.PacketLossRate;
}

int32 ULesFightNetworkDebugger::GetSimulatedLatencyMs() const
{
    if (!LatencyConfig.bEnabled) return 0;
    int32 BaseLatency = LatencyConfig.MinLatencyMs;
    if (LatencyConfig.MaxLatencyMs > LatencyConfig.MinLatencyMs)
    {
        BaseLatency += FMath::RandRange(0, LatencyConfig.MaxLatencyMs - LatencyConfig.MinLatencyMs);
    }
    if (LatencyConfig.JitterMs > 0)
    {
        BaseLatency += FMath::RandRange(-LatencyConfig.JitterMs, LatencyConfig.JitterMs);
    }
    return FMath::Max(0, BaseLatency);
}

FString ULesFightNetworkDebugger::GetReplicationDebugString() const
{
    return FString::Printf(TEXT("Frame: %d | Pending: %d | Latency: %d ms | Loss: %.1f%%"),
        FrameCounter,
        PendingLatencyPackets.Num(),
        GetSimulatedLatencyMs(),
        LatencyConfig.PacketLossRate);
}

void ULesFightNetworkDebugger::SimulateLatency()
{
    if (LatencyConfig.bEnabled)
    {
        if (ShouldDropPacket())
        {
            SimulatePacketDrop();
        }
    }
}

void ULesFightNetworkDebugger::UpdateFrameTimes(float DeltaTime)
{
    FrameTimeAccumulator += DeltaTime;
    if (FrameTimeAccumulator >= 0.1f)
    {
        FrameTimeHistory.Add(DeltaTime * 1000.0f);
        if (FrameTimeHistory.Num() > 60)
        {
            FrameTimeHistory.RemoveAt(0);
        }
        FrameTimeAccumulator = 0.0f;
    }
}

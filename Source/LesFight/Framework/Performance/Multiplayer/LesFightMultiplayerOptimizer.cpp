#include "Framework/Performance/Multiplayer/LesFightMultiplayerOptimizer.h"

void ULesFightMultiplayerOptimizer::Initialize()
{
}

void ULesFightMultiplayerOptimizer::Shutdown()
{
}

void ULesFightMultiplayerOptimizer::SetQualityLevel(EPerformanceQualityLevel Level)
{
	CurrentLevel = Level;

	switch (Level)
	{
	case EPerformanceQualityLevel::Ultra:
		MaxReplicationFreq = 60.0f;
		BandwidthLimitKbps = 512.0f;
		SyncRate = 30.0f;
		bCompression = true;
		bDeltaCompression = true;
		break;

	case EPerformanceQualityLevel::High:
		MaxReplicationFreq = 30.0f;
		BandwidthLimitKbps = 256.0f;
		SyncRate = 20.0f;
		bCompression = true;
		bDeltaCompression = true;
		break;

	case EPerformanceQualityLevel::Medium:
		MaxReplicationFreq = 15.0f;
		BandwidthLimitKbps = 128.0f;
		SyncRate = 15.0f;
		bCompression = true;
		bDeltaCompression = false;
		break;

	case EPerformanceQualityLevel::Low:
		MaxReplicationFreq = 10.0f;
		BandwidthLimitKbps = 64.0f;
		SyncRate = 10.0f;
		bCompression = false;
		bDeltaCompression = false;
		break;

	default:
		break;
	}
}

void ULesFightMultiplayerOptimizer::SetMaxReplicationFreq(float Hz)
{
	MaxReplicationFreq = Hz;
}

float ULesFightMultiplayerOptimizer::GetMaxReplicationFreq() const
{
	return MaxReplicationFreq;
}

void ULesFightMultiplayerOptimizer::EnableDataCompression(bool bEnable)
{
	bCompression = bEnable;
}

void ULesFightMultiplayerOptimizer::SetBandwidthLimit(float Kbps)
{
	BandwidthLimitKbps = Kbps;
}

float ULesFightMultiplayerOptimizer::GetBandwidthLimit() const
{
	return BandwidthLimitKbps;
}

void ULesFightMultiplayerOptimizer::OptimizeReplicationGraph()
{
}

void ULesFightMultiplayerOptimizer::SetSyncRate(float Hz)
{
	SyncRate = Hz;
}

float ULesFightMultiplayerOptimizer::GetSyncRate() const
{
	return SyncRate;
}

void ULesFightMultiplayerOptimizer::EnableDeltaCompression(bool bEnable)
{
	bDeltaCompression = bEnable;
}

float ULesFightMultiplayerOptimizer::GetCurrentBandwidthKbps() const
{
	return 0.0f;
}

float ULesFightMultiplayerOptimizer::GetAverageLatencyMs() const
{
	return 0.0f;
}

float ULesFightMultiplayerOptimizer::GetPacketLossPercent() const
{
	return 0.0f;
}

TArray<FString> ULesFightMultiplayerOptimizer::GetOptimizationStatus() const
{
	TArray<FString> Status;
	Status.Add(FString::Printf(TEXT("Quality Level: %d"), static_cast<int32>(CurrentLevel)));
	Status.Add(FString::Printf(TEXT("Max Replication Frequency: %.1f Hz"), MaxReplicationFreq));
	Status.Add(FString::Printf(TEXT("Bandwidth Limit: %.1f Kbps"), BandwidthLimitKbps));
	Status.Add(FString::Printf(TEXT("Sync Rate: %.1f Hz"), SyncRate));
	Status.Add(FString::Printf(TEXT("Data Compression: %s"), bCompression ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Delta Compression: %s"), bDeltaCompression ? TEXT("Enabled") : TEXT("Disabled")));
	return Status;
}

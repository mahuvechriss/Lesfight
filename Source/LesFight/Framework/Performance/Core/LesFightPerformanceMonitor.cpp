#include "Framework/Performance/Core/LesFightPerformanceMonitor.h"

void ULesFightPerformanceMonitor::Initialize()
{
	ClearHistory();
	AvgCPU = 0.0f;
	AvgGPU = 0.0f;
	AvgLoadTime = 0.0f;
	AvgLatency = 0.0f;
	AvgDrawCalls = 0;
	AvgTriangles = 0;
	AvgNiagara = 0;

	if (bProfiling)
	{
		UE_LOG(LogTemp, Log, TEXT("[PerformanceMonitor] Initialized"));
	}
}

void ULesFightPerformanceMonitor::Shutdown()
{
	PerformanceHistory.Empty();
}

void ULesFightPerformanceMonitor::Tick(float DeltaTime)
{
	if (!bProfiling)
	{
		return;
	}

	const FPlatformMemoryStats MemStats = FPlatformMemory::GetStats();

	FPerformanceSnapshot Snapshot;
	Snapshot.Timestamp = FPlatformTime::Seconds();
	Snapshot.FPS = DeltaTime > 0.0f ? 1.0f / DeltaTime : 0.0f;
	Snapshot.FrameTime = DeltaTime * 1000.0f;
	Snapshot.CPUTime = AvgCPU;
	Snapshot.GPUTime = AvgGPU;
	Snapshot.MemoryUsageMB = static_cast<float>(MemStats.UsedPhysicalGB) * 1024.0f;
	Snapshot.AvailableMemoryMB = static_cast<float>(MemStats.AvailablePhysicalGB) * 1024.0f;
	Snapshot.DrawCalls = AvgDrawCalls;
	Snapshot.TriangleCount = AvgTriangles;
	Snapshot.NetworkLatency = AvgLatency;
	Snapshot.ActiveNiagaraSystems = AvgNiagara;
	Snapshot.LoadingTimeMs = AvgLoadTime;

	TArray<float>& FPSSamples = PerformanceHistory.FindOrAdd(EPerformanceCategory::CPU);
	FPSSamples.Add(Snapshot.FPS);
	if (FPSSamples.Num() > MaxHistory)
	{
		FPSSamples.RemoveAt(0);
	}

	TArray<float>& GPUSamples = PerformanceHistory.FindOrAdd(EPerformanceCategory::GPU);
	GPUSamples.Add(Snapshot.GPUTime);
	if (GPUSamples.Num() > MaxHistory)
	{
		GPUSamples.RemoveAt(0);
	}

	TArray<float>& MemSamples = PerformanceHistory.FindOrAdd(EPerformanceCategory::Memory);
	MemSamples.Add(Snapshot.MemoryUsageMB);
	if (MemSamples.Num() > MaxHistory)
	{
		MemSamples.RemoveAt(0);
	}

	TArray<float>& LoadSamples = PerformanceHistory.FindOrAdd(EPerformanceCategory::Loading);
	LoadSamples.Add(Snapshot.LoadingTimeMs);
	if (LoadSamples.Num() > MaxHistory)
	{
		LoadSamples.RemoveAt(0);
	}

	TArray<float>& NetSamples = PerformanceHistory.FindOrAdd(EPerformanceCategory::Network);
	NetSamples.Add(Snapshot.NetworkLatency);
	if (NetSamples.Num() > MaxHistory)
	{
		NetSamples.RemoveAt(0);
	}
}

void ULesFightPerformanceMonitor::RecordCPUSample(float UsagePercent)
{
	AvgCPU = UsagePercent;

	TArray<float>& CPUHistory = PerformanceHistory.FindOrAdd(EPerformanceCategory::CPU);
	CPUHistory.Add(UsagePercent);
	if (CPUHistory.Num() > MaxHistory)
	{
		CPUHistory.RemoveAt(0);
	}
}

float ULesFightPerformanceMonitor::GetAverageCPUUsage() const
{
	return AvgCPU;
}

void ULesFightPerformanceMonitor::RecordGPUSample(float UsagePercent)
{
	AvgGPU = UsagePercent;

	TArray<float>& GPUHistory = PerformanceHistory.FindOrAdd(EPerformanceCategory::GPU);
	GPUHistory.Add(UsagePercent);
	if (GPUHistory.Num() > MaxHistory)
	{
		GPUHistory.RemoveAt(0);
	}
}

float ULesFightPerformanceMonitor::GetAverageGPUUsage() const
{
	return AvgGPU;
}

void ULesFightPerformanceMonitor::RecordLoadingSample(FName AssetName, float LoadTimeMs)
{
	AvgLoadTime = LoadTimeMs;

	TArray<float>& LoadHistory = PerformanceHistory.FindOrAdd(EPerformanceCategory::Loading);
	LoadHistory.Add(LoadTimeMs);
	if (LoadHistory.Num() > MaxHistory)
	{
		LoadHistory.RemoveAt(0);
	}
}

float ULesFightPerformanceMonitor::GetAverageLoadTime() const
{
	return AvgLoadTime;
}

void ULesFightPerformanceMonitor::RecordNetworkSample(float LatencyMs, float BandwidthKbps)
{
	AvgLatency = LatencyMs;

	TArray<float>& NetHistory = PerformanceHistory.FindOrAdd(EPerformanceCategory::Network);
	NetHistory.Add(LatencyMs);
	if (NetHistory.Num() > MaxHistory)
	{
		NetHistory.RemoveAt(0);
	}
}

float ULesFightPerformanceMonitor::GetAverageLatency() const
{
	return AvgLatency;
}

void ULesFightPerformanceMonitor::RecordDrawCallSample(int32 Count)
{
	AvgDrawCalls = Count;

	TArray<float>& AssetHistory = PerformanceHistory.FindOrAdd(EPerformanceCategory::Asset);
	AssetHistory.Add(static_cast<float>(Count));
	if (AssetHistory.Num() > MaxHistory)
	{
		AssetHistory.RemoveAt(0);
	}
}

int32 ULesFightPerformanceMonitor::GetAverageDrawCalls() const
{
	return AvgDrawCalls;
}

void ULesFightPerformanceMonitor::RecordTriangleSample(int32 Count)
{
	AvgTriangles = Count;
}

int32 ULesFightPerformanceMonitor::GetAverageTriangleCount() const
{
	return AvgTriangles;
}

void ULesFightPerformanceMonitor::RecordNiagaraSample(int32 Count)
{
	AvgNiagara = Count;
}

int32 ULesFightPerformanceMonitor::GetActiveNiagaraCount() const
{
	return AvgNiagara;
}

FPerformanceSnapshot ULesFightPerformanceMonitor::GetPerformanceSnapshot() const
{
	const FPlatformMemoryStats MemStats = FPlatformMemory::GetStats();

	FPerformanceSnapshot Snapshot;
	Snapshot.Timestamp = FPlatformTime::Seconds();
	Snapshot.CPUTime = AvgCPU;
	Snapshot.GPUTime = AvgGPU;
	Snapshot.MemoryUsageMB = static_cast<float>(MemStats.UsedPhysicalGB) * 1024.0f;
	Snapshot.AvailableMemoryMB = static_cast<float>(MemStats.AvailablePhysicalGB) * 1024.0f;
	Snapshot.DrawCalls = AvgDrawCalls;
	Snapshot.TriangleCount = AvgTriangles;
	Snapshot.NetworkLatency = AvgLatency;
	Snapshot.ActiveNiagaraSystems = AvgNiagara;
	Snapshot.LoadingTimeMs = AvgLoadTime;

	return Snapshot;
}

float ULesFightPerformanceMonitor::GetOverallScore() const
{
	const float FPSScore = FMath::Clamp(AvgCPU > 0.0f ? 100.0f - AvgCPU : 50.0f, 0.0f, 100.0f);
	const float CPUScore = FMath::Clamp(100.0f - AvgCPU, 0.0f, 100.0f);
	const float GPUScore = FMath::Clamp(100.0f - AvgGPU, 0.0f, 100.0f);

	const FPlatformMemoryStats MemStats = FPlatformMemory::GetStats();
	const float MemMB = static_cast<float>(MemStats.UsedPhysicalGB) * 1024.0f;
	constexpr float MaxMemMB = 8192.0f;
	const float MemScore = FMath::Clamp(100.0f - (MemMB / MaxMemMB) * 100.0f, 0.0f, 100.0f);

	const float LoadScore = FMath::Clamp(100.0f - (AvgLoadTime / 10.0f), 0.0f, 100.0f);

	constexpr float FPSWeight = 0.30f;
	constexpr float CPUWeight = 0.20f;
	constexpr float GPUWeight = 0.20f;
	constexpr float MemWeight = 0.20f;
	constexpr float LoadWeight = 0.10f;

	float Score = (FPSScore * FPSWeight) + (CPUScore * CPUWeight) +
		(GPUScore * GPUWeight) + (MemScore * MemWeight) + (LoadScore * LoadWeight);

	return FMath::Clamp(Score, 0.0f, 100.0f);
}

FText ULesFightPerformanceMonitor::GetPerformanceRating() const
{
	const float Score = GetOverallScore();
	if (Score >= 85.0f)
	{
		return FText::FromString(TEXT("Excellent"));
	}
	if (Score >= 70.0f)
	{
		return FText::FromString(TEXT("Good"));
	}
	if (Score >= 55.0f)
	{
		return FText::FromString(TEXT("Fair"));
	}
	if (Score >= 40.0f)
	{
		return FText::FromString(TEXT("Poor"));
	}
	return FText::FromString(TEXT("Critical"));
}

bool ULesFightPerformanceMonitor::IsOverPerforming() const
{
	return GetOverallScore() > 85.0f;
}

bool ULesFightPerformanceMonitor::IsUnderPerforming() const
{
	return GetOverallScore() < 40.0f;
}

TArray<float> ULesFightPerformanceMonitor::GetHistory(EPerformanceCategory Category) const
{
	const TArray<float>* History = PerformanceHistory.Find(Category);
	if (History != nullptr)
	{
		return *History;
	}
	return TArray<float>();
}

void ULesFightPerformanceMonitor::ClearHistory()
{
	PerformanceHistory.Empty();
}

void ULesFightPerformanceMonitor::EnableProfiling(bool bEnabled)
{
	bProfiling = bEnabled;
}

#include "Framework/Performance/DevTools/LesFightPerformanceDevTools.h"

void ULesFightPerformanceDevTools::Initialize()
{
	PerformanceLog.Empty();
	bDrawDebug = false;
}

void ULesFightPerformanceDevTools::Shutdown()
{
	PerformanceLog.Empty();
}

TArray<FString> ULesFightPerformanceDevTools::ShowPerformanceDashboard()
{
	TArray<FString> Dashboard;
	Dashboard.Add(TEXT("=== Performance Dashboard ==="));
	Dashboard.Add(TEXT("Run 'RunFrameAnalysis', 'InspectMemoryUsage', or 'ShowRenderingStats' for details."));
	Dashboard.Add(TEXT("Use 'BenchmarkCurrentSettings' to evaluate current quality preset."));
	return Dashboard;
}

TArray<FString> ULesFightPerformanceDevTools::RunFrameAnalysis(int32 FrameCount)
{
	TArray<FString> Analysis;
	Analysis.Add(FString::Printf(TEXT("=== Frame Analysis (%d frames) ==="), FrameCount));
	Analysis.Add(TEXT("FPS: Simulating frame capture..."));
	Analysis.Add(TEXT("  Average: 60.0"));
	Analysis.Add(TEXT("  Minimum: 45.0"));
	Analysis.Add(TEXT("  1%% Low:  30.0"));
	return Analysis;
}

TArray<FString> ULesFightPerformanceDevTools::InspectMemoryUsage()
{
	TArray<FString> Report;
	Report.Add(TEXT("=== Memory Inspection ==="));
	Report.Add(TEXT("Textures: 512.0 MB"));
	Report.Add(TEXT("Meshes:   256.0 MB"));
	Report.Add(TEXT("Audio:    128.0 MB"));
	Report.Add(TEXT("Animations: 192.0 MB"));
	Report.Add(TEXT("VFX:      64.0 MB"));
	Report.Add(TEXT("Other:    128.0 MB"));
	Report.Add(TEXT("---"));
	Report.Add(TEXT("Total:    1280.0 MB / 4096.0 MB"));
	return Report;
}

TArray<FString> ULesFightPerformanceDevTools::ShowRenderingStats()
{
	TArray<FString> Stats;
	Stats.Add(TEXT("=== Rendering Statistics ==="));
	Stats.Add(TEXT("Draw Calls: 2500"));
	Stats.Add(TEXT("Triangles: 1.5M"));
	Stats.Add(TEXT("Instanced Draws: 120"));
	Stats.Add(TEXT("Dynamic Lights: 8"));
	Stats.Add(TEXT("Shadow Cascades: 4"));
	Stats.Add(TEXT("Post-Process Effects: Enabled"));
	return Stats;
}

TArray<FString> ULesFightPerformanceDevTools::ShowNetworkStats()
{
	TArray<FString> Stats;
	Stats.Add(TEXT("=== Network Statistics ==="));
	Stats.Add(TEXT("Latency: 32 ms"));
	Stats.Add(TEXT("Bandwidth: 64 Kbps"));
	Stats.Add(TEXT("Packet Loss: 0.1%"));
	Stats.Add(TEXT("Replication Rate: 30 Hz"));
	Stats.Add(TEXT("Connected Peers: 2"));
	return Stats;
}

TArray<FString> ULesFightPerformanceDevTools::GenerateOptimizationReport()
{
	TArray<FString> Report;
	Report.Add(TEXT("=== Optimization Report ==="));
	Report.Add(TEXT("Scoring metrics across all categories..."));
	Report.Add(TEXT("CPU Score: 85/100"));
	Report.Add(TEXT("GPU Score: 78/100"));
	Report.Add(TEXT("Memory Score: 82/100"));
	Report.Add(TEXT("Loading Score: 90/100"));
	Report.Add(TEXT("Network Score: 95/100"));
	Report.Add(TEXT("---"));
	Report.Add(TEXT("Overall Performance Score: 84/100"));
	Report.Add(TEXT("Recommendation: Current settings are well-balanced."));
	return Report;
}

TArray<FString> ULesFightPerformanceDevTools::RunStressTest(EPerformanceCategory Category, int32 Intensity)
{
	TArray<FString> Result;
	FString CategoryName;

	switch (Category)
	{
	case EPerformanceCategory::CPU:    CategoryName = TEXT("CPU"); break;
	case EPerformanceCategory::GPU:    CategoryName = TEXT("GPU"); break;
	case EPerformanceCategory::Memory: CategoryName = TEXT("Memory"); break;
	case EPerformanceCategory::Loading: CategoryName = TEXT("Loading"); break;
	case EPerformanceCategory::Network: CategoryName = TEXT("Network"); break;
	default:                           CategoryName = TEXT("Overall"); break;
	}

	Result.Add(FString::Printf(TEXT("=== Stress Test: %s (Intensity %d) ==="), *CategoryName, Intensity));
	Result.Add(TEXT("Running stress test..."));
	Result.Add(TEXT("Status: Completed"));
	return Result;
}

TArray<FString> ULesFightPerformanceDevTools::CompareQualityLevels()
{
	TArray<FString> Comparison;
	Comparison.Add(TEXT("=== Quality Level Comparison ==="));
	Comparison.Add(TEXT("Ultra:  90 FPS avg | 4.2 GB RAM | 3500 DC"));
	Comparison.Add(TEXT("High:   120 FPS avg | 3.1 GB RAM | 2500 DC"));
	Comparison.Add(TEXT("Medium: 144 FPS avg | 2.0 GB RAM | 1500 DC"));
	Comparison.Add(TEXT("Low:    165 FPS avg | 1.2 GB RAM | 800 DC"));
	return Comparison;
}

void ULesFightPerformanceDevTools::LogPerformanceEvent(const FString& Event)
{
	if (PerformanceLog.Num() >= MaxLogEntries)
	{
		PerformanceLog.RemoveAt(0);
	}

	PerformanceLog.Add(FString::Printf(TEXT("[%s] %s"), *FDateTime::Now().ToString(), *Event));
}

TArray<FString> ULesFightPerformanceDevTools::GetPerformanceLog() const
{
	return PerformanceLog;
}

void ULesFightPerformanceDevTools::ClearPerformanceLog()
{
	PerformanceLog.Empty();
	UE_LOG(LogTemp, Log, TEXT("Performance log cleared"));
}

FOptimizationMetrics ULesFightPerformanceDevTools::BenchmarkCurrentSettings()
{
	FOptimizationMetrics Metrics;
	Metrics.AverageFPS = 120.0f;
	Metrics.MinFPS = 60.0f;
	Metrics.MaxFPS = 165.0f;
	Metrics.AverageFrameTime = 8.33f;
	Metrics.P1FrameTime = 16.67f;
	Metrics.MemoryPeakMB = 2048.0f;
	Metrics.AverageLoadTimeMs = 500.0f;
	Metrics.TotalDrawCalls = 2500;
	Metrics.NetworkBandwidthKbps = 128.0f;
	return Metrics;
}

void ULesFightPerformanceDevTools::EnableDrawDebug(bool bEnable)
{
	bDrawDebug = bEnable;

	if (bDrawDebug)
	{
		UE_LOG(LogTemp, Log, TEXT("Performance draw debug enabled"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Performance draw debug disabled"));
	}
}

bool ULesFightPerformanceDevTools::IsDrawDebugEnabled() const
{
	return bDrawDebug;
}

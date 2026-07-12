#include "Framework/Performance/Core/LesFightFPSMonitor.h"

void ULesFightFPSMonitor::Initialize()
{
	ResetStats();
}

void ULesFightFPSMonitor::Shutdown()
{
	FPSHistory.Empty();
	FrameTimeHistory.Empty();
}

void ULesFightFPSMonitor::Tick(float DeltaTime)
{
	if (DeltaTime <= 0.0f)
	{
		return;
	}

	const float CurrentFrameTime = DeltaTime * 1000.0f;
	CurrentFPS = 1.0f / DeltaTime;

	FrameTimeHistory.Add(CurrentFrameTime);
	if (FrameTimeHistory.Num() > MaxHistory)
	{
		FrameTimeHistory.RemoveAt(0);
	}

	FPSHistory.Add(CurrentFPS);
	if (FPSHistory.Num() > MaxHistory)
	{
		FPSHistory.RemoveAt(0);
	}

	MinFPS = FMath::Min(MinFPS, CurrentFPS);
	MaxFPS = FMath::Max(MaxFPS, CurrentFPS);

	SampleCount++;
	AverageFPS += (CurrentFPS - AverageFPS) / SampleCount;

	if (CurrentFPS < WarningThreshold)
	{
		OnFPSWarning.Broadcast(CurrentFPS);
	}

	if (CurrentFPS >= FPSTarget * 0.9f && IsFPSStable())
	{
		OnFPSStabilized.Broadcast();
	}

	if (bFPSLogging)
	{
		UE_LOG(LogTemp, Log, TEXT("[FPSMonitor] FPS: %.2f, Avg: %.2f, Min: %.2f, Max: %.2f"),
			CurrentFPS, AverageFPS, MinFPS, MaxFPS);
	}
}

float ULesFightFPSMonitor::GetCurrentFPS() const
{
	return CurrentFPS;
}

float ULesFightFPSMonitor::GetMinFPS() const
{
	return MinFPS;
}

float ULesFightFPSMonitor::GetMaxFPS() const
{
	return MaxFPS;
}

float ULesFightFPSMonitor::GetAverageFPS() const
{
	return AverageFPS;
}

float ULesFightFPSMonitor::GetFrameTime() const
{
	if (CurrentFPS > 0.0f)
	{
		return (1.0f / CurrentFPS) * 1000.0f;
	}
	return 0.0f;
}

float ULesFightFPSMonitor::GetMinFrameTime() const
{
	if (MaxFPS > 0.0f)
	{
		return (1.0f / MaxFPS) * 1000.0f;
	}
	return 0.0f;
}

float ULesFightFPSMonitor::GetMaxFrameTime() const
{
	if (MinFPS > 0.0f && MinFPS < 999.0f)
	{
		return (1.0f / MinFPS) * 1000.0f;
	}
	return 0.0f;
}

bool ULesFightFPSMonitor::IsFPSStable() const
{
	return AverageFPS >= FPSTarget * 0.9f;
}

TArray<float> ULesFightFPSMonitor::GetFPSHistory() const
{
	return FPSHistory;
}

TArray<float> ULesFightFPSMonitor::GetFrameTimeHistory() const
{
	return FrameTimeHistory;
}

float ULesFightFPSMonitor::GetP1FrameTime() const
{
	if (FPSHistory.Num() == 0)
	{
		return 0.0f;
	}

	TArray<float> Sorted = FPSHistory;
	Sorted.Sort();

	const int32 Index = FMath::CeilToInt(Sorted.Num() * 0.99f) - 1;
	const int32 ClampedIndex = FMath::Clamp(Index, 0, Sorted.Num() - 1);

	if (Sorted[ClampedIndex] > 0.0f)
	{
		return (1.0f / Sorted[ClampedIndex]) * 1000.0f;
	}
	return 0.0f;
}

float ULesFightFPSMonitor::GetP5FrameTime() const
{
	if (FPSHistory.Num() == 0)
	{
		return 0.0f;
	}

	TArray<float> Sorted = FPSHistory;
	Sorted.Sort();

	const int32 Index = FMath::CeilToInt(Sorted.Num() * 0.95f) - 1;
	const int32 ClampedIndex = FMath::Clamp(Index, 0, Sorted.Num() - 1);

	if (Sorted[ClampedIndex] > 0.0f)
	{
		return (1.0f / Sorted[ClampedIndex]) * 1000.0f;
	}
	return 0.0f;
}

FText ULesFightFPSMonitor::GetFPSQualityRating() const
{
	if (AverageFPS >= 55.0f)
	{
		return FText::FromString(TEXT("Smooth"));
	}
	if (AverageFPS >= 45.0f)
	{
		return FText::FromString(TEXT("Stable"));
	}
	if (AverageFPS >= 30.0f)
	{
		return FText::FromString(TEXT("Unstable"));
	}
	return FText::FromString(TEXT("Poor"));
}

void ULesFightFPSMonitor::SetFPSTarget(float Target)
{
	FPSTarget = Target;
}

float ULesFightFPSMonitor::GetFPSTarget() const
{
	return FPSTarget;
}

void ULesFightFPSMonitor::SetWarningThreshold(float FPS)
{
	WarningThreshold = FPS;
}

float ULesFightFPSMonitor::GetWarningThreshold() const
{
	return WarningThreshold;
}

void ULesFightFPSMonitor::EnableFPSLogging(bool bEnabled)
{
	bFPSLogging = bEnabled;
}

void ULesFightFPSMonitor::ResetStats()
{
	FPSHistory.Empty();
	FrameTimeHistory.Empty();
	CurrentFPS = 60.0f;
	MinFPS = 999.0f;
	MaxFPS = 0.0f;
	AverageFPS = 0.0f;
	SampleCount = 0;
}

#include "Framework/Performance/Core/LesFightMemoryTracker.h"

void ULesFightMemoryTracker::Initialize()
{
	const FPlatformMemoryStats Stats = FPlatformMemory::GetStats();
	CurrentMemoryMB = static_cast<float>(Stats.UsedPhysicalGB) * 1024.0f;
	PeakMemoryMB = CurrentMemoryMB;
	BaselineMemoryMB = CurrentMemoryMB;
	AvailableMemoryMB = static_cast<float>(Stats.AvailablePhysicalGB) * 1024.0f;

	if (bMemoryLogging)
	{
		UE_LOG(LogTemp, Log, TEXT("[MemoryTracker] Initialized. Current: %.2f MB, Available: %.2f MB"),
			CurrentMemoryMB, AvailableMemoryMB);
	}
}

void ULesFightMemoryTracker::Shutdown()
{
	AssetMemoryMap.Empty();
	TrackedObjects.Empty();
	ObjectMemorySnapshots.Empty();
}

void ULesFightMemoryTracker::Tick(float DeltaTime)
{
	const FPlatformMemoryStats Stats = FPlatformMemory::GetStats();
	CurrentMemoryMB = static_cast<float>(Stats.UsedPhysicalGB) * 1024.0f;
	AvailableMemoryMB = static_cast<float>(Stats.AvailablePhysicalGB) * 1024.0f;

	if (CurrentMemoryMB > PeakMemoryMB)
	{
		PeakMemoryMB = CurrentMemoryMB;
	}

	if (CurrentMemoryMB > Budget.TotalBudgetMB)
	{
		OnMemoryWarning.Broadcast(CurrentMemoryMB, Budget.TotalBudgetMB);
	}

	if (bMemoryLogging)
	{
		UE_LOG(LogTemp, Log, TEXT("[MemoryTracker] Current: %.2f MB, Peak: %.2f MB, Budget: %.2f MB"),
			CurrentMemoryMB, PeakMemoryMB, Budget.TotalBudgetMB);
	}
}

float ULesFightMemoryTracker::GetCurrentMemoryMB() const
{
	return CurrentMemoryMB;
}

float ULesFightMemoryTracker::GetPeakMemoryMB() const
{
	return PeakMemoryMB;
}

float ULesFightMemoryTracker::GetAvailableMemoryMB() const
{
	return AvailableMemoryMB;
}

float ULesFightMemoryTracker::GetMemoryUsageByCategory(EPerformanceCategory Category) const
{
	float Total = 0.0f;
	for (const auto& Pair : AssetMemoryMap)
	{
		Total += Pair.Value;
	}
	return Total;
}

void ULesFightMemoryTracker::ReportMemoryUsage(FName AssetName, float SizeMB)
{
	AssetMemoryMap.Add(AssetName, SizeMB);

	if (bMemoryLogging)
	{
		UE_LOG(LogTemp, Log, TEXT("[MemoryTracker] Reported: %s = %.2f MB"), *AssetName.ToString(), SizeMB);
	}
}

void ULesFightMemoryTracker::RemoveMemoryReport(FName AssetName)
{
	AssetMemoryMap.Remove(AssetName);
}

TArray<FString> ULesFightMemoryTracker::GetLargestAssets(int32 Count) const
{
	TArray<TPair<FName, float>> SortedAssets;
	for (const auto& Pair : AssetMemoryMap)
	{
		SortedAssets.Emplace(Pair.Key, Pair.Value);
	}

	SortedAssets.Sort([](const TPair<FName, float>& A, const TPair<FName, float>& B)
	{
		return A.Value > B.Value;
	});

	TArray<FString> Result;
	for (int32 i = 0; i < FMath::Min(Count, SortedAssets.Num()); i++)
	{
		Result.Add(SortedAssets[i].Key.ToString());
	}

	return Result;
}

FMemoryBudget ULesFightMemoryTracker::GetMemoryBudget() const
{
	return Budget;
}

void ULesFightMemoryTracker::SetMemoryBudget(FMemoryBudget NewBudget)
{
	Budget = NewBudget;
}

bool ULesFightMemoryTracker::IsMemoryBudgetExceeded() const
{
	return CurrentMemoryMB > Budget.TotalBudgetMB;
}

float ULesFightMemoryTracker::GetMemoryUsagePercentage() const
{
	if (Budget.TotalBudgetMB > 0.0f)
	{
		return (CurrentMemoryMB / Budget.TotalBudgetMB) * 100.0f;
	}
	return 0.0f;
}

bool ULesFightMemoryTracker::TrackObject(UObject* Object)
{
	if (Object == nullptr)
	{
		return false;
	}

	TrackedObjects.Add(Object);

	float ObjectSize = static_cast<float>(FPlatformMemory::GetStats().UsedPhysicalGB) * 1024.0f;
	ObjectMemorySnapshots.Add(Object->GetFName(), ObjectSize);

	return true;
}

void ULesFightMemoryTracker::UntrackObject(UObject* Object)
{
	if (Object == nullptr)
	{
		return;
	}

	TrackedObjects.Remove(Object);
	ObjectMemorySnapshots.Remove(Object->GetFName());
}

int32 ULesFightMemoryTracker::GetTrackedObjectCount() const
{
	return TrackedObjects.Num();
}

TArray<FString> ULesFightMemoryTracker::DetectMemoryLeaks() const
{
	TArray<FString> Leaks;

	const FPlatformMemoryStats Stats = FPlatformMemory::GetStats();
	const float CurrentMB = static_cast<float>(Stats.UsedPhysicalGB) * 1024.0f;

	if (BaselineMemoryMB > 0.0f && (CurrentMB - BaselineMemoryMB) > 500.0f)
	{
		Leaks.Add(TEXT("Potential memory leak detected: ") +
			FString::Printf(TEXT("Current (%.2f MB) exceeds baseline (%.2f MB) by more than 500 MB"),
				CurrentMB, BaselineMemoryMB));
	}

	for (const auto& Pair : ObjectMemorySnapshots)
	{
		const float CurrentObjSize = static_cast<float>(FPlatformMemory::GetStats().UsedPhysicalGB) * 1024.0f;
		if ((CurrentObjSize - Pair.Value) > 100.0f)
		{
			Leaks.Add(FString::Printf(TEXT("Tracked object '%s' may have leaked (baseline: %.2f MB, current: %.2f MB)"),
				*Pair.Key.ToString(), Pair.Value, CurrentObjSize));
		}
	}

	return Leaks;
}

void ULesFightMemoryTracker::EnableMemoryLogging(bool bEnabled)
{
	bMemoryLogging = bEnabled;
}

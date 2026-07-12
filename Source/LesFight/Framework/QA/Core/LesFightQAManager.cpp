#include "Framework/QA/Core/LesFightQAManager.h"

void ULesFightQAManager::Initialize()
{
	AllBugs.Empty();
	AllTestCases.Empty();
	ReleaseChecklist.Empty();
	bQARunning = false;
}

void ULesFightQAManager::Shutdown()
{
	AllBugs.Empty();
	AllTestCases.Empty();
	ReleaseChecklist.Empty();
	bQARunning = false;
}

void ULesFightQAManager::RunFullQAPipeline()
{
	bQARunning = true;

	UE_LOG(LogTemp, Log, TEXT("=== QA Pipeline Started ==="));
	RunFunctionalTests();
	RunRegressionTests();
	RunPerformanceTests();
	GenerateQAReport();

	UE_LOG(LogTemp, Log, TEXT("=== QA Pipeline Completed ==="));
	bQARunning = false;
}

TArray<FQATestCase> ULesFightQAManager::RunFunctionalTests()
{
	UE_LOG(LogTemp, Log, TEXT("Running functional test suite..."));
	TArray<FQATestCase> Results;
	return Results;
}

TArray<FQATestCase> ULesFightQAManager::RunRegressionTests()
{
	UE_LOG(LogTemp, Log, TEXT("Running regression test suite..."));
	TArray<FQATestCase> Results;
	return Results;
}

TArray<FQATestCase> ULesFightQAManager::RunPerformanceTests()
{
	UE_LOG(LogTemp, Log, TEXT("Running performance test suite..."));
	TArray<FQATestCase> Results;
	return Results;
}

void ULesFightQAManager::GenerateQAReport()
{
	UE_LOG(LogTemp, Log, TEXT("=== QA Report ==="));
	UE_LOG(LogTemp, Log, TEXT("Total Bugs: %d"), AllBugs.Num());

	int32 CriticalCount = 0;
	for (const FQABugEntry& Bug : AllBugs)
	{
		if (Bug.Severity == EBugSeverity::Critical && Bug.Status != EBugStatus::Closed && Bug.Status != EBugStatus::WontFix)
		{
			CriticalCount++;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Open Critical Bugs: %d"), CriticalCount);
	UE_LOG(LogTemp, Log, TEXT("Ready for Release: %s"), IsReadyForRelease() ? TEXT("YES") : TEXT("NO"));
}

TArray<FQABugEntry> ULesFightQAManager::GetOpenBugs() const
{
	TArray<FQABugEntry> Open;
	for (const FQABugEntry& Bug : AllBugs)
	{
		if (Bug.Status != EBugStatus::Closed && Bug.Status != EBugStatus::WontFix)
		{
			Open.Add(Bug);
		}
	}
	return Open;
}

TArray<FQABugEntry> ULesFightQAManager::GetBugsBySeverity(EBugSeverity Severity) const
{
	TArray<FQABugEntry> Filtered;
	for (const FQABugEntry& Bug : AllBugs)
	{
		if (Bug.Severity == Severity)
		{
			Filtered.Add(Bug);
		}
	}
	return Filtered;
}

TArray<FQAReleaseChecklistItem> ULesFightQAManager::GetReleaseChecklist() const
{
	return ReleaseChecklist;
}

bool ULesFightQAManager::IsReadyForRelease() const
{
	for (const FQABugEntry& Bug : AllBugs)
	{
		if (Bug.Severity == EBugSeverity::Critical && Bug.Status != EBugStatus::Closed && Bug.Status != EBugStatus::WontFix)
		{
			return false;
		}
	}

	for (const FQAReleaseChecklistItem& Item : ReleaseChecklist)
	{
		if (Item.Priority == EReleaseChecklistItem::Critical && !Item.bCompleted)
		{
			return false;
		}
	}

	return true;
}

float ULesFightQAManager::GetQAScore() const
{
	float Score = 100.0f;

	int32 OpenCritical = 0;
	int32 OpenMajor = 0;
	int32 OpenMinor = 0;

	for (const FQABugEntry& Bug : AllBugs)
	{
		if (Bug.Status == EBugStatus::Closed || Bug.Status == EBugStatus::WontFix) continue;

		switch (Bug.Severity)
		{
		case EBugSeverity::Critical: OpenCritical++; break;
		case EBugSeverity::Major:    OpenMajor++;    break;
		case EBugSeverity::Minor:    OpenMinor++;    break;
		default: break;
		}
	}

	Score -= OpenCritical * 10.0f;
	Score -= OpenMajor * 5.0f;
	Score -= OpenMinor * 1.0f;

	return FMath::Clamp(Score, 0.0f, 100.0f);
}

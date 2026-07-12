#include "Framework/QA/Core/LesFightTestReportGenerator.h"
#include "Misc/FileHelper.h"

void ULesFightTestReportGenerator::Initialize()
{
	GeneratedReports.Empty();
}

void ULesFightTestReportGenerator::Shutdown()
{
	GeneratedReports.Empty();
}

FString ULesFightTestReportGenerator::GenerateSummaryReport(const TArray<FQATestCase>& TestCases, const TArray<FQABugEntry>& Bugs)
{
	FString Report;
	Report += TEXT("========================================\n");
	Report += TEXT("  LesFight QA Summary Report\n");
	Report += TEXT("========================================\n\n");

	int32 Passed = 0, Failed = 0, Skipped = 0, Blocked = 0;
	for (const FQATestCase& Test : TestCases)
	{
		switch (Test.Result)
		{
		case ETestResult::Passed:  Passed++;  break;
		case ETestResult::Failed:  Failed++;  break;
		case ETestResult::Skipped: Skipped++; break;
		case ETestResult::Blocked: Blocked++; break;
		default: break;
		}
	}

	int32 OpenBugs = 0;
	int32 CriticalOpen = 0;
	for (const FQABugEntry& Bug : Bugs)
	{
		if (Bug.Status != EBugStatus::Closed && Bug.Status != EBugStatus::WontFix)
		{
			OpenBugs++;
			if (Bug.Severity == EBugSeverity::Critical) CriticalOpen++;
		}
	}

	Report += FString::Printf(TEXT("Test Results:\n"));
	Report += FString::Printf(TEXT("  Total:    %d\n"), TestCases.Num());
	Report += FString::Printf(TEXT("  Passed:   %d (%.1f%%)\n"), Passed, TestCases.Num() > 0 ? (100.0f * Passed / TestCases.Num()) : 0.0f);
	Report += FString::Printf(TEXT("  Failed:   %d\n"), Failed);
	Report += FString::Printf(TEXT("  Skipped:  %d\n"), Skipped);
	Report += FString::Printf(TEXT("  Blocked:  %d\n\n"), Blocked);

	Report += FString::Printf(TEXT("Bug Status:\n"));
	Report += FString::Printf(TEXT("  Total Bugs:     %d\n"), Bugs.Num());
	Report += FString::Printf(TEXT("  Open Bugs:      %d\n"), OpenBugs);
	Report += FString::Printf(TEXT("  Critical Open:  %d\n"), CriticalOpen);

	if (CriticalOpen == 0 && (TestCases.Num() == 0 || Failed == 0))
	{
		Report += TEXT("\n  >> Overall: PASSED <<\n");
	}
	else
	{
		Report += TEXT("\n  >> Overall: ISSUES REMAIN <<\n");
	}

	return Report;
}

FString ULesFightTestReportGenerator::GenerateDetailedReport(const TArray<FQATestCase>& TestCases, const TArray<FQABugEntry>& Bugs)
{
	FString Report = GenerateSummaryReport(TestCases, Bugs);
	Report += TEXT("\n\n=== Detailed Test Results ===\n\n");

	for (const FQATestCase& Test : TestCases)
	{
		FString ResultStr;
		switch (Test.Result)
		{
		case ETestResult::Passed:  ResultStr = TEXT("PASS");   break;
		case ETestResult::Failed:  ResultStr = TEXT("FAIL");   break;
		case ETestResult::Skipped: ResultStr = TEXT("SKIP");   break;
		case ETestResult::Blocked: ResultStr = TEXT("BLOCK");  break;
		case ETestResult::NotRun:  ResultStr = TEXT("NOT RUN");break;
		}

		Report += FString::Printf(TEXT("[%s] #%d: %s\n"), *ResultStr, Test.TestCaseID, *Test.TestName.ToString());
		Report += FString::Printf(TEXT("  Category: %d | Duration: %.2fs\n"), static_cast<int32>(Test.Category), Test.DurationSeconds);

		if (Test.Result == ETestResult::Failed)
		{
			Report += FString::Printf(TEXT("  Actual: %s\n"), *Test.ActualOutcome.ToString());
		}
		Report += TEXT("\n");
	}

	return Report;
}

FString ULesFightTestReportGenerator::GenerateBugReport(const TArray<FQABugEntry>& Bugs)
{
	FString Report;
	Report += TEXT("=== Bug Report ===\n\n");

	TArray<EBugSeverity> SeverityOrder = { EBugSeverity::Critical, EBugSeverity::Major, EBugSeverity::Minor, EBugSeverity::Cosmetic, EBugSeverity::Suggestion };

	for (EBugSeverity Sev : SeverityOrder)
	{
		bool bHasHeader = false;
		for (const FQABugEntry& Bug : Bugs)
		{
			if (Bug.Severity != Sev) continue;
			if (!bHasHeader)
			{
				FString SevStr;
				switch (Sev)
				{
				case EBugSeverity::Critical:  SevStr = TEXT("CRITICAL"); break;
				case EBugSeverity::Major:     SevStr = TEXT("MAJOR");    break;
				case EBugSeverity::Minor:     SevStr = TEXT("MINOR");    break;
				case EBugSeverity::Cosmetic:  SevStr = TEXT("COSMETIC"); break;
				case EBugSeverity::Suggestion:SevStr = TEXT("SUGGESTION");break;
				}
				Report += FString::Printf(TEXT("--- %s ---\n"), *SevStr);
				bHasHeader = true;
			}

			FString StatusStr;
			switch (Bug.Status)
			{
			case EBugStatus::New:		StatusStr = TEXT("New");		break;
			case EBugStatus::Confirmed:	StatusStr = TEXT("Confirmed");	break;
			case EBugStatus::InProgress:StatusStr = TEXT("InProgress");	break;
			case EBugStatus::Fixed:		StatusStr = TEXT("Fixed");		break;
			case EBugStatus::Verified:	StatusStr = TEXT("Verified");	break;
			case EBugStatus::Closed:	StatusStr = TEXT("Closed");		break;
			case EBugStatus::WontFix:	StatusStr = TEXT("WontFix");	break;
			}

			Report += FString::Printf(TEXT("  [#%d][%s] %s\n"), Bug.BugID, *StatusStr, *Bug.Title);
			Report += FString::Printf(TEXT("    Area: %s | Assigned: %s\n"), *Bug.Area, *Bug.AssignedTo);
		}
		Report += TEXT("\n");
	}

	return Report;
}

FString ULesFightTestReportGenerator::GeneratePerformanceReport(const TArray<FQAPerformanceSample>& Samples)
{
	FString Report;
	Report += TEXT("=== Performance Test Report ===\n\n");

	for (const FQAPerformanceSample& Sample : Samples)
	{
		Report += FString::Printf(TEXT("Test: %s\n"), *Sample.TestName);
		Report += FString::Printf(TEXT("  Platform: %s\n"), *Sample.Platform);
		Report += FString::Printf(TEXT("  Avg FPS:  %.1f | Min FPS: %.1f | P1: %.1f\n"), Sample.AverageFPS, Sample.MinFPS, Sample.P1FPS);
		Report += FString::Printf(TEXT("  Memory:   %.0f MB\n"), Sample.MemoryMB);
		Report += FString::Printf(TEXT("  CPU:      %.2f ms | GPU: %.2f ms\n"), Sample.CPUTimeMs, Sample.GPUTimeMs);
		Report += FString::Printf(TEXT("  Load:     %.0f ms\n\n"), Sample.LoadTimeMs);
	}

	return Report;
}

FString ULesFightTestReportGenerator::GenerateReleaseReport(const TArray<FQAReleaseChecklistItem>& Checklist, bool bReadyForRelease)
{
	FString Report;
	Report += TEXT("=== Release Readiness Report ===\n\n");

	int32 Completed = 0;
	int32 Total = Checklist.Num();
	for (const FQAReleaseChecklistItem& Item : Checklist)
	{
		if (Item.bCompleted) Completed++;
	}

	Report += FString::Printf(TEXT("Checklist: %d/%d completed (%.0f%%)\n\n"), Completed, Total, Total > 0 ? (100.0f * Completed / Total) : 0.0f);

	Report += TEXT("Items:\n");
	for (const FQAReleaseChecklistItem& Item : Checklist)
	{
		FString PriorityStr;
		switch (Item.Priority)
		{
		case EReleaseChecklistItem::Critical:   PriorityStr = TEXT("CRIT"); break;
		case EReleaseChecklistItem::Required:   PriorityStr = TEXT("REQ");  break;
		case EReleaseChecklistItem::Recommended:PriorityStr = TEXT("REC");  break;
		case EReleaseChecklistItem::Optional:   PriorityStr = TEXT("OPT");  break;
		}

		Report += FString::Printf(TEXT("  [%s][%s] %s\n"),
			Item.bCompleted ? TEXT("X") : TEXT(" "),
			*PriorityStr,
			*Item.Item);
	}

	Report += FString::Printf(TEXT("\nRelease Ready: %s\n"), bReadyForRelease ? TEXT("YES") : TEXT("NO"));

	return Report;
}

FString ULesFightTestReportGenerator::GenerateKnownIssuesDocument(const TArray<FQABugEntry>& KnownIssues)
{
	FString Doc;
	Doc += TEXT("# LesFight - Known Issues\n\n");
	Doc += TEXT("This document lists known issues in the current build.\n\n");
	Doc += GenerateBugReport(KnownIssues);
	Doc += TEXT("---\n");
	Doc += TEXT("Last Updated: ") + FDateTime::Now().ToString() + TEXT("\n");
	return Doc;
}

bool ULesFightTestReportGenerator::ExportReportToFile(const FString& FilePath, const FString& ReportContent)
{
	bool bSuccess = FFileHelper::SaveStringToFile(ReportContent, *FilePath);
	if (bSuccess)
	{
		GeneratedReports.Add(FilePath);
		UE_LOG(LogTemp, Log, TEXT("[ReportGenerator] Report saved to %s"), *FilePath);
	}
	return bSuccess;
}

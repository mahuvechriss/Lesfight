#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightTestReportGenerator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightTestReportGenerator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	FString GenerateSummaryReport(const TArray<FQATestCase>& TestCases, const TArray<FQABugEntry>& Bugs);

	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	FString GenerateDetailedReport(const TArray<FQATestCase>& TestCases, const TArray<FQABugEntry>& Bugs);

	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	FString GenerateBugReport(const TArray<FQABugEntry>& Bugs);

	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	FString GeneratePerformanceReport(const TArray<FQAPerformanceSample>& Samples);

	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	FString GenerateReleaseReport(const TArray<FQAReleaseChecklistItem>& Checklist, bool bReadyForRelease);

	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	FString GenerateKnownIssuesDocument(const TArray<FQABugEntry>& KnownIssues);

	UFUNCTION(BlueprintCallable, Category = "QA|ReportGenerator")
	bool ExportReportToFile(const FString& FilePath, const FString& ReportContent);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|ReportGenerator")
	TArray<FString> GeneratedReports;
};

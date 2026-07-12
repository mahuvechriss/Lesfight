#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightAutomationFramework.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTestSuiteComplete, const FATestSuiteResult&, Result);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAutomationFramework : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	FATestSuiteResult RunAutomatedSuite(const FString& SuiteName, const TArray<FQATestCase>& TestCases);

	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	FATestSuiteResult RunCategory(ETestCategory Category, const TArray<FQATestCase>& TestCases);

	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	void ScheduleAutomatedRun(const FString& ScheduleName, float IntervalSeconds);

	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	void CancelScheduledRun(const FString& ScheduleName);

	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	TArray<FATestSuiteResult> GetRunHistory() const;

	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	int32 GetTotalTestsRun() const;

	UFUNCTION(BlueprintCallable, Category = "QA|Automation")
	bool ExportAutomationResults(const FString& FilePath);

	UPROPERTY(BlueprintAssignable, Category = "QA|Automation")
	FOnTestSuiteComplete OnTestSuiteComplete;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|Automation")
	TArray<FATestSuiteResult> RunHistory;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|Automation")
	TMap<FString, float> ScheduledRuns;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|Automation")
	int32 TotalTestsRun = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|Automation")
	bool bAutomationActive = false;
};

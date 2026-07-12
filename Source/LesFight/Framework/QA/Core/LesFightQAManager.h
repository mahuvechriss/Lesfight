#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightQAManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightQAManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	void RunFullQAPipeline();

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	TArray<FQATestCase> RunFunctionalTests();

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	TArray<FQATestCase> RunRegressionTests();

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	TArray<FQATestCase> RunPerformanceTests();

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	void GenerateQAReport();

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	TArray<FQABugEntry> GetOpenBugs() const;

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	TArray<FQABugEntry> GetBugsBySeverity(EBugSeverity Severity) const;

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	TArray<FQAReleaseChecklistItem> GetReleaseChecklist() const;

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	bool IsReadyForRelease() const;

	UFUNCTION(BlueprintCallable, Category = "QA|Manager")
	float GetQAScore() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|Manager")
	TArray<FQABugEntry> AllBugs;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|Manager")
	TArray<FQATestCase> AllTestCases;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|Manager")
	TArray<FQAReleaseChecklistItem> ReleaseChecklist;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|Manager")
	bool bQARunning = false;
};

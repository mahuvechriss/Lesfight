#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightTestCaseManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightTestCaseManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	int32 AddTestCase(const FString& Name, const FText& Description, ETestCategory Category, const TArray<FString>& Steps, const FText& ExpectedOutcome);

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	FQATestCase GetTestCase(int32 ID) const;

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	TArray<FQATestCase> GetAllTestCases() const;

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	TArray<FQATestCase> GetTestCasesByCategory(ETestCategory Category) const;

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	TArray<FQATestCase> GetTestCasesByResult(ETestResult Result) const;

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	bool UpdateTestResult(int32 TestCaseID, ETestResult Result, const FText& ActualOutcome);

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	int32 GetTotalCount() const;

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	int32 GetPassCount() const;

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	int32 GetFailCount() const;

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	float GetPassRate() const;

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	void ClearAllResults();

	UFUNCTION(BlueprintCallable, Category = "QA|TestCaseManager")
	TArray<FATestSuiteResult> GetSuiteResults() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|TestCaseManager")
	TArray<FQATestCase> TestCaseDatabase;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|TestCaseManager")
	TArray<FATestSuiteResult> SuiteResults;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|TestCaseManager")
	int32 NextTestCaseID = 1;
};

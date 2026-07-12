#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightRegressionTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightRegressionTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	TArray<FQATestCase> RunRegressionSuite();

	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	TArray<FQATestCase> RunPostFixValidation(int32 BugID);

	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	bool VerifySystemStillWorks(const FString& SystemName);

	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	TArray<FString> GetAffectedSystems(const FString& ChangeDescription);

	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	void RecordBaseline(const FString& BaselineName);

	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	bool CompareToBaseline(const FString& BaselineName);

	UFUNCTION(BlueprintCallable, Category = "QA|Regression")
	TArray<FString> GetRegressionHistory() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|Regression")
	TArray<FString> RegressionHistory;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|Regression")
	TMap<FString, TArray<FQATestCase>> Baselines;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|Regression")
	int32 TotalRegressionRuns = 0;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightPerformanceTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPerformanceTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunFPSTest(float DurationSeconds);

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunMemoryTest();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunCPUTest();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunGPUTest();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunLoadTimeTest();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunNetworkPerformanceTest();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunLongPlaySessionTest(float DurationMinutes);

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunMaxEffectsTest();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunHeavyCustomizationTest();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> RunFullPerformanceSuite();

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	bool IsTargetFPSMet(float TargetFPS) const;

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	float GetAverageFPS() const;

	UFUNCTION(BlueprintCallable, Category = "QA|Performance")
	TArray<FQAPerformanceSample> GetResults() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|Performance")
	TArray<FQAPerformanceSample> Results;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightPerformanceDevTools.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPerformanceDevTools : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> ShowPerformanceDashboard();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> RunFrameAnalysis(int32 FrameCount);

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> InspectMemoryUsage();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> ShowRenderingStats();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> ShowNetworkStats();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> GenerateOptimizationReport();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> RunStressTest(EPerformanceCategory Category, int32 Intensity);

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> CompareQualityLevels();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	void LogPerformanceEvent(const FString& Event);

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	TArray<FString> GetPerformanceLog() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	void ClearPerformanceLog();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	FOptimizationMetrics BenchmarkCurrentSettings();

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	void EnableDrawDebug(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|DevTools")
	bool IsDrawDebugEnabled() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|DevTools")
	TArray<FString> PerformanceLog;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|DevTools")
	bool bDrawDebug = false;

	static constexpr int32 MaxLogEntries = 500;
};

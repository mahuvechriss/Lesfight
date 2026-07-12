#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightPerformanceMonitor.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPerformanceMonitor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void RecordCPUSample(float UsagePercent);

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	float GetAverageCPUUsage() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void RecordGPUSample(float UsagePercent);

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	float GetAverageGPUUsage() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void RecordLoadingSample(FName AssetName, float LoadTimeMs);

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	float GetAverageLoadTime() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void RecordNetworkSample(float LatencyMs, float BandwidthKbps);

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	float GetAverageLatency() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void RecordDrawCallSample(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	int32 GetAverageDrawCalls() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void RecordTriangleSample(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	int32 GetAverageTriangleCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void RecordNiagaraSample(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	int32 GetActiveNiagaraCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	FPerformanceSnapshot GetPerformanceSnapshot() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	float GetOverallScore() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	FText GetPerformanceRating() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	bool IsOverPerforming() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	bool IsUnderPerforming() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	TArray<float> GetHistory(EPerformanceCategory Category) const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void ClearHistory();

	UFUNCTION(BlueprintCallable, Category = "Performance|Monitor")
	void EnableProfiling(bool bEnabled);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	TMap<EPerformanceCategory, TArray<float>> PerformanceHistory;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	float AvgCPU = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	float AvgGPU = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	float AvgLoadTime = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	float AvgLatency = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	int32 AvgDrawCalls = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	int32 AvgTriangles = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	int32 AvgNiagara = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Monitor")
	bool bProfiling = false;

	static constexpr int32 MaxHistory = 200;
};

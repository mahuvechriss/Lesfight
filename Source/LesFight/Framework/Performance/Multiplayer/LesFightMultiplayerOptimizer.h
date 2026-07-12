#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightMultiplayerOptimizer.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMultiplayerOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void SetMaxReplicationFreq(float Hz);

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	float GetMaxReplicationFreq() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void EnableDataCompression(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void SetBandwidthLimit(float Kbps);

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	float GetBandwidthLimit() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void OptimizeReplicationGraph();

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void SetSyncRate(float Hz);

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	float GetSyncRate() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	void EnableDeltaCompression(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	float GetCurrentBandwidthKbps() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	float GetAverageLatencyMs() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	float GetPacketLossPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Multiplayer")
	TArray<FString> GetOptimizationStatus() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Multiplayer")
	float MaxReplicationFreq = 30.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Multiplayer")
	float BandwidthLimitKbps = 256.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Multiplayer")
	float SyncRate = 20.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Multiplayer")
	bool bCompression = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Multiplayer")
	bool bDeltaCompression = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Multiplayer")
	EPerformanceQualityLevel CurrentLevel = EPerformanceQualityLevel::High;
};

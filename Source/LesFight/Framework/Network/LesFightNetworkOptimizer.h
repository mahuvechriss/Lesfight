#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkOptimizer.generated.h"

UENUM(BlueprintType)
enum class EOptimizationLevel : uint8
{
    None,
    Low,
    Medium,
    High,
    MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FBandwidthStats
{
    GENERATED_BODY()

    float CurrentBandwidthKbps;
    float AverageBandwidthKbps;
    float PeakBandwidthKbps;
    int32 PacketsPerSecond;
    int32 AveragePacketSize;
    float ReplicationEfficiency;

    FBandwidthStats()
        : CurrentBandwidthKbps(0.0f)
        , AverageBandwidthKbps(0.0f)
        , PeakBandwidthKbps(0.0f)
        , PacketsPerSecond(0)
        , AveragePacketSize(0)
        , ReplicationEfficiency(1.0f)
    {}
};

UCLASS(Blueprintable)
class ULesFightNetworkOptimizer : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNetworkOptimizer();

    void Initialize(ULesFightMultiplayerManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    void SetBandwidthLimit(int32 MaxKbps);

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    void SetReplicationRate(float RateHz);

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    void SetOptimizationLevel(EOptimizationLevel Level);

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    EOptimizationLevel GetOptimizationLevel() const { return CurrentLevel; }

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    FBandwidthStats GetBandwidthStats() const { return Stats; }

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    bool ShouldReplicateThisFrame() const;

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    float GetAdaptiveReplicationRate() const;

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    void RecordPacket(int32 PacketSizeBytes);

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    void EnableAdaptiveRate(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    bool IsAdaptiveRateEnabled() const { return bAdaptiveRate; }

    UFUNCTION(BlueprintCallable, Category = "Network|Optimization")
    void ResetStats();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxBandwidthKbps;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float TargetReplicationRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    EOptimizationLevel CurrentLevel;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FBandwidthStats Stats;

private:
    TWeakObjectPtr<ULesFightMultiplayerManager> MultiplayerManager;
    float LastReplicationTime;
    float LastStatsUpdateTime;
    bool bAdaptiveRate;
    TArray<int32> PacketSizeHistory;
    TArray<float> ReplicationTimeHistory;

    void UpdateStats(float DeltaTime);
    float CalculateOptimalReplicationRate() const;
    void ApplyOptimizationLevel(EOptimizationLevel Level);
};

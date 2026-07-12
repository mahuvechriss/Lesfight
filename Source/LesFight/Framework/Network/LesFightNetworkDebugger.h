#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightNetworkDebugger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDebugLogAdded, FString, Category, FString, Message);

UCLASS(Blueprintable)
class ULesFightNetworkDebugger : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNetworkDebugger();

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void EnableDebugging(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    bool IsDebuggingEnabled() const { return bDebuggingEnabled; }

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void SetLatencySimulation(int32 MinMs, int32 MaxMs);

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void SetPacketLossSimulation(float LossPercentage);

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void SetJitterSimulation(int32 JitterMs);

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void LogNetworkEvent(const FString& Category, const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    TArray<FString> GetDebugLog() const { return DebugLog; }

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void ClearDebugLog();

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void SimulatePacketDrop();

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void SimulateLatencySpike(int32 SpikeMs);

    UFUNCTION(BlueprintCallable, Category = "Network|Debug")
    void SetDebugDisplayMode(bool bShowOverlay);

    UFUNCTION(BlueprintPure, Category = "Network|Debug")
    bool ShouldDropPacket() const;

    UFUNCTION(BlueprintPure, Category = "Network|Debug")
    int32 GetSimulatedLatencyMs() const;

    UFUNCTION(BlueprintPure, Category = "Network|Debug")
    int32 GetCurrentFrame() const { return FrameCounter; }

    UFUNCTION(BlueprintPure, Category = "Network|Debug")
    TArray<float> GetFrameTimeHistory() const { return FrameTimeHistory; }

    UFUNCTION(BlueprintPure, Category = "Network|Debug")
    FString GetReplicationDebugString() const;

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDebugLogAdded OnDebugLogAdded;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FString> DebugLog;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bDebuggingEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bShowOverlay;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxLogEntries;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float StatsUpdateInterval;

private:
    int32 FrameCounter;
    float FrameTimeAccumulator;
    TArray<float> FrameTimeHistory;

    struct FLatencySimConfig
    {
        bool bEnabled;
        int32 MinLatencyMs;
        int32 MaxLatencyMs;
        float PacketLossRate;
        int32 JitterMs;

        FLatencySimConfig()
            : bEnabled(false), MinLatencyMs(0), MaxLatencyMs(0)
            , PacketLossRate(0.0f), JitterMs(0)
        {}
    } LatencyConfig;

    TArray<int32> PendingLatencyPackets;
    float LastStatsTime;

    void SimulateLatency();
    void UpdateFrameTimes(float DeltaTime);
};

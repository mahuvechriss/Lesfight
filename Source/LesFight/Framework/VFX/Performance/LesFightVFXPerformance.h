#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightVFXPerformance.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightVFXPerformance : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    void SetQualityLevel(EVFXQualityLevel Level);

    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    EVFXQualityLevel GetQualityLevel() const;

    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    FVFXPerformanceMetrics GetCurrentMetrics() const;

    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    void OptimizeForPlatform();

    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    EVFXQualityLevel GetRecommendedQuality() const;

    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    float RunVFXBenchmark();

    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    void StartProfiling();

    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    void StopProfiling();

    UFUNCTION(BlueprintCallable, Category = "VFX Performance")
    FString GetPerformanceReport() const;

    void Initialize(ULesFightVFXWorldManager* InOwner);

protected:
    UPROPERTY()
    EVFXQualityLevel CurrentQuality;

    UPROPERTY()
    FVFXPerformanceMetrics Metrics;

    UPROPERTY()
    bool bProfiling;

    UPROPERTY()
    TArray<float> FrameGPUTimes;

    UPROPERTY()
    TMap<EVFXQualityLevel, int32> MaxParticlesByQuality;

    UPROPERTY()
    TMap<EVFXQualityLevel, int32> MaxSystemsByQuality;

private:
    TWeakObjectPtr<class ULesFightVFXWorldManager> OwnerManager;
};

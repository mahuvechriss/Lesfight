#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaPerformance.generated.h"

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaPerformance : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    void SetQualityLevel(int32 Level);

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    int32 GetQualityLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    void SetNaniteEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    void SetLumenEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    void SetTexturePoolSize(int32 MB);

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    FArenaPerformanceMetrics GetCurrentMetrics() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    float GetAverageFPS() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    FArenaPerformanceMetrics GetRecommendedSettings() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    void OptimizeForArena(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Performance")
    float RunPerformanceBenchmark();

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Arena|Performance")
    int32 QualityLevel = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Performance")
    bool bNanite = true;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Performance")
    bool bLumen = true;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Performance")
    int32 TexturePoolMB = 4096;

    UPROPERTY()
    FArenaPerformanceMetrics Metrics;

    UPROPERTY()
    TArray<float> FrameTimeHistory;

    UPROPERTY()
    float PerformanceScore = 0.0f;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;
};

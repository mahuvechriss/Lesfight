#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightAIPerformance.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIPerformance : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void SetProcessingPriority(int32 Priority);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    int32 GetProcessingPriority() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void SetMaxMemoryMB(int32 MB);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    int32 GetMaxMemoryMB() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    float EstimateProcessingTime(EAIPipelineStage Stage) const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void SetThreadCount(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    int32 GetThreadCount() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void EnableAsyncProcessing(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    bool IsAsyncProcessingEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    FString GetPerformanceReport() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void LimitTextureResolution(int32 MaxResolution);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    int32 GetTextureResolutionLimit() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void OptimizeForPlatform();

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void StartPerformanceTracking();

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void StopPerformanceTracking();

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    float GetAverageStageTime(EAIPipelineStage Stage) const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Performance|Config")
    int32 ProcessingPriority;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Performance|Config")
    int32 MaxMemoryMB;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Performance|Config")
    int32 ThreadCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Performance|Config")
    int32 TextureResolutionLimit;

    UPROPERTY(BlueprintReadWrite, Category = "AI|Performance|Config")
    bool bAsyncProcessing;

    UPROPERTY(BlueprintReadWrite, Category = "AI|Performance|Tracking")
    bool bTracking;

    UPROPERTY(BlueprintReadOnly, Category = "AI|Performance|Tracking")
    TMap<EAIPipelineStage, TArray<float>> StageTimings;

private:
    TWeakObjectPtr<class ULesFightAIManager> OwnerManager;

public:
    void Initialize(ULesFightAIManager* InManager);
};

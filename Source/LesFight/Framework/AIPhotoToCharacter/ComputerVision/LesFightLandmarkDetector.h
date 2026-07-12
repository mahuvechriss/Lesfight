#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightLandmarkDetector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLandmarksDetected, const FFacialLandmarkData&, Landmarks);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightLandmarkDetector : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    void DetectLandmarks(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    FFacialLandmarkData GetLandmarks() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    int32 GetLandmarkCount() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    float GetLandmarkConfidence() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    void SetLandmarkAccuracy(int32 Level);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    bool VisualizeLandmarks(const FString& ImagePath, const FString& OutputPath);

    UPROPERTY(BlueprintAssignable, Category = "AI Photo|Computer Vision")
    FOnLandmarksDetected OnLandmarksDetected;

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Detection")
    FFacialLandmarkData DetectedLandmarks;

    UPROPERTY(VisibleInstanceOnly, Category = "Detection")
    float LandmarkConfidence = 0.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Detection")
    int32 AccuracyLevel = 2;

    UPROPERTY(VisibleInstanceOnly, Category = "Detection")
    bool bLandmarksDetected = false;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightFaceDetector.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightFaceDetector : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    void DetectFaces(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    int32 GetDetectedFaceCount() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    FBox2D GetFaceBounds(int32 FaceIndex) const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    float GetFaceConfidence(int32 FaceIndex) const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    void SetDetectionThreshold(float Threshold);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    float GetDetectionThreshold() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    bool IsFaceDetected() const;

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Detection")
    TArray<FBox2D> DetectedFaces;

    UPROPERTY(VisibleInstanceOnly, Category = "Detection")
    TArray<float> FaceConfidences;

    UPROPERTY(EditDefaultsOnly, Category = "Detection")
    float DetectionThreshold = 0.7f;

    UPROPERTY(EditDefaultsOnly, Category = "Detection")
    int32 MaxFaces = 4;

    UPROPERTY(VisibleInstanceOnly, Category = "Detection")
    FBox2D PrimaryFaceBounds;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};

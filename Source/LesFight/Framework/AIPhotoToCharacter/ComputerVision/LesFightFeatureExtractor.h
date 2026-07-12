#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightFeatureExtractor.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightFeatureExtractor : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    void ExtractFeatures(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    FFaceFeatureData GetFaceFeatures() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    FHairDetectionData GetHairDetection() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    EFacialExpression GetExpression() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    TArray<FLinearColor> ExtractSkinTone(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    int32 EstimateAge(const FString& ImagePath);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Computer Vision")
    FString EstimateGender(const FString& ImagePath);

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Features")
    FFaceFeatureData ExtractedFeatures;

    UPROPERTY(VisibleInstanceOnly, Category = "Features")
    FHairDetectionData HairFeatures;

    UPROPERTY(VisibleInstanceOnly, Category = "Features")
    TArray<FLinearColor> SkinPalette;

    UPROPERTY(VisibleInstanceOnly, Category = "Features")
    bool bFeaturesExtracted = false;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightFaceReconstructor.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightFaceReconstructor : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void ReconstructFace(const FFaceFeatureData& Features, const FFacialLandmarkData& Landmarks);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    const F3DFaceReconstructionData& GetReconstructedData() const { return ReconstructedFace; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void SetReconstructionQuality(EAIGenerationQuality Quality);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    EAIGenerationQuality GetReconstructionQuality() const { return ReconstructionQuality; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void GenerateBlendShapes(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    TArray<FName> GetBlendShapeNames() const { return BlendShapeNames; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void RefineFaceFromMultipleImages(const TArray<FFaceFeatureData>& MultiViews);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void EstimateMissingFeatures(const FFaceFeatureData& PartialData);

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    F3DFaceReconstructionData ReconstructedFace;

    UPROPERTY(EditDefaultsOnly, Category = "Reconstruction")
    EAIGenerationQuality ReconstructionQuality = EAIGenerationQuality::Standard;

    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    bool bReconstructionComplete = false;

    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    TArray<FName> BlendShapeNames;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
    int32 VertexCount = 0;
    int32 TriangleCount = 0;
};

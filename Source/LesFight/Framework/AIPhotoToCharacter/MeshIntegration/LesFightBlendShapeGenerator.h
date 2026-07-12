#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightBlendShapeGenerator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightBlendShapeGenerator : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Blend Shapes")
    void GenerateBlendShapesFromFace(const F3DFaceReconstructionData& FaceData);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Blend Shapes")
    TArray<FVector> GetBlendShapeData(int32 Index) const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Blend Shapes")
    TArray<FName> GetAllBlendShapeNames() const { return BlendShapeNames; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Blend Shapes")
    int32 GetBlendShapeCount() const { return BlendShapeCount; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Blend Shapes")
    void ApplyBlendShapeToMesh(int32 ShapeIndex, float Weight);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Blend Shapes")
    void GenerateExpressionBlendShapes();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Blend Shapes")
    void GenerateVisemeBlendShapes();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Blend Shapes")
    bool TestBlendShapeCompatibility() const;

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Blend Shapes")
    TArray<FName> BlendShapeNames;

    UPROPERTY(VisibleInstanceOnly, Category = "Blend Shapes")
    TMap<FName, TArray<FVector>> BlendShapeDeltas;

    UPROPERTY(EditDefaultsOnly, Category = "Blend Shapes")
    TMap<FName, float> BlendShapeRanges;

    UPROPERTY(EditDefaultsOnly, Category = "Blend Shapes")
    int32 BlendShapeCount = 52;

    UPROPERTY(VisibleInstanceOnly, Category = "Blend Shapes")
    bool bBlendShapesGenerated = false;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
    TArray<FVector> BaseVertexPositions;

    void AddBlendShape(FName Name, const TArray<FVector>& Deltas, float Range);
    TArray<FVector> GenerateSimulatedDeltas(int32 VertexCount, float Magnitude, int32 Seed) const;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightBodyReconstructor.generated.h"

USTRUCT(BlueprintType)
struct FBodyMeshData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> VertexPositions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> TriangleIndices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> UVCoordinates;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> Normals;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MeshDataReference;
};

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightBodyReconstructor : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void ReconstructBody(const FBodyProportionData& Proportions);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    FBodyMeshData GetBodyMeshData() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void AdjustBodyProportions(const TMap<EBodyMorphType, float>& Adjustments);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    FString GenerateCharacterMesh(const F3DFaceReconstructionData& Face, const FBodyProportionData& Body);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    void SetBodyDetailLevel(int32 Level);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Reconstruction")
    const TMap<EBodyMorphType, float>& GetBodyMorphTargets() const { return BodyMorphValues; }

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    TArray<FVector> BodyVertexPositions;

    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    TArray<int32> BodyTriangles;

    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    TMap<EBodyMorphType, float> BodyMorphValues;

    UPROPERTY(EditDefaultsOnly, Category = "Reconstruction")
    int32 DetailLevel = 3;

    UPROPERTY(VisibleInstanceOnly, Category = "Reconstruction")
    bool bBodyGenerated = false;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};

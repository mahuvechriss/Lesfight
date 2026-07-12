#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightMeshAdapter.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMeshAdapter : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Mesh Integration")
    void AdaptMesh(const F3DFaceReconstructionData& FaceData, const TArray<FVector>& BodyVerts, const TArray<int32>& BodyTris);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Mesh Integration")
    FString GetAdaptedMeshPath() const { return AdaptedMeshPath; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Mesh Integration")
    void ApplyToCharacter(AActor* CharacterActor);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Mesh Integration")
    void SetMeshLOD(int32 LODLevel);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Mesh Integration")
    int32 GetMeshLOD() const { return CurrentLOD; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Mesh Integration")
    void OptimizeMeshGeometry(int32 TargetTriangleCount);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Mesh Integration")
    void GenerateCollisionMesh();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Mesh Integration")
    bool ValidateMesh() const;

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Mesh Adapter")
    FString AdaptedMeshPath;

    UPROPERTY(EditDefaultsOnly, Category = "Mesh Adapter")
    int32 CurrentLOD = 0;

    UPROPERTY(EditDefaultsOnly, Category = "Mesh Adapter")
    int32 MaxLOD = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Mesh Adapter")
    TArray<int32> TriangleCounts;

    UPROPERTY(VisibleInstanceOnly, Category = "Mesh Adapter")
    bool bMeshAdapted = false;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};

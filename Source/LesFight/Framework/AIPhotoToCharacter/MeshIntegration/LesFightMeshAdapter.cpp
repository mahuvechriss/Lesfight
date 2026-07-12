#include "LesFightMeshAdapter.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightMeshAdapter::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bMeshAdapted = false;
    CurrentLOD = 0;
    TriangleCounts = {25000, 15000, 8000, 4000};
}

void ULesFightMeshAdapter::AdaptMesh(const F3DFaceReconstructionData& FaceData, const TArray<FVector>& BodyVerts, const TArray<int32>& BodyTris)
{
    AdaptedMeshPath = TEXT("/Game/Generated/AICharacter_Mesh");
    bMeshAdapted = true;
}

void ULesFightMeshAdapter::ApplyToCharacter(AActor* CharacterActor)
{
}

void ULesFightMeshAdapter::SetMeshLOD(int32 LODLevel)
{
    CurrentLOD = FMath::Clamp(LODLevel, 0, MaxLOD);
}

void ULesFightMeshAdapter::OptimizeMeshGeometry(int32 TargetTriangleCount)
{
    if (TriangleCounts.IsValidIndex(CurrentLOD))
    {
        TriangleCounts[CurrentLOD] = TargetTriangleCount;
    }
}

void ULesFightMeshAdapter::GenerateCollisionMesh()
{
}

bool ULesFightMeshAdapter::ValidateMesh() const
{
    return !AdaptedMeshPath.IsEmpty();
}

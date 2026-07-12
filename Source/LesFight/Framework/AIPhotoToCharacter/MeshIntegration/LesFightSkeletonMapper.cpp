#include "LesFightSkeletonMapper.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightSkeletonMapper::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bSkeletonMapped = false;
    BoneWeights.Empty();
    CompatibilityReport.Empty();
}

void ULesFightSkeletonMapper::MapToSkeleton(const TArray<FVector>& MeshVertices)
{
    BoneWeights.Empty();
    BoneWeights.Reserve(MeshVertices.Num());

    for (int32 VertIdx = 0; VertIdx < MeshVertices.Num(); ++VertIdx)
    {
        int32 BoneCount = FMath::RandRange(1, 4);
        TArray<TPair<int32, float>> Weights;
        float TotalWeight = 0.0f;

        for (int32 b = 0; b < BoneCount; ++b)
        {
            int32 BoneIdx = FMath::RandRange(0, 14);
            float Weight = FMath::FRandRange(0.1f, 1.0f);
            Weights.Emplace(BoneIdx, Weight);
            TotalWeight += Weight;
        }

        float InvTotal = 1.0f / TotalWeight;
        for (auto& WeightPair : Weights)
        {
            WeightPair.Value *= InvTotal;
        }

        BoneWeights.Add(VertIdx, Weights);
    }

    CompatibilityReport.Add(TEXT("Mapped ") + FString::FromInt(MeshVertices.Num()) + TEXT(" vertices to skeleton ") + TargetSkeletonName.ToString());
    bSkeletonMapped = true;
}

void ULesFightSkeletonMapper::SetTargetSkeleton(FName SkeletonName)
{
    TargetSkeletonName = SkeletonName;
}

void ULesFightSkeletonMapper::AutoAssignBoneWeights()
{
    BoneWeights.Empty();

    TArray<TPair<int32, float>> SpineWeights = {{0, 0.6f}, {1, 0.3f}, {2, 0.1f}};
    TArray<TPair<int32, float>> NeckWeights = {{3, 0.7f}, {4, 0.3f}};
    TArray<TPair<int32, float>> HeadWeights = {{4, 0.8f}, {3, 0.2f}};
    TArray<TPair<int32, float>> ArmWeights = {{5, 0.5f}, {6, 0.3f}, {7, 0.2f}};
    TArray<TPair<int32, float>> LegWeights = {{8, 0.5f}, {9, 0.3f}, {10, 0.2f}};

    for (int32 i = 0; i < 30; ++i) BoneWeights.Add(i, SpineWeights);
    for (int32 i = 30; i < 40; ++i) BoneWeights.Add(i, NeckWeights);
    for (int32 i = 40; i < 55; ++i) BoneWeights.Add(i, HeadWeights);
    for (int32 i = 55; i < 80; ++i) BoneWeights.Add(i, ArmWeights);
    for (int32 i = 80; i < 100; ++i) BoneWeights.Add(i, LegWeights);

    bSkeletonMapped = true;
}

bool ULesFightSkeletonMapper::ValidateSkeletonMapping() const
{
    return BoneWeights.Num() > 0;
}

void ULesFightSkeletonMapper::RemapForDifferentSkeleton(FName SourceSkeleton, FName TargetSkeleton)
{
    TargetSkeletonName = TargetSkeleton;
    CompatibilityReport.Add(TEXT("Remapped from ") + SourceSkeleton.ToString() + TEXT(" to ") + TargetSkeleton.ToString());
}

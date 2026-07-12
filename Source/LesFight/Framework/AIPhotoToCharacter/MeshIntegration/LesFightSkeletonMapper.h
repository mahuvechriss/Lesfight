#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightSkeletonMapper.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSkeletonMapper : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(class ULesFightAIPipelineManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Skeleton Mapping")
    void MapToSkeleton(const TArray<FVector>& MeshVertices);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Skeleton Mapping")
    TMap<int32, TArray<TPair<int32, float>>> GetBoneWeights() const { return BoneWeights; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Skeleton Mapping")
    TArray<FString> GetSkeletonCompatibilityReport() const { return CompatibilityReport; }

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Skeleton Mapping")
    void SetTargetSkeleton(FName SkeletonName);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Skeleton Mapping")
    void AutoAssignBoneWeights();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Skeleton Mapping")
    bool ValidateSkeletonMapping() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Skeleton Mapping")
    void RemapForDifferentSkeleton(FName SourceSkeleton, FName TargetSkeleton);

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Skeleton Mapper")
    TMap<int32, TArray<TPair<int32, float>>> BoneWeights;

    UPROPERTY(EditDefaultsOnly, Category = "Skeleton Mapper")
    FName TargetSkeletonName = TEXT("Fighter_Skeleton");

    UPROPERTY(VisibleInstanceOnly, Category = "Skeleton Mapper")
    TArray<FString> CompatibilityReport;

    UPROPERTY(VisibleInstanceOnly, Category = "Skeleton Mapper")
    bool bSkeletonMapped = false;

private:
    TWeakObjectPtr<class ULesFightAIPipelineManager> OwnerManager;
};

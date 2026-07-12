#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "LesFightArenaDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FArenaDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ArenaID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ArenaName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UWorld> ArenaMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Thumbnail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> PlayerSpawnLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArenaBoundaryWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArenaBoundaryHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString AmbientMusic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EnvironmentType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraDistanceOverride;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> UnlockConditions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    FArenaDataTableRow()
        : ArenaBoundaryWidth(1000.0f)
        , ArenaBoundaryHeight(600.0f)
        , CameraDistanceOverride(0.0f)
    {}
};

UCLASS(BlueprintType)
class ULesFightArenaDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
    FArenaDataTableRow ArenaData;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(TEXT("ArenaData"), ArenaData.ArenaID);
    }
};

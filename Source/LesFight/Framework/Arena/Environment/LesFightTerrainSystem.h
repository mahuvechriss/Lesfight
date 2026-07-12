#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightTerrainSystem.generated.h"

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightTerrainSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Terrain")
    void RegisterTerrainType(ETerrainType Type, FName SurfaceMaterial);

    UFUNCTION(BlueprintCallable, Category = "Arena|Terrain")
    ETerrainType GetTerrainAtLocation(FVector WorldLocation) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Terrain")
    FName GetSurfaceMaterial(ETerrainType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Terrain")
    float GetMovementSpeedModifier(ETerrainType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Terrain")
    float GetFrictionCoefficient(ETerrainType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Terrain")
    TArray<ETerrainType> GetTerrainList() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Terrain")
    void SetTerrainGrid(TArray<TArray<ETerrainType>> Grid, FVector GridOrigin, float CellSize);

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Arena|Terrain")
    TArray<ETerrainType> AvailableTerrains;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Terrain")
    TMap<ETerrainType, FName> SurfaceMaterials;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Terrain")
    TMap<ETerrainType, float> SpeedModifiers;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Terrain")
    TMap<ETerrainType, float> FrictionCoefficients;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Terrain")
    TArray<TArray<ETerrainType>> TerrainGrid;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Terrain")
    FVector GridOrigin;

    UPROPERTY(BlueprintReadWrite, Category = "Arena|Terrain")
    float CellSize;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;
};

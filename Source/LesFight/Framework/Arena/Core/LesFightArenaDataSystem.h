#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaDataSystem.generated.h"

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaDataSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Data")
    void LoadArenaDatabase();

    UFUNCTION(BlueprintCallable, Category = "Arena|Data")
    void RegisterArena(const FArenaInfo& Info);

    UFUNCTION(BlueprintCallable, Category = "Arena|Data")
    FArenaInfo GetArenaInfo(EArenaType Type) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Data")
    TArray<FArenaInfo> GetAllArenaInfos() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Data")
    TArray<FArenaInfo> GetArenasByCategory(EArenaEnvironmentCategory Category) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Data")
    EArenaType GetRandomArena() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Data")
    int32 GetArenaCount() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Data")
    TArray<FString> GetArenaNames() const;

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Arena|Data")
    TMap<EArenaType, FArenaInfo> ArenaDatabase;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Data")
    TArray<EArenaType> ArenaList;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Data")
    FString DatabasePath;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;

    FArenaInfo BuildDefaultArenaInfo(EArenaType Type, EArenaEnvironmentCategory Category, const FString& Name, const FString& Description, const TArray<EWeatherType>& Weather, const TArray<ELightingPreset>& Lighting, const TArray<ETerrainType>& Terrain, const FVector& Bounds, const FVector& Spawn1, const FVector& Spawn2) const;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightDebrisSystem.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightDebrisSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Debris")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Arena|Debris")
    void SpawnDebris(FVector Location, int32 Count, FVector Spread);

    UFUNCTION(BlueprintCallable, Category = "Arena|Debris")
    void SpawnDebrisFromMesh(FVector Location, UStaticMesh* SourceMesh, int32 FragmentCount);

    UFUNCTION(BlueprintCallable, Category = "Arena|Debris")
    int32 GetActiveDebrisCount() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Debris")
    void SetMaxDebris(int32 Max);

    UFUNCTION(BlueprintCallable, Category = "Arena|Debris")
    void CleanupExpiredDebris();

    UFUNCTION(BlueprintCallable, Category = "Arena|Debris")
    void ClearAllDebris();

    UFUNCTION(BlueprintCallable, Category = "Arena|Debris")
    void SetDebrisLifetime(float Seconds);

protected:
    UPROPERTY()
    TArray<FVector> DebrisLocations;

    UPROPERTY()
    TArray<float> DebrisTimers;

    UPROPERTY()
    int32 MaxDebris = 200;

    UPROPERTY()
    float DebrisLifetime = 5.0f;

    UPROPERTY()
    TArray<FString> DebrisMeshPaths;

private:
    TWeakObjectPtr<class ULesFightArenaWorldManager> OwnerManager;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightEnvironmentManager.generated.h"

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightEnvironmentManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void InitializeEnvironment(FArenaInfo Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void UpdateEnvironment(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void SetWeather(EWeatherType Weather, EWeatherIntensity Intensity);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void SetLighting(ELightingPreset Preset);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    EWeatherType GetCurrentWeather() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    ELightingPreset GetCurrentLighting() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    ETerrainType GetTerrainAtLocation(FVector Location) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    ETerrainType GetSurfaceTypeAtLocation(FVector Location) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void TransitionToWeather(EWeatherType Target, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    FString GetEnvironmentDescription() const;

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Arena|Environment")
    FWeatherState CurrentWeather;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Environment")
    FArenaLightingState CurrentLighting;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Environment")
    TArray<ETerrainType> ArenaTerrain;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Environment")
    float EnvironmentTime;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;
};

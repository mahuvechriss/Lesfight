#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightEnvironmentalVFX.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightEnvironmentalVFX : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void InitializeForArena(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void PlayDustCloud(FVector Location, float Size);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void PlayDebrisBurst(FVector Location, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void PlayWaterSplash(FVector Location, float Force);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void PlayRainReaction(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void PlayLeafBurst(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void PlaySmokeEffect(FVector Location, float Density);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void PlayFireEffect(FVector Location, float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void SetWeatherVFX(EWeatherType Weather, EWeatherIntensity Intensity);

    UFUNCTION(BlueprintCallable, Category = "Environmental VFX")
    void ClearEnvironmentalEffects();

    void Initialize(ULesFightVFXWorldManager* InOwner);

protected:
    UPROPERTY()
    TMap<EArenaType, TArray<FString>> ArenaEffects;

    UPROPERTY()
    TMap<EWeatherType, FString> WeatherEffectPaths;

    UPROPERTY()
    int32 MaxEnvEffects;

    UPROPERTY()
    TArray<FName> ActiveEnvEffects;

private:
    TWeakObjectPtr<class ULesFightVFXWorldManager> OwnerManager;
};
